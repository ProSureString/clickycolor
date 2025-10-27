#include <Windows.h>
#include <iostream>
#include <cmath>

int rad = 1;
int ox = -4;
int oy = 4;
bool active = false;

void LeftClick() {
	INPUT in[2] = {};
	in[0].type = INPUT_MOUSE;
	in[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	in[1] = in[0];
	in[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(2, in, sizeof(INPUT));
}

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

COLORREF getPixelColor(int x, int y, HDC hdc)
{
	COLORREF color = GetPixel(hdc, x, y);

	return color;
}

bool checkAreaForColor(int x, int y, int rad, HDC hdc)
{
    for (int dx = -rad; dx <= rad; dx++) {
        for (int dy = -rad; dy <= rad; dy++) {
			COLORREF c = GetPixel(hdc, x + dx, y + dy);
			if (isYellowOrOrange(c)) {
				return true;
			}
		}
	}
	return false;
}

int main()
{
	//int screenX = GetSystemMetrics(SM_CXSCREEN) / 2;
	//int screenY = GetSystemMetrics(SM_CYSCREEN) / 2;
	RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 'B');

	HDC hdc = GetDC(NULL);


	MSG msg = { 0 };
	while (true) {

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_HOTKEY) {
				active = !active, std::cout << "toggled : " << (active ? "ON" : "OFF") << "\n";
			}
		}
		if (active) {
			POINT p;
			GetCursorPos(&p);

			p.x += ox;
			p.y += oy;



			COLORREF c = getPixelColor(p.x, p.y, hdc);
			//std::cout << "Pixel at (" << p.x << ", " << p.y << ") -> " << "R: " << (int)GetRValue(c) << " G: " << (int)GetGValue(c) << " B: " << (int)GetBValue(c) << std::endl;
			//std::cout << "Color check: " << (isYellowOrOrange(c) ? "Match!" : "No match.") << std::endl;
		
			if (isYellowOrOrange(getPixelColor(p.x, p.y, hdc))) {
				LeftClick();
				std::cout << "match" << std::endl;
			}
		}
	}

	ReleaseDC(NULL, hdc);
	return 0;
}