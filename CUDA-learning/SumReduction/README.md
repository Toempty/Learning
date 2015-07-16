
### 1. 使用 Thrust

Thrust 是一个开源的 C++ 库，用于开发高性能并行应用程序，以 C++ 标准模板库为蓝本实现。

官方文档见这里：[CUDA Thrust ](http://docs.nvidia.com/cuda/thrust/)

```
/* ... */
float *fMatrix_Device; // 指向设备显存
int iMatrixSize = iRow * iCol; // 矩阵元素个数

cudaMalloc((void**)&fMatrix_Device, iMatrixSize * sizeof(float)); // 在显存中为矩阵开辟空间
cudaMemcpy(fMatrix_Device, fMatrix_Host, iMatrixSize * sizeof(float), cudaMemcpyHostToDevice); // 将数据拷贝到显存

thrust::device_ptr<float> dev_ptr(fMatrix_Device);
float thrustResult = thrust::reduce(dev_ptr, dev_ptr + size_t(iMatrixSize), (float)0, thrust::plus<float>());
```

其中，fMatrix_Host 为指向主机内存的矩阵的头指针。

### 2. 我的 Reduction

```
/**
* 每个 warp 自动同步，不用 __syncthreads();
* volatile : 加上关键字volatile的变量将被定义为敏感变量，意思是加了volatile
*            的变量在内存中的值可能会随时发生变化，当程序要去读取这个变量时，
             必须要从内存中读取，而不是从缓存中读取
* sdata  数组头指针，数组位于共享内存
* tid    线程索引
*/
__device__ void warpReduce(volatile float *sdata, int tid)
{
    sdata[tid] += sdata[tid + 32];
    sdata[tid] += sdata[tid + 16];
    sdata[tid] += sdata[tid + 8];
    sdata[tid] += sdata[tid + 4];
    sdata[tid] += sdata[tid + 2];
    sdata[tid] += sdata[tid + 1];
}

/**
* 优化：解决了 reduce3 中存在的多余同步操作（每个warp默认自动同步）。
* globalInputData  输入数据，位于全局内存
* globalOutputData 输出数据，位于全局内存
*/
__global__ void reduce4(float *globalInputData, float *globalOutputData, unsigned int n)
{
    __shared__ float sdata[BLOCK_SIZE];

    // 坐标索引
    unsigned int tid = threadIdx.x;
    unsigned int index = blockIdx.x*(blockDim.x * 2) + threadIdx.x;
    unsigned int indexWithOffset = index + blockDim.x;

    if (index >= n) sdata[tid] = 0;
    else if (indexWithOffset >= n) sdata[tid] = globalInputData[index];
    else sdata[tid] = globalInputData[index] + globalInputData[indexWithOffset];
    
    __syncthreads();

    // 在共享内存中对每一个块进行规约计算
    for (unsigned int s = blockDim.x / 2; s>32; s >>= 1)
    {
        if (tid < s) sdata[tid] += sdata[tid + s];

        __syncthreads();
    }
    if (tid < 32) warpReduce(sdata, tid);

    // 把计算结果从共享内存写回全局内存
    if (tid == 0) globalOutputData[blockIdx.x] = sdata[0];
}

/**
* 计算 reduce4 函数的时间
* fMatrix_Host  矩阵头指针
* iRow          矩阵行数
* iCol          矩阵列数
* @return       和
*/
float RuntimeOfReduce4(float *fMatrix_Host, const int iRow, const int iCol)
{
    float *fReuslt = (float*)malloc(sizeof(float));;
    float *fMatrix_Device; // 指向设备显存
    int iMatrixSize = iRow * iCol; // 矩阵元素个数

    cudaMalloc((void**)&fMatrix_Device, iMatrixSize * sizeof(float)); // 在显存中为矩阵开辟空间
    cudaMemcpy(fMatrix_Device, fMatrix_Host, iMatrixSize * sizeof(float), cudaMemcpyHostToDevice); // 将数据拷贝到显存
    
    /* ... */
    for (int i = 1, int iNum = iMatrixSize; i < iMatrixSize; i = 2 * i * BLOCK_SIZE)
    {
        int iBlockNum = (iNum + (2 * BLOCK_SIZE) - 1) / (2 * BLOCK_SIZE);
        reduce4<<<iBlockNum, BLOCK_SIZE>>>(fMatrix_Device, fMatrix_Device, iNum);
        iNum = iBlockNum;
    }

    cudaMemcpy(fReuslt, fMatrix_Device, sizeof(float), cudaMemcpyDeviceToHost); // 将数据拷贝到内存

    /* ... */
    cudaFree(fMatrix_Device);// 释放显存空间

    return fReuslt[0];
}
```

上述程序是优化的最终版本，优化的主要内容包括：
1. 避免每个 Warp 中出现分支导致效率低下。
2. 减少取余操作。
3. 减小不必要的同步操作，每个warp都是默认同步的，不用额外的同步操作。
4. 减小线程的闲置，提高并行度

### 3. 时间对比

数据的大小为：

iRow = 1000;
iCol = 1000;

时间为：

```
ReduceThrust 的运行时间为：0.179968ms.
494497
Reduce0 的运行时间为：0.229152ms.
494497
Reduce1 的运行时间为：0.134816ms.
494497
Reduce2 的运行时间为：0.117504ms.
494497
Reduce3 的运行时间为：0.086016ms.
494497
Reduce4 的运行时间为：0.07424ms.
494497
CPU的运行时间为：1 ms.
494497
```

数据的大小为：

iRow = 2000;
iCol = 2000;

时间为：

```
ReduceThrust 的运行时间为：0.282944ms.
1.97828e+006
Reduce0 的运行时间为：0.779776ms.
1.97828e+006
Reduce1 的运行时间为：0.42624ms.
1.97828e+006
Reduce2 的运行时间为：0.343744ms.
1.97828e+006
Reduce3 的运行时间为：0.217248ms.
1.97828e+006
Reduce4 的运行时间为：0.160416ms.
1.97828e+006
CPU的运行时间为：3 ms.
1.97828e+006
```

数据的大小为：

iRow = 4000;
iCol = 4000;

时间为：

```
ReduceThrust 的运行时间为：0.536832ms.
7.91319e+006
Reduce0 的运行时间为：2.9919ms.
7.91319e+006
Reduce1 的运行时间为：1.56054ms.
7.91319e+006
Reduce2 的运行时间为：1.26618ms.
7.91319e+006
Reduce3 的运行时间为：0.726016ms.
7.91319e+006
Reduce4 的运行时间为：0.531712ms.
7.91319e+006
CPU的运行时间为：11 ms.
7.91319e+006
```

数据的大小为：

iRow = 6000;
iCol = 6000;

时间为：

```
ReduceThrust 的运行时间为：0.988992ms.
1.7807e+007
Reduce4 的运行时间为：1.09286ms.
1.7807e+007
CPU的运行时间为：25 ms.
1.7807e+007
```

数据的大小为：

iRow = 11000;
iCol = 11000;

时间为：

```
ReduceThrust 的运行时间为：2.9208ms.
5.98583e+007
Reduce4 的运行时间为：3.36998ms.
5.98583e+007
CPU的运行时间为：85 ms.
5.98583e+007
```

> 从上可以看出，2 中介绍的几种优化方式取得了良好的效果；另外，当数据量较少时，我自己优化的规约函数比 Thrust 中的规约更高效，但是当数据量大于 4000 * 4000 时，Thrust 更高效，因此还有优化的空间。

### 4. 完整代码
