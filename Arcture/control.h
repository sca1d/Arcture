#pragma once

#include "defstrct.h"

#define _IMP_CHECKED(__hwnd)									\
	BOOL Checked(BOOL value = ARC_NULL) {						\
																\
		if (value != ARC_NULL) {								\
			SendMessage(hwnd, BM_SETCHECK, value, 0);			\
			return value;										\
		}														\
		else {													\
			return SendMessage(hwnd, BM_GETCHECK, NULL, NULL);	\
		}														\
																\
	}

namespace arc {

	class ARC_Control {

	private:

		ARC_RGB	bcolor;

	public:

		int		id;
		HWND	hwnd, parent;
		void(*Click)(void);

		ARC_Control(void) {



		}
		ARC_Control(int _id, HWND _hwnd, HWND _parent, void(*_click)(void) = nullptr) {

			this->id = _id;
			this->hwnd = _hwnd;
			this->parent = _parent;
			this->Click = _click;

		}

		BOOL Enable(BOOL value = ARC_NULL) {

			if (value != ARC_NULL) {
				return ARC_SET_ENABLE(hwnd, value);
			}
			else {
				return ARC_GET_ENABLE(hwnd);
			}

		}

		HFONT Font(HFONT value = nullptr) {

			if (value != nullptr) {
				SendMessage(hwnd, WM_SETFONT, (LPARAM)value, true);
				return value;
			}
			else {
				return reinterpret_cast<HFONT>(SendMessage(hwnd, WM_GETFONT, 0, 0));
			}

		}

		ARC_RGB BackColor(ARC_RGB value = ARC_NULL) {

			if (value.IsNull()) {
				bcolor = value;
				InvalidateRect(hwnd, NULL, TRUE);
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
				InvalidateRect(hwnd, NULL, TRUE);
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

		_IMP_CHECKED(hwnd)

	};

	class ARC_CheckboxControl : public ARC_ButtonControl {

	public:

		using ARC_ButtonControl::ARC_ButtonControl;

		_IMP_CHECKED(hwnd);

	};

}
