#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Arcture.h"

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) {

	arc::GUI gui(hCurInst, hPrevInst, lpsCmdLine, nCmdShow);

	gui.SetWindowName("Test Window");
	gui.SetWindowPosition(30, 50);
	gui.SetWindowSize(900, 400);

	gui.WindowLoop();

}