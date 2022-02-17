#pragma once

#include "arcture.h"

#include "GL/glut.h"

using namespace arc;

namespace glarc {

	static PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL,
	PFD_TYPE_RGBA,
	32,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	24,
	0,
	0,
	PFD_MAIN_PLANE,
	0,
	0, 0, 0,
	};

	class GlutControl {

	private:

		arc::ARC_Control* control;
		int width, height;
		BITMAPINFO bmi;
		HBITMAP hBmp;
		HDC hdc;
		HGLRC hrc;
		void* pvBits;

	public:

		GlutControl(void) {

		}
		DLL_EXPORT GlutControl(arc::ARC_Control* ctrl) {

			control = ctrl;
			hdc		= GetDC(ctrl->hWnd());
			width	= ctrl->Size().width;
			height	= ctrl->Size().height;

			bmi = {
				{sizeof(BITMAPINFOHEADER), width, height, 1, 32, BI_RGB, 0, 0, 0, 0, 0},
			};

		}

		void Begin(void) {

			hBmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);

			SelectObject(hdc, hBmp);

			int pixFormat = ChoosePixelFormat(hdc, &pfd);
			SetPixelFormat(hdc, pixFormat, &pfd);

			hrc = wglCreateContext(hdc);

		}

		void End(void) {

			wglMakeCurrent(hdc, hrc);

		}

	};

}