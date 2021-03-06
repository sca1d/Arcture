#pragma once

#include "deflate.h"
#include "defstrct.h"
#include "control.h"
#include "builder.h"

extern "C" NTSTATUS WPCloop(int id, arc::ControlInfoArray* ctrls, int cnum);

void(*_createFunc)(arc::Builder* builder);
void(*_destroyFunc)(void);
void(*_paintFunc)(HDC* hdcp, PAINTSTRUCT* psp);
void(*_drawItemFunc)(LPDRAWITEMSTRUCT itemp);
void(*_focusedFunc)(HWND oldFocusHandle);
void(*_outFocusFunc)(HWND newFocusHandle);
void(*_mouseDownFunc)(int x, int y, int input);
void(*_mouseDBClickFunc)(int x, int y, int input);
void(*_mouseUpFunc)(int x, int y, int input);
void(*_charFunc)(char keycode);
void(*_keyDownFunc)(int charset);
void(*_keyUpFunc)(int charset);

namespace arc {

	ITable table;

	ControlInfoArray Controls;
	int ControlNum = 0;

	//@brief UI・GUI・ウィンドウ生成クラス
	class GUI {

	private:
		HWND hWnd;
		HICON icon = NULL, hicon = NULL;
		HBRUSH bg = (HBRUSH)GetStockObject(BLACK_BRUSH);
		LPCSTR classname = (LPCSTR)"winclass";

		char WindowName[0xFF];

		HWND	Parent = NULL;
		
		LPCSTR	MenuSTR	= NULL;
		HMENU	Menu	= NULL;

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
			w.lpszMenuName = MenuSTR;
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
					if (control != nullptr) {

						if (control->Click != nullptr) control->Click();

						switch (HIWORD(_wp)) {
						case EN_UPDATE:
							if (control->Update != nullptr) control->Update();
							break;
						}

					}

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

			case WM_DRAWITEM:
				if (_drawItemFunc != nullptr) _drawItemFunc((LPDRAWITEMSTRUCT)_lp);
				break;

			case WM_SETFOCUS:
				if (_focusedFunc != nullptr) _focusedFunc((HWND)_wp);
				break;

			case WM_KILLFOCUS:
				if (_outFocusFunc != nullptr) _outFocusFunc((HWND)_wp);
				break;

