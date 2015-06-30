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
	unsigned char *pixels; // ָ�����ݵ��ڴ�����
	int col, row; // ��͸�

	/* ���캯������ʼ�� */
	Bitmap(int width, int height)
	{
		Bitmap **bitmap = get_bitmap_ptr();
		*bitmap = this;
		pixels = (unsigned char*)malloc(width * height * 4 * sizeof(unsigned char));
		memset(pixels, 0, width * height * 4 * sizeof(unsigned char));
		col = width;
		row = height;
	}

	/* �������� */
	~Bitmap()
	{
		delete[] pixels;
	}
	/* ͼ���ڴ��׵�ַ*/
	unsigned char* get_ptr(void) const   
	{ 
		return pixels; 
	}

	/* ��ʾ��ʼ�� */
	void DisplayInit()
	{
		int numInit = 1;
		char* InitDummy = "";
		glutInit(&numInit, &InitDummy); // ��ʼ��
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // ˫���建�壬RGBA��ʽ
		glutInitWindowPosition(1, 1); // ������ʼλ�ã������ʾ�������Ͻ�λ��
		glutInitWindowSize(col, row); // ���ڳ�ʼ��С
		glutCreateWindow("bitmap"); // ��������
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	}

	/* ��ʾ���� */
	void Imshow()
	{
		glutDisplayFunc(Display); // ��ʾ
		glutMainLoopEvent(); // ʹ��glutMainLoop() �������˳�
		glutPostRedisplay(); // ˢ��
	}

private:
	// static method used for glut callbacks
	static Bitmap** get_bitmap_ptr(void)
	{
		static Bitmap *gBitmap;
		return &gBitmap;
	}

	/* ��ʾ���� */
	static void Display(void)
	{
		Bitmap *bitmap = *(get_bitmap_ptr());
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(bitmap->col, bitmap->row, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->pixels);
		glFlush();
		glutSwapBuffers(); // ˫���建��
	}
};

#endif  // __BITMAP_H__
