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

	private:

		int		_id;
		HWND	_hwnd, _parent;
		ARC_RGB	bcolor;

	public:

		void(*Click)(void);

		ARC_Control(void) {



		}
		ARC_Control(int id_, HWND hwnd_, HWND parent_, void(*_click)(void) = nullptr) {

			this->_id = id_;
			this->_hwnd = hwnd_;
			this->_parent = parent_;
			this->Click = _click;

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

}
