#pragma once

#include "deflate.h"

namespace arc {

	typedef struct _ITable {

		HINSTANCE	hInst;
		HINSTANCE	prev;
		LPSTR		cmdline;
		int			cmdshow;

		_ITable(void) {



		}
		_ITable(HINSTANCE _cur, HINSTANCE _prev, LPSTR _cmdline, int _cmdshow) {

			this->hInst		= _cur;
			this->prev		= _prev;
			this->cmdline	= _cmdline;
			this->cmdshow	= _cmdshow;

		}

	}ITable;

	typedef struct _Point {

		int x;
		int y;

		_Point(int _x, int _y) {
			
			this->x = _x;
			this->y = _y;

		}

	}Point;

	typedef struct _PointF {
		
		float x;
		float y;

		_PointF(float _x, float _y) {

			this->x = _x;
			this->y = _y;

		}

	}PointF;

	typedef struct _PointD {
	
		double x;
		double y;

		_PointD(double _x, double _y) {

			this->x = _x;
			this->y = _y;

		}

	}PointD;

	typedef struct _Size {

		int width;
		int height;

		_Size(int w, int h) {

			this->width		= w;
			this->height	= h;

		}

	}Size;

	typedef struct _SizeF {

		float width;
		float height;

		_SizeF(float w, float h) {

			this->width		= w;
			this->height	= h;

		}

	}SizeF;

	typedef struct _SizeD {

		double width;
		double height;

		_SizeD(double w, double h) {

			this->width		= w;
			this->height	= h;

		}

	}SizeD;

}
