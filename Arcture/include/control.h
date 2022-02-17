#pragma once

#include "defstrct.h"

#define _IMP_CHECKED(__hwnd)										\
	BOOL Checked(BOOL value = ARC_NULL) {							\
																	\
		if (value != ARC_NULL) {									\
			SendMessage(__hwnd, BM_SETCHECK, value, 0);				\
			return value;											\
		}															\
		else {														\
			return SendMessage(__hwnd, BM_GETCHECK, NULL, NULL);	\
		}															\
																	\
	}

namespace arc {

	class ARC_Control {

	protected:

		int		_id;
		HWND	_hwnd, _parent;
		Point	_location;
		Size	_size;
		ARC_RGB	bcolor;

	public:

		void(*Update)(void);
		void(*Click)(void);

		ARC_Control(void) {



		}
		ARC_Control(int id_, HWND hwnd_, HWND parent_, Point loc_, Size size_, void(*_click)(void) = nullptr) {

			this->_id = id_;
			this->_hwnd = hwnd_;
			this->_parent = parent_;
			this->_location = loc_;
			this->_size = size_;
			this->Click = _click;

		}

		void Focus(void) {

			SetFocus(this->_hwnd);

		}

		int ID(void) {

			return _id;

		}

		HWND hWnd(void) {

			return _hwnd;

		}

		HWND Parent(void) {

			return _parent;

		}

		Point Location(void) {

			return _location;

		}

		Size Size(void) {

			return _size;

		}

		BOOL Enable(BOOL value = ARC_NULL) {

			if (value != ARC_NULL) {
				return ARC_SET_ENABLE(_hwnd, value);
			}
			else {
				return ARC_GET_ENABLE(_hwnd);
			}

		}

		HFONT Font(HFONT value = nullptr) {

			if (value != nullptr) {
				SendMessage(_hwnd, WM_SETFONT, (LPARAM)value, true);
				return value;
			}
			else {
				return reinterpret_cast<HFONT>(SendMessage(_hwnd, WM_GETFONT, 0, 0));
			}

		}

		ARC_RGB BackColor(ARC_RGB value = ARC_NULL) {

			if (value.IsNull()) {
				bcolor = value;
				InvalidateRect(_hwnd, NULL, TRUE);
				return value;
			}
			else {
				return bcolor;
			}

		}

	};

	typedef struct { ARC_Control c[0xFF]; }ControlInfoArray;

	#pragma region buttons

	class ARC_ButtonControl : public ARC_Control {

	private:

		ARC_RGB	tcolor;

	public:

		using ARC_Control::ARC_Control;

		ARC_RGB TextColor(ARC_RGB value = ARC_NULL) {

			if (value.IsNull()) {
				tcolor = value;
				InvalidateRect(hWnd(), NULL, TRUE);
				return value;
			}
			else {
				return tcolor;
			}

		}

	};

	class ARC_RadioButtonControl : public ARC_ButtonControl {

	public:

		using ARC_ButtonControl::ARC_ButtonControl;

		_IMP_CHECKED(hWnd())

	};

	class ARC_CheckboxControl : public ARC_ButtonControl {

	public:

		using ARC_ButtonControl::ARC_ButtonControl;

		_IMP_CHECKED(hWnd());

	};

	#pragma endregion

	class ARC_TextBoxControl : public ARC_Control {

	private:

		char* _text;

	public:

		using ARC_Control::ARC_Control;

		void SetMultiLineMode(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_MULTILINE);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

		void SetScrollBar(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_AUTOHSCROLL);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

		void SetOnlyNumberMode(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_NUMBER);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

	};
}
