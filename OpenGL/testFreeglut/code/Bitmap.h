#ifdef _WIN64
#pragma comment (lib, "freeglut.lib")    /* link with Win64 GLUT lib */
#endif //_WIN64

#ifdef _WIN32
#pragma comment (lib, "freeglut32.lib")    /* link with Win64 GLUT lib */
#endif //_WIN32

#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "GL/freeglut.h"

class Bitmap
{
public:
	unsigned char *pixels; // 指向数据的内存区域
	int col, row; // 宽和高

	/* 构造函数，初始化 */
	Bitmap(int width, int height)
	{
		Bitmap **bitmap = get_bitmap_ptr();
		*bitmap = this;
		pixels = (unsigned char*)malloc(width * height * 4 * sizeof(unsigned char));
		memset(pixels, 0, width * height * 4 * sizeof(unsigned char));
		col = width;
		row = height;
	}

	/* 析构函数 */
	~Bitmap()
	{
		delete[] pixels;
	}
	/* 图像内存首地址*/
	unsigned char* get_ptr(void) const   
	{ 
		return pixels; 
	}

	/* 显示初始化 */
	void DisplayInit()
	{
		int numInit = 1;
		char* InitDummy = "";
		glutInit(&numInit, &InitDummy); // 初始化
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // 双缓冲缓冲，RGBA格式
		glutInitWindowPosition(1, 1); // 窗口起始位置，相对显示器的左上角位置
		glutInitWindowSize(col, row); // 窗口初始大小
		glutCreateWindow("bitmap"); // 创建窗口
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	}

	/* 显示更新 */
	void Imshow()
	{
		glutDisplayFunc(Display); // 显示
		glutMainLoopEvent(); // 使用glutMainLoop() 将不会退出
		glutPostRedisplay(); // 刷新
	}

private:
	// static method used for glut callbacks
	static Bitmap** get_bitmap_ptr(void)
	{
		static Bitmap *gBitmap;
		return &gBitmap;
	}

	/* 显示函数 */
	static void Display(void)
	{
		Bitmap *bitmap = *(get_bitmap_ptr());
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(bitmap->col, bitmap->row, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->pixels);
		glFlush();
		glutSwapBuffers(); // 双缓冲缓存
	}
};

#endif  // __BITMAP_H__
