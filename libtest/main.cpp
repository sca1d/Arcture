#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>

#include "Arcture.h"
#include "Diversity.h"

//using namespace arc;

void Paint(HDC* hdcp, PAINTSTRUCT* psp) {

	TCHAR szText[] = TEXT("text sample.");

	FillRect(*hdcp, &psp->rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	TextOut(*hdcp, 0, 0, szText, lstrlen(szText));

}

void MouseDown(int x, int y, int input) {

	switch (input) {
	case ARC_LEFT_BUTTON:
		printf("[mouse down] x:%d y:%d input:left\n", x, y);
		break;
	case ARC_MIDDLE_BUTTON:
		printf("[mouse down] x:%d y:%d input:middle\n", x, y);
		break;
	case ARC_RIGHT_BUTTON:
		printf("[mouse down] x:%d y:%d input:right\n", x, y);
		break;
	}
	//std::cout << "x:" << x << " y:" << y << "\n";

}

void MouseDBClick(int x, int y, int input) {

	switch (input) {
	case ARC_LEFT_BUTTON:
		printf("[mouse dbclick] x:%d y:%d input:left\n", x, y);
		break;
	case ARC_MIDDLE_BUTTON:
		printf("[mouse dbclick] x:%d y:%d input:middle\n", x, y);
		break;
	case ARC_RIGHT_BUTTON:
		printf("[mouse dbclick] x:%d y:%d input:right\n", x, y);
		break;
	}

}

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) {

	arc::ViewConsole();

	arc::GUI gui(hCurInst, hPrevInst, lpsCmdLine, nCmdShow);

	gui.SetWindowName("Test Window");
	gui.SetWindowPosition(30, 50);
	gui.SetWindowSize(900, 400);
	gui.AddWindowStyle(WS_HSCROLL);

	gui.PaintFunc(Paint);
	gui.MouseDownFunc(MouseDown);
	gui.MouseDBClickFunc(MouseDBClick);

	gui.WindowLoop();

}