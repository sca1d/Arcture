#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Arcture.h"

//using namespace arc;

void Paint(HDC* hdcp, PAINTSTRUCT* psp) {

	TCHAR szText[] = TEXT("text sample.");

	FillRect(*hdcp, &psp->rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	TextOut(*hdcp, 0, 0, szText, lstrlen(szText));

}

void MouseDown(int x, int y) {

	printf("x:%d y:%d\n", x, y);

}

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) {

	arc::GUI gui(hCurInst, hPrevInst, lpsCmdLine, nCmdShow);

	gui.SetWindowName("Test Window");
	gui.SetWindowPosition(30, 50);
	gui.SetWindowSize(900, 400);
	gui.AddWindowStyle(WS_HSCROLL);

	gui.PaintFunc(Paint);
	gui.MouseDownFunc(MouseDown);

	gui.WindowLoop();

}