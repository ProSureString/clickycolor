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
 
	while (true) {
		COLORREF c = GetPixelColor(p.x - 20, p.y);
		std::cout << "Pixel at (" << p.x << ", " << p.y << ") -> " << "R: " << (int)GetRValue(c) << " G: " << (int)GetGValue(c) << " B: " << (int)GetBValue(c) << std::endl;
	}
}