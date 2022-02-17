#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>

#include "resource.h"

#include "Arcture.h"
#include "Diversity.h"

#define ID_BUTTON	100
#define ID_RADIO	101
#define ID_CHECKBOX	102
#define ID_IMAGE	103
#define ID_TEXTBOX	104
#define ID_CUSTOM	105

//using namespace arc;
arc::ARC_RadioButtonControl* RadioButton;
arc::ARC_CheckboxControl* Checkbox;
arc::ARC_Control* TextBox;
arc::ARC_Control* CustomControl;

void Button_Click(void) {

	HFONT font = CreateFont(20, 0, 0, 0, 0, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		VARIABLE_PITCH | FF_DONTCARE, "HGs‘‘Ì");

	RadioButton->Checked(!RadioButton->Checked());
	
	Checkbox->Font(font);
	RadioButton->Font(Checkbox->Font());

	//TextBox.SetOnlyNumberMode();

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
void TextBox_Update(void) {

	printf("textbox update\n");

}
void Custom_Click(void) {

	printf("custom control clicked\n");

}

void Create(arc::Builder* builder) {

	builder->AddButton("button!!", arc::Point(10, 20), arc::Size(90, 30), ID_BUTTON, Button_Click);
	RadioButton = builder->AddAutoRadioButton("radio!", arc::Point(10, 60), arc::Size(90, 30), ID_RADIO, Radio_Click);
	Checkbox = builder->AddCheckBoxButton("checkbox!", arc::Point(10, 100), arc::Size(90, 30), ID_CHECKBOX, Checkbox_Click);
	builder->AddImageButton("image!", "button.jpg", arc::Point(10, 140), arc::Size(90, 30), ID_IMAGE, Image_Click);

	TextBox = builder->AddTextBox("text", arc::Point(10, 180), arc::Size(150, 50), ID_TEXTBOX);
	TextBox->Update = TextBox_Update;

	CustomControl = builder->AddCustomControl(arc::Point(10, 240), arc::Size(90, 30), ID_CUSTOM, Custom_Click);

}

void Paint(HDC* hdcp, PAINTSTRUCT* psp) {

	TCHAR szText[] = TEXT("text sample.");

	FillRect(*hdcp, &psp->rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	TextOut(*hdcp, 0, 0, szText, lstrlen(szText));

}

void DrawItem(LPDRAWITEMSTRUCT itemp) {

	if (itemp->hwndItem == CustomControl->hWnd()) {

		SetTextColor(itemp->hDC, RGB(100, 0, 100));
		const char* text = "Some static text";
		TextOut(itemp->hDC, itemp->rcItem.left, itemp->rcItem.top, text, ARRAY_SIZE(text));

	}

}

void Focused(HWND oldFocusedHandle) {

	char buff[256] = "";
	GetWindowText(oldFocusedHandle, buff, sizeof(buff));
	printf("%s\n", buff);

	printf("focused!!\n");

}

void OutFocus(HWND newFocusHandle) {

	char buff[256] = "";
	GetWindowText(newFocusHandle, buff, sizeof(buff));
	printf("%s\n", buff);

	printf("out focus\n");

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

void CharInput(char keycode) {

	printf("keycode:%c\n", keycode);

}

void KeyDown(int charset) {

	printf("Key Down:%c\n", charset);

}

void KeyUp(int charset) {

	printf("Key Up:%c\n", charset);

}

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) {

	arc::ViewConsole();

	arc::GUI gui(hCurInst, hPrevInst, lpsCmdLine, nCmdShow);

	arc::ITable table = gui.GetTable();

	gui.SetWindowName("Test Window");
	gui.SetWindowPosition(30, 50);
	gui.SetWindowSize(900, 400);
	gui.SetMenuItem(TEXT("IDR_MENU1"));
	gui.AddWindowStyle(WS_HSCROLL);

	gui.CreateFunc(Create);
	gui.PaintFunc(Paint);
	gui.DrawItemFunc(DrawItem);
	gui.FocuedFunc(Focused);
	gui.OutFocusFunc(OutFocus);
	gui.MouseDownFunc(MouseDown);
	gui.MouseDBClickFunc(MouseDBClick);
	gui.CharInput(CharInput);
	gui.KeyDown(KeyDown);
	gui.KeyUp(KeyUp);

	gui.WindowLoop();

}