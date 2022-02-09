#pragma once

#include "deflate.h"
#include "defstrct.h"

namespace arc {

	class Builder {

	private:
		HWND*	hwnd;
		ITable* table;
		
	public:
		Builder(HWND* _hwnd, ITable* _tbl) {

			hwnd	= _hwnd;
			table	= _tbl;

		}

		template <typename S>
		HWND AddButton(S text, Point position, Size size, int id, int style = WS_CHILD | WS_VISIBLE | BS_FLAT) {

			return CreateWindowEx(
				0,
				"BUTTON",
				text,
				style,
				position.x,
				position.y,
				size.width,
				size.height,
				*hwnd,
				(HMENU)id,
				table->hInst,
				NULL
			);

		}

	};

}
