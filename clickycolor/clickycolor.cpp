#include <Windows.h>
#include <iostream>
#include <cmath>



bool isWithinRange(int value, int target, int range) 
{
	return std::abs(value - target) <= range;
}

bool isYellowOrOrange(COLORREF c) 
{
	int r = GetRValue(c);
	int g = GetGValue(c);
	int b = GetBValue(c);

	int brightness = (r + g + b) / 3;

	bool warmTone(r > g * 0.8 && r > b * 1.2);


	bool yellowish = (r > 180 && g > 140 && b < 120);
	bool orangish = (r > 120 && g > 60 && b < 80);


	bool darkYellow = (brightness > 40 && brightness < 140 && r > g && g > b);

	return (warmTone && (yellowish || orangish || darkYellow));
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
		p.y += 8;

		COLORREF c = GetPixelColor(p.x, p.y);
		std::cout << "Pixel at (" << p.x << ", " << p.y << ") -> " << "R: " << (int)GetRValue(c) << " G: " << (int)GetGValue(c) << " B: " << (int)GetBValue(c) << std::endl;
		std::cout << "Color check: " << (isYellowOrOrange(c) ? "Match!" : "No match.") << std::endl;
	}
}