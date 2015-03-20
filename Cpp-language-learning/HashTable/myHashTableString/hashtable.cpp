#include "hashtable.h"
#include <malloc.h>
#include <memory.h>

// 构造函数
hashtable::hashtable(int HashTablsSize)
{
    iHashTableSize = HashTablsSize;
    iHashTableDataCount = 0; // Table中数据个数
    pHashTable = (Node**)malloc(sizeof(Node*) * iHashTableSize);
    if (NULL == pHashTable)
    {
        return;
    }
    memset(pHashTable, 0, sizeof(Node*) * iHashTableSize);
}

// 析构函数
hashtable::~hashtable()
{
    free(pHashTable);
    pHashTable = NULL; //释放内存后，将指针设置为NULL。避免产生“野指针”
    iHashTableSize = 0;
    iHashTableDataCount = 0;
}

// 哈希函数
// int inline hashtable::HashFun(hashNodeType val)
// {
//     return (val ^ 0xdeadbeef) % iHashTableSize;
// }
/* End Of type int Hash Function */

// 哈希函数
// unsigned int inline hashtable::HashFun(hashNodeType val)
// {
//     unsigned int nHash = 0;
//     for (int i = 0; val[i] != '\0'; ++i)
//     {
//         nHash = (nHash << 5) + nHash + val[i];
//     }
//     return nHash % iHashTableSize;
// }
/* End Of times33 Hash Function */


// 哈希函数
// unsigned int inline hashtable::HashFun(hashNodeType val)
// {
//     unsigned int nHash = 0;
//     unsigned int seed = 131; //31 131 1313 13131

//     for (int i = 0; val[i] != '\0'; ++i)
//     {
//         nHash = nHash * seed + val[i];
//     }
//     return nHash % iHashTableSize;
// }
/* End Of BHDR Hash Function */

unsigned int inline hashtable::HashFun(hashNodeType val)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   for(std::size_t i = 0; i < val.length(); i++)
   {
      hash = hash * a + val[i];
      a    = a * b;
   }

   return hash % iHashTableSize;
}
/* End Of RS Hash Function */

bool hashtable::InsertHashTable(hashNodeType val)
{
    unsigned int key = HashFun(val);

    for(Node *p = pHashTable[key]; p != NULL; p = p->next)
    {
        if (val == p->nodeData)
        {
            return true;
        }
    }

    Node *pNode = new Node(val);
    if (NULL == pNode)
    {
        return false;
    }

    pNode->next = pHashTable[key];
    pHashTable[key] = pNode;

    iHashTableDataCount++; // Table中数据个数
    return true;
}

bool hashtable::FindHashTable(hashNodeType val)
{
    unsigned int key = HashFun(val);

    for(Node *p = pHashTable[key]; p!= NULL; p = p->next)
    {
        if (val == p->nodeData)
        {
            return true;
        }
    }
    return false;
}

int hashtable::SizeHashTable()
{
    return iHashTableSize;
}
