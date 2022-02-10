#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>

#include "Arcture.h"
#include "Diversity.h"

#define ID_BUTTON	100
#define ID_RADIO	101
#define ID_CHECKBOX	102
#define ID_IMAGE	103

//using namespace arc;
arc::ARC_RadioButtonControl RadioButton;
arc::ARC_CheckboxControl Checkbox;

void Button_Click(void) {

	HFONT font = CreateFont(20, 0, 0, 0, 0, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		VARIABLE_PITCH | FF_DONTCARE, "HGs‘‘Ì");

	RadioButton.Checked(!RadioButton.Checked());
	
	Checkbox.Font(font);
	RadioButton.Font(Checkbox.Font());


	printf("Clicked!!\n");

}
void Radio_Click(void) {

	printf("radio!\n");

}
void Checkbox_Click(void) {

	printf("checkbox!\n");

}
void Image_Click(void) {

	printf("image!\n");

}

void Create(arc::Builder* builder) {

	builder->AddButton("button!!", arc::Point(10, 20), arc::Size(90, 30), ID_BUTTON, Button_Click);
	RadioButton = builder->AddAutoRadioButton("radio!", arc::Point(10, 60), arc::Size(90, 30), ID_RADIO, Radio_Click);
	Checkbox = builder->AddCheckBoxButton("checkbox!", arc::Point(10, 100), arc::Size(90, 30), ID_CHECKBOX, Checkbox_Click);
	builder->AddImageButton("image!", "button.jpg", arc::Point(10, 140), arc::Size(90, 30), ID_IMAGE, Image_Click);

}

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

	gui.CreateFunc(Create);
	gui.PaintFunc(Paint);
	gui.MouseDownFunc(MouseDown);
	gui.MouseDBClickFunc(MouseDBClick);

	gui.WindowLoop();

}