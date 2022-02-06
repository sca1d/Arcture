#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Arcture.h"

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) {

	arc::GUI gui(hCurInst, hPrevInst, lpsCmdLine, nCmdShow);
	gui.WindowInit("test");
	gui.WindowLoop();

}