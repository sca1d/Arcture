#pragma once

#include "deflate.h"
#include "defstrct.h"
#include "control.h"
#include "builder.h"

extern "C" NTSTATUS WPCloop();

void(*_createFunc)(arc::Builder* builder);
void(*_destroyFunc)(void);
void(*_paintFunc)(HDC* hdcp, PAINTSTRUCT* psp);
void(*_mouseDownFunc)(int x, int y, int input);
void(*_mouseDBClickFunc)(int x, int y, int input);
void(*_mouseUpFunc)(int x, int y, int input);

namespace arc {

	ITable table;

	ControlInfoArray Controls;
	int ControlNum = 0;

	class GUI {

	private:
		HWND hWnd;
		HICON icon = NULL, hicon = NULL;
		HBRUSH bg = (HBRUSH)GetStockObject(BLACK_BRUSH);
		LPCSTR menu_name = NULL;
		LPCSTR classname = (LPCSTR)"winclass";

		char WindowName[0xFF];

		HWND	Parent = NULL;
		HMENU	Menu = NULL;

		DWORD	style = WS_OVERLAPPEDWINDOW;

		int x = CW_USEDEFAULT,
			y = CW_USEDEFAULT,
			w = CW_USEDEFAULT,
			h = CW_USEDEFAULT;

		MSG msg;
		
		static ARC_Control* CtrlInId(int id) {

			for (int i = 0; i < ControlNum; i++) {

				if (Controls.c[i].ID() == id) {
					return &Controls.c[i];
				}

			}

			return nullptr;

		}

		ATOM Init(WNDPROC wproc) {

			WNDCLASSEX w;

			w.cbSize = sizeof(WNDCLASSEX);
			w.style = CS_HREDRAW | CS_VREDRAW;
			w.lpfnWndProc = wproc;
			w.cbClsExtra = 0;
			w.cbWndExtra = 0;
			w.hInstance = table.hInst;
			w.hIcon = icon;
			w.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
			w.hbrBackground = bg;
			w.lpszMenuName = menu_name;
			w.lpszClassName = classname;
			w.hIconSm = hicon;

			return (RegisterClassEx(&w));

		}

		BOOL MakeWindow(void) {

			int _w = w,
				_h = h;

			if (_w != CW_USEDEFAULT) _w += x;
			if (_h != CW_USEDEFAULT) _h += y;

			hWnd = CreateWindow(
				classname,
				WindowName,
				style,
				x,
				y,
				_w,
				_h,
				Parent,
				Menu,
				table.hInst,
				NULL
			);

			if (!hWnd) return FALSE;

			ShowWindow(hWnd, table.cmdshow);
			UpdateWindow(hWnd);

			return TRUE;

		}

