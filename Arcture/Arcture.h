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

namespace arc {

	class GUI {

	private:
		HWND hWnd;
		ITable table;
		HICON icon = NULL, hicon = NULL;
		HBRUSH bg = (HBRUSH)GetStockObject(BLACK_BRUSH);
		LPCSTR menu_name = NULL;
		LPCSTR classname = (LPCSTR)"winclass";

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

		BOOL WindowInit(const char* WindowName, HWND Parent = NULL, HMENU Menu = NULL) {

			hWnd = CreateWindow(
				classname,
				WindowName,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
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

		void WindowLoop(void) {

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