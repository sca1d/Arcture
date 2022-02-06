#pragma once

namespace arc {

	/*
	@brief �E�B���h�E�̒u������
	@param future:	�u��������̃n���h��
	@param old:		�u��������n���h��
	*/
	int RePlaceWindow(HWND future, HWND old) {

		LONG_PTR ws = ::GetWindowLongPtr(old, GWL_STYLE);
		ws &= ~(WS_CAPTION | WS_SIZEBOX);

		::SetWindowLongPtr(old, GWL_STYLE, ws);

		HWND res = ::SetParent(old, future);
		if (res == NULL) return 1;

		RECT rc;
		::GetClientRect(future, &rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		::SetWindowPos(old, NULL, 0, 0, width, height, SWP_NOZORDER);

		return 0;

	}

}
