#include <iostream>
#include <Windows.h>

#include "Bitmap.h"

using std::cout;
using std::endl;

void SetPixl(unsigned char ptr[], int offset, int type)
{
	ptr[offset*4 + 3] = 255;

	switch (type)
	{
	case 0:
		ptr[offset*4 + 0] = 255;
		break;
	case 1:
		ptr[offset*4 + 1] = 255;
		break;
	case 2:
		ptr[offset*4 + 2] = 255;
		break;
	case 3:
		ptr[offset*4 + 0] = 255;
		ptr[offset*4 + 1] = 255;
		break;
	case 4:
		ptr[offset*4 + 0] = 255;
		ptr[offset*4 + 2] = 255;
		break;
	case 5:
		ptr[offset*4 + 1] = 255;
		ptr[offset*4 + 2] = 255;
		break;
	others:
		ptr[offset*4 + 0] = 255;
		ptr[offset*4 + 1] = 255;
		ptr[offset*4 + 2] = 255;
	}
}
int main()
{
	int col = 512;
	int row = 512;

	int N = 256;

	Bitmap bitmap(col, row);
	unsigned char *ptr = bitmap.get_ptr();
	bitmap.DisplayInit(); // ³õÊ¼»¯

	int color = 0;
	for (int len = 128; len > 32; len = len - 16)
	{
		for (int i = 0; i < len * 2; i++)
		{
			int offset = (256 - len) * col + i + (256 - len);
			SetPixl(ptr, offset, color % 6);
			bitmap.Imshow();
		}
		color++;
		for (int i = 0; i < len * 2; i++)
		{
			int offset = ((256 - len) + i) * col + (256 + len);
			SetPixl(ptr, offset, color % 6);
			bitmap.Imshow();
		}
		color++;
		for (int i = 0; i < len * 2; i++)
		{
			int offset = (256 + len) * col + (256 + len) - i;
			SetPixl(ptr, offset, color % 6);
			bitmap.Imshow();
		}
		color++;
		for (int i = 0; i < len * 2; i++)
		{
			int offset = ((256 + len) - i) * col + (256 - len);
			SetPixl(ptr, offset, color % 6);
			bitmap.Imshow();
		}
		color++;
	}
}