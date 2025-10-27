#include <Windows.h>
#include <iostream>

HDC GetScreenDC()
{
	return GetDC(NULL);
}

void ReleeaseScreenDC(HDC hdc)
{
	ReleaseDC(NULL, hdc);
}

COLORREF GetPixelColor(int x, int y, HDC hdc)
{
	COLORREF color = GetPixel(hdc, x, y);

	return color;
}

int main()
{
	POINT p;
	GetCursorPos(&p);
 
	HDC hdc = GetScreenDC();

	while (true) {
		COLORREF c = GetPixelColor(p.x, p.y, hdc);
		std::cout << "Pixel at (" << p.x << ", " << p.y << ") -> " << "R: " << (int)GetRValue(c) << " G: " << (int)GetGValue(c) << " B: " << (int)GetBValue(c) << std::endl;
	}


	ReleeaseScreenDC(hdc);

}