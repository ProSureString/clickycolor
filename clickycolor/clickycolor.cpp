#include <Windows.h>
#include <iostream>

COLORREF GetPixelColor(int x, int y)
{
	HDC hdcScreen = GetDC(NULL);
	COLORREF color = GetPixel(hdcScreen, x, y);
	ReleaseDC(NULL, hdcScreen);

	return color;
}

int main()
{
	POINT p;
	GetCursorPos(&p);
 
	COLORREF c = GetPixelColor(p.x, p.y);

	std::cout << "Pixel at (" << p.x << ", " << p.y << ") -> " << "R: " << (int)GetRValue(c) << " G: " << (int)GetGValue(c) << " B: " << (int)GetBValue(c) << std::endl;
}