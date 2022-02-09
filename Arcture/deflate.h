#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <functional>
#include <string>

#define DLL_EXPORT		__declspec(dllexport)

#define ARRAY_SIZE(_a)	(_a / _a[0])

#define ARC_LEFT_BUTTON		0x00
#define ARC_MIDDLE_BUTTON	0x01
#define ARC_RIGHT_BUTTON	0x02
