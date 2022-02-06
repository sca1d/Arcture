#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <functional>
#include <string>

#define DLL_EXPORT __declspec(dllexport)

struct _ITable {

public:

	HINSTANCE	cur;
	HINSTANCE	prev;
	LPSTR		cmdline;
	int			cmdshow;

	/*
	_ITable(HINSTANCE _cur, HINSTANCE _prev, LPSTR _cmdline, int _cmdshow) {
		cur = _cur;
		prev = _prev;
		cmdline = _cmdline;
		cmdshow = _cmdshow;
	}
	*/

};

typedef _ITable ITable;

typedef struct {
	int x;
	int y;
}Point;

typedef struct {
	float x;
	float y;
}PointF;

typedef struct {
	double x;
	double y;
}PointD;

typedef struct {
	int width;
	int height;
}Size;

typedef struct {
	float width;
	float height;
}SizeF;

typedef struct {
	double width;
	double height;
}SizeD;

namespace arc {

	class GUI {

	private:
		HWND hWnd;
		ITable table;
		HICON icon = NULL, hicon = NULL;
		HBRUSH bg = (HBRUSH)GetStockObject(BLACK_BRUSH);
		LPCSTR menu_name = NULL;
		LPCSTR classname = (LPCSTR)"winclass";

		char WindowName[0xFF];

		HWND	Parent = NULL;
		HMENU	Menu = NULL;

		int x = CW_USEDEFAULT,
			y = CW_USEDEFAULT,
			w = CW_USEDEFAULT,
			h = CW_USEDEFAULT;

		MSG msg;

		ATOM Init(WNDPROC wproc) {

			WNDCLASSEX w;

			w.cbSize = sizeof(WNDCLASSEX);
			w.style = CS_HREDRAW | CS_VREDRAW;
			w.lpfnWndProc = wproc;
			w.cbClsExtra = 0;
			w.cbWndExtra = 0;
			w.hInstance = table.cur;
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
				WS_OVERLAPPEDWINDOW,
				x,
				y,
				_w,
				_h,
				Parent,
				Menu,
				table.cur,
				NULL
			);

			if (!hWnd) return FALSE;

			ShowWindow(hWnd, table.cmdshow);
			UpdateWindow(hWnd);

			return TRUE;

		}

		static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wp, LPARAM _lp) {

			switch (_msg) {
			case WM_CREATE:
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_PAINT:
				break;
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

		void SetParentWindow(HWND hWnd) {

			Parent = hWnd;

		}

		void SetMenu(HMENU hMenu) {

			Menu = hMenu;

		}

		#pragma endregion

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