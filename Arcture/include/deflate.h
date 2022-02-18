#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <functional>
#include <string>

//@brief 関数エクスポート
#define DLL_EXPORT		__declspec(dllexport)

//@brief 配列の長さ
#define ARRAY_SIZE(_a)	(sizeof(_a) / sizeof(_a[0]))

#define ARC_ID2HANDLE		GetDlgItem
#define ARC_HANDLE2ID		GetDlgCtrlID

#define ARC_SET_ENABLE		EnableWindow
#define ARC_GET_ENABLE		IsWindowEnabled

//@brief Arcライブラリ内のNULL規定値
#define ARC_NULL			UINT_MAX

//@brief ARC_RGB から COLORREF 値に変換
#define ARC_RGB2CREF(_rgb)	(RGB(_rgb.r, _rgb.g, _rgb.b))

//@brief Arcライブラリ内のマウスイベントタイプ:	左クリック
#define ARC_LEFT_BUTTON		0x00
//@brief Arcライブラリ内のマウスイベントタイプ:	中央クリック
#define ARC_MIDDLE_BUTTON	0x01
//@brief Arcライブラリ内のマウスイベントタイプ:	右クリック
#define ARC_RIGHT_BUTTON	0x02

//@brief Arcライブラリ内のコントロールスタイル規定値
#define ARC_DEFAULT_STYLE	( WS_CHILD | WS_VISIBLE | BS_FLAT )
