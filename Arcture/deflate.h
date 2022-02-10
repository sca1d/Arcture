#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <functional>
#include <string>

#define DLL_EXPORT		__declspec(dllexport)

#define ARRAY_SIZE(_a)	(_a / _a[0])

#define ARC_ID2HANDLE		GetDlgItem
#define ARC_HANDLE2ID		GetDlgCtrlID

#define ARC_SET_ENABLE		EnableWindow
#define ARC_GET_ENABLE		IsWindowEnabled

#define ARC_NULL			UINT_MAX

#define ARC_RGB2CREF(_rgb)	(RGB(_rgb.r, _rgb.g, _rgb.b))

#define ARC_LEFT_BUTTON		0x00
#define ARC_MIDDLE_BUTTON	0x01
#define ARC_RIGHT_BUTTON	0x02

#define ARC_DEFAULT_STYLE	( WS_CHILD | WS_VISIBLE | BS_FLAT )