			#pragma region buttons
			case WM_LBUTTONDBLCLK:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseDBClickFunc != nullptr) _mouseDBClickFunc(x, y, ARC_LEFT_BUTTON);
				break;
			case WM_MBUTTONDBLCLK:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseDBClickFunc != nullptr) _mouseDBClickFunc(x, y, ARC_MIDDLE_BUTTON);
				break;
			case WM_RBUTTONDBLCLK:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseDBClickFunc != nullptr) _mouseDBClickFunc(x, y, ARC_RIGHT_BUTTON);
				break;

			case WM_LBUTTONUP:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseUpFunc != nullptr) _mouseUpFunc(x, y, ARC_LEFT_BUTTON);
				break;
			case WM_MBUTTONUP:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseUpFunc != nullptr) _mouseUpFunc(x, y, ARC_MIDDLE_BUTTON);
				break;
			case WM_RBUTTONUP:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseUpFunc != nullptr) _mouseUpFunc(x, y, ARC_RIGHT_BUTTON);
				break;

			case WM_LBUTTONDOWN:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseDownFunc != nullptr) _mouseDownFunc(x, y, ARC_LEFT_BUTTON);
				break;
			case WM_MBUTTONDOWN:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseDownFunc != nullptr) _mouseDownFunc(x, y, ARC_MIDDLE_BUTTON);
				break;
			case WM_RBUTTONDOWN:
				y = HIWORD(_lp);
				x = LOWORD(_lp);
				SetFocus(_hWnd);
				if (_mouseDownFunc != nullptr) _mouseDownFunc(x, y, ARC_RIGHT_BUTTON);
				//InvalidateRect(_hWnd, NULL, TRUE);
				break;
			#pragma endregion

			#pragma region keyinput
			
			case WM_CHAR:
				if (_charFunc != nullptr) _charFunc(_wp);
				break;

			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
				if (_keyDownFunc != nullptr) _keyDownFunc(_wp);
				break;

			case WM_SYSKEYUP:
			case WM_KEYUP:
				if (_keyUpFunc != nullptr) _keyUpFunc(_wp);
				break;


			#pragma endregion

			default:
				return (DefWindowProc(_hWnd, _msg, _wp, _lp));

			}

			return 0;

		}

	public:
		/*
		@param t:		インスタンスデータテーブル
		@param wProc:	独自で WndProc 関数を使用したい場合に設定
		*/
		GUI(ITable t, LRESULT (*wProc)(HWND, UINT, WPARAM, LPARAM) = nullptr) {

			table = t;

			ATOM ret;

			if (wProc != nullptr)	ret = Init(wProc);
			else					ret = Init(WndProc);

			if (!ret) throw;

		}
		/*
		@param hCurInst:	インスタンスハンドル
		@param hPrevInst:	Win16のインスタンス ※Win32では常にNULL
		@param lpsCmdLine:	コマンドライン
		@param nCmdShow:	アプリケーション初期表示設定
		@param wProc:		独自で WndProc 関数を使用したい場合に設定
		*/
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

		//@brief ウィンドウタイトル を設定
		template <typename S>
		void SetWindowName(S name) {

			sprintf_s(WindowName, 0xFF, "%s", name);

		}

		//@brief ウィンドウ生成時の 表示位置 を 内部初期値 に設定
		void SetWindowPositionDefault(void) {

			x = CW_USEDEFAULT;
			y = CW_USEDEFAULT;

		}

		//@brief ウィンドウ生成時の 表示位置 を設定
		template <typename P>
		void SetWindowPosition(P p) {

			x = static_cast<int>(p.x);
			y = static_cast<int>(p.y);

		}
		//@brief ウィンドウ生成時の 表示位置 を設定
		template <typename T>
		void SetWindowPosition(T _x, T _y) {

			x = static_cast<int>(_x);
			y = static_cast<int>(_y);

		}

		//@brief ウィンドウ生成時の 表示サイズ を 内部初期値 に設定
		void SetWindowSizeDefault(void) {

			w = CW_USEDEFAULT;
			h = CW_USEDEFAULT;

		}

		//@brief ウィンドウ生成時の 表示サイズ を設定
		template <typename S>
		void SetWindowSize(S s) {

			w = static_cast<int>(s.width);
			h = static_cast<int>(s.height);

		}

		//@brief ウィンドウ生成時の 表示サイズ を設定
		template <typename T>
		void SetWindowSize(T width, T height) {

			w = static_cast<int>(width);
			h = static_cast<int>(height);

		}

		//@brief ウィンドウスタイル を設定
		void SetWindowStyle(DWORD _style) {

			style = _style;

		}

		//@brief ウィンドウスタイル を追加設定
		void AddWindowStyle(DWORD _style) {

			style |= _style;
		}

		//@brief 親ウィンドウ を設定
		void SetParentWindow(HWND hWnd) {

			Parent = hWnd;

		}

		//@brief ウィンドウメニュー を設定
		void SetMenuItem(LPCSTR menuId) {

			MenuSTR	= menuId;
			Menu	= LoadMenu(table.hInst, menuId);
			if (Menu != NULL) printf("menu handle is not null\n");
			SetMenu(hWnd, Menu);

		}

		#pragma endregion

		#pragma region events

		//@brief ウィンドウ生成イベント を設定
		void CreateFunc(void(*_create)(Builder* builder)) {

			_createFunc = _create;

		}

		//@brief ウィンドウ破棄イベント を設定
		void DestroyFunc(void(*_destroy)(void)) {

			_destroyFunc = _destroy;

		}

		//@brief 描画イベント を設定
		void PaintFunc(void(*_paint)(HDC* hdcp, PAINTSTRUCT* psp)) {

			_paintFunc = _paint;

		}

		//@brief オーナードローイベント を設定
		void DrawItemFunc(void(*_drawItem)(LPDRAWITEMSTRUCT itemp)) {

			_drawItemFunc = _drawItem;

		}

		//@brief フォーカスイベント を設定
		void FocuedFunc(void(*_focused)(HWND oldFocusedHandle)) {

			_focusedFunc = _focused;

		}

		//@brief アンフォーカスイベント を設定
		void OutFocusFunc(void(*_outFocus)(HWND newFocusHandle)) {

			_outFocusFunc = _outFocus;

		}

		//@brief マウスダウンイベント を設定
		void MouseDownFunc(void(*_mouseDown)(int x, int y, int input)) {

			_mouseDownFunc = _mouseDown;

		}

		//@brief マウスダブルクリックイベント を設定
		void MouseDBClickFunc(void(*_mouseDBClick)(int x, int y, int input)) {

			_mouseDBClickFunc = _mouseDBClick;

		}

		//@brief マウスアップイベント を設定
		void MouseUpFunc(void(*_mouseUp)(int x, int y, int input)) {

			_mouseUpFunc = _mouseUp;

		}

		//@brief キー入力イベント を設定
		void CharInput(void(*_keyInput)(char keycode)) {

			_charFunc = _keyInput;

		}

		//@brief キーダウンイベント を設定
		void KeyDown(void(*_keyDown)(int charset)) {

			_keyDownFunc = _keyDown;

		}

		//@brief キーアップイベント を設定
		void KeyUp(void(*_keyUp)(int charset)) {

			_keyUpFunc = _keyUp;

		}

		#pragma endregion

		#pragma region getter

		//@brief ウィンドウハンドル を取得
		HWND GetHandle(void) {

			return hWnd;

		}

		//@brief 親ウィンドウハンドル を取得
		HWND GetParentHandle(void) {

			return Parent;

		}

		//@brief インスタンステーブル を取得
		ITable GetTable(void) {

			return table;

		}

		//@brief アイコン を取得
		HICON GetIcon(void) {

			return icon;

		}

		//@brief スモールアイコン を取得
		HICON GetIconSM(void) {

			return hicon;

		}

		#pragma endregion

		//@brief ウィンドウに 再描画命令 を送信
		void Redraw(void) {

			InvalidateRect(hWnd, NULL, TRUE);

		}

		//@brief メインループ
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