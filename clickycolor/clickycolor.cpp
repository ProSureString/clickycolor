#include <Windows.h>
#include <iostream>
#include <cmath>

bool isWithinRange(int value, int target, int range) 
{
	return std::abs(value - target) <= range;
}

bool isYellowOrOrange(COLORREF c, int to1Yellow = 50, int to1Orange = 25) 
{
	int r = GetRValue(c);
	int g = GetGValue(c);
	int b = GetBValue(c);

	bool isYellow = isWithinRange(r, 255, to1Yellow) && isWithinRange(g, 255, to1Yellow) && isWithinRange(b, 0, to1Yellow);
	bool isOrange = isWithinRange(r, 255, to1Orange) && isWithinRange(g, 165, to1Orange) && isWithinRange(b, 0, to1Orange);

	return isYellow || isOrange;
}

COLORREF GetPixelColor(int x, int y)
{
	HDC hdc = GetDC(NULL);
	COLORREF color = GetPixel(hdc, x, y);
	ReleaseDC(NULL, hdc);

	return color;
}

int main()
{

 
	while (true) {
		POINT p;
		GetCursorPos(&p);

		p.x -= 8;
		p.y -= 8;

		COLORREF c = GetPixelColor(p.x, p.y);
		std::cout << "Pixel at (" << p.x << ", " << p.y << ") -> " << "R: " << (int)GetRValue(c) << " G: " << (int)GetGValue(c) << " B: " << (int)GetBValue(c) << std::endl;
		std::cout << "Color check: " << (isYellowOrOrange(c) ? "Match!" : "No match.") << std::endl;
	}
}