		static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wp, LPARAM _lp) {

			HDC hdc;
			static int x, y;
			Builder builder(_hWnd, &table, &Controls, &ControlNum);
			ARC_Control* control;

			switch (_msg) {

			case WM_CREATE:
				if (_createFunc != nullptr)	_createFunc(&builder);
				break;

			case WM_COMMAND:
				if (ControlNum > 0) {
					control = CtrlInId(LOWORD(_wp));
					if (control != nullptr && control->Click != nullptr) {
						control->Click();
					}
					/*
					for (int i = 0; i < ControlNum; i++) {

						if (Controls.c[i].id == LOWORD(_wp) && Controls.c[i].Click != nullptr) {
							Controls.c[i].Click();
						}

					}
					*/
				}
				break;

			case WM_CTLCOLORBTN:
			case WM_CTLCOLORSTATIC:

				hdc = (HDC)_wp;
				
				break;

			case WM_DESTROY:
				if (_destroyFunc != nullptr) _destroyFunc();
				PostQuitMessage(0);
				break;

			case WM_PAINT:
				PAINTSTRUCT ps;
				hdc = BeginPaint(_hWnd, &ps);
				if (_paintFunc != nullptr) _paintFunc(&hdc, &ps);
				EndPaint(_hWnd, &ps);
				break;

			#pragma region buttons
			case WM_LBUTTONDBLCLK:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseDBClickFunc != nullptr) _mouseDBClickFunc(x, y, ARC_LEFT_BUTTON);
				break;
			case WM_MBUTTONDBLCLK:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseDBClickFunc != nullptr) _mouseDBClickFunc(x, y, ARC_MIDDLE_BUTTON);
				break;
			case WM_RBUTTONDBLCLK:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseDBClickFunc != nullptr) _mouseDBClickFunc(x, y, ARC_RIGHT_BUTTON);
				break;

			case WM_LBUTTONUP:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseUpFunc != nullptr) _mouseUpFunc(x, y, ARC_LEFT_BUTTON);
				break;
			case WM_MBUTTONUP:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseUpFunc != nullptr) _mouseUpFunc(x, y, ARC_MIDDLE_BUTTON);
				break;
			case WM_RBUTTONUP:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseUpFunc != nullptr) _mouseUpFunc(x, y, ARC_RIGHT_BUTTON);
				break;

			case WM_LBUTTONDOWN:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseDownFunc != nullptr) _mouseDownFunc(x, y, ARC_LEFT_BUTTON);
				break;
			case WM_MBUTTONDOWN:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseDownFunc != nullptr) _mouseDownFunc(x, y, ARC_MIDDLE_BUTTON);
				break;
			case WM_RBUTTONDOWN:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				if (_mouseDownFunc != nullptr) _mouseDownFunc(x, y, ARC_RIGHT_BUTTON);
				//InvalidateRect(_hWnd, NULL, TRUE);
				break;
			#pragma endregion

			default:
				return (DefWindowProc(_hWnd, _msg, _wp, _lp));

			}

			return 0;

		}

	public:
		GUI(ITable t, LRESULT (*wProc)(HWND, UINT, WPARAM, LPARAM) = nullptr) {

			table = t;

			ATOM ret;

			if (wProc != nullptr)	ret = Init(wProc);
			else					ret = Init(WndProc);

			if (!ret) throw;

		}
		GUI(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow, LRESULT(*wProc)(HWND, UINT, WPARAM, LPARAM) = nullptr) {

			table = { hCurInst, hPrevInst, lpsCmdLine, nCmdShow };

			ATOM ret;

			if (wProc != nullptr)	ret = Init(wProc);
			else					ret = Init(WndProc);

			if (!ret) throw;

		}

		~GUI(void) {

		}

		#pragma region setups

		template <typename S>
		void SetWindowName(S name) {

			sprintf_s(WindowName, 0xFF, "%s", name);

		}

		void SetWindowPositionDefault(void) {

			x = CW_USEDEFAULT;
			y = CW_USEDEFAULT;

		}

		template <typename P>
		void SetWindowPosition(P p) {

			x = static_cast<int>(p.x);
			y = static_cast<int>(p.y);

		}
		template <typename T>
		void SetWindowPosition(T _x, T _y) {

			x = static_cast<int>(_x);
			y = static_cast<int>(_y);

		}

		void SetWindowSizeDefault(void) {

			w = CW_USEDEFAULT;
			h = CW_USEDEFAULT;

		}

		template <typename S>
		void SetWindowSize(S s) {

			w = static_cast<int>(s.width);
			h = static_cast<int>(s.height);

		}

		template <typename T>
		void SetWindowSize(T width, T height) {

			w = static_cast<int>(width);
			h = static_cast<int>(height);

		}

		void SetWindowStyle(DWORD _style) {

			style = _style;

		}

		void AddWindowStyle(DWORD _style) {

			style |= _style;
		}

		void SetParentWindow(HWND hWnd) {

			Parent = hWnd;

		}

		void SetMenu(HMENU hMenu) {

			Menu = hMenu;

		}

		#pragma endregion

		#pragma region events

		void CreateFunc(void(*_create)(Builder* builder)) {

			_createFunc = _create;

		}

		void DestroyFunc(void(*_destroy)(void)) {

			_destroyFunc = _destroy;

		}

		void PaintFunc(void(*_paint)(HDC* hdcp, PAINTSTRUCT* psp)) {

			_paintFunc = _paint;

		}

		void MouseDownFunc(void(*_mouseDown)(int x, int y, int input)) {

			_mouseDownFunc = _mouseDown;

		}

		void MouseDBClickFunc(void(*_mouseDBClick)(int x, int y, int input)) {

			_mouseDBClickFunc = _mouseDBClick;

		}

		void MouseUpFunc(void(*_mouseUp)(int x, int y, int input)) {

			_mouseUpFunc = _mouseUp;

		}

		#pragma endregion

		#pragma region getter

		HWND GetHandle(void) {

			return hWnd;

		}

		HWND GetParentHandle(void) {

			return Parent;

		}

		HICON GetIcon(void) {

			return icon;

		}

		HICON GetIconSM(void) {

			return hicon;

		}

		#pragma endregion

		void Redraw(void) {

			InvalidateRect(hWnd, NULL, TRUE);

		}

		void WindowLoop(void) {

			MakeWindow();

			BOOL ret;

			while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0) {
			
				if (ret == -1) break;
				else {

					TranslateMessage(&msg);
					DispatchMessage(&msg);

				}

			}

		}

	};

}