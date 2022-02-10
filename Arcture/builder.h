#pragma once

#include "deflate.h"
#include "defstrct.h"
#include "control.h"

namespace arc {

	class Builder {

	private:
		HWND				hwnd;
		ITable*				table;
		ControlInfoArray*	info;
		int*				cm;
		
	public:
		Builder(HWND _hwnd, ITable* _tbl, ControlInfoArray* _info, int* _cm) {

			hwnd	= _hwnd;
			table	= _tbl;
			info	= _info;
			cm		= _cm;

		}

		template <typename S>
		ARC_ButtonControl AddButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE) {

			HWND control_hwnd = CreateWindowEx(
				0,
				"BUTTON",
				text,
				style,
				position.x,
				position.y,
				size.width,
				size.height,
				hwnd,
				(HMENU)id,
				table->hInst,
				NULL
			);

			ARC_ButtonControl control(id, control_hwnd, hwnd, _click);

			info->c[*cm] = control;
			*cm += 1;

			return control;

		}

		template <typename S>
		ARC_RadioButtonControl AddRadioButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_RADIOBUTTON) {

			HWND control_hwnd = CreateWindowEx(
				0,
				"BUTTON",
				text,
				style,
				position.x,
				position.y,
				size.width,
				size.height,
				hwnd,
				(HMENU)id,
				table->hInst,
				NULL
			);

			ARC_RadioButtonControl control(id, control_hwnd, hwnd, _click);

			info->c[*cm] = control;
			*cm += 1;

			return control;

		}

		template <typename S>
		ARC_RadioButtonControl AddAutoRadioButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_AUTORADIOBUTTON) {

			HWND control_hwnd = CreateWindowEx(
				0,
				"BUTTON",
				text,
				style,
				position.x,
				position.y,
				size.width,
				size.height,
				hwnd,
				(HMENU)id,
				table->hInst,
				NULL
			);

			ARC_RadioButtonControl control(id, control_hwnd, hwnd, _click);

			info->c[*cm] = control;
			*cm += 1;

			return control;

		}

		template <typename S>
		ARC_CheckboxControl AddCheckBoxButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_AUTOCHECKBOX) {

			HWND control_hwnd = CreateWindowEx(
				0,
				"BUTTON",
				text,
				style,
				position.x,
				position.y,
				size.width,
				size.height,
				hwnd,
				(HMENU)id,
				table->hInst,
				NULL
			);

			ARC_CheckboxControl control(id, control_hwnd, hwnd, _click);

			info->c[*cm] = control;
			*cm += 1;

			return control;

		}

		template <typename S>
		ARC_ButtonControl AddImageButton(S text, HBITMAP image, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_BITMAP) {

			ARC_ButtonControl info = AddButton(text, position, size, id, _click, style);
			SendMessage(info.hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
			return info;

		}
		template <typename S>
		ARC_ButtonControl AddImageButton(S text, S image_path, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_BITMAP) {

			HBITMAP hBmp = (HBITMAP)LoadImage(NULL, image_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			return AddImageButton(text, hBmp, position, size, id, _click, style);

		}

	};

}
