#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <functional>
#include <string>

//@brief �֐��G�N�X�|�[�g
#define DLL_EXPORT		__declspec(dllexport)

//@brief �z��̒���
#define ARRAY_SIZE(_a)	(sizeof(_a) / sizeof(_a[0]))

#define ARC_ID2HANDLE		GetDlgItem
#define ARC_HANDLE2ID		GetDlgCtrlID

#define ARC_SET_ENABLE		EnableWindow
#define ARC_GET_ENABLE		IsWindowEnabled

//@brief Arc���C�u��������NULL�K��l
#define ARC_NULL			UINT_MAX

//@brief ARC_RGB ���� COLORREF �l�ɕϊ�
#define ARC_RGB2CREF(_rgb)	(RGB(_rgb.r, _rgb.g, _rgb.b))

//@brief Arc���C�u�������̃}�E�X�C�x���g�^�C�v:	���N���b�N
#define ARC_LEFT_BUTTON		0x00
//@brief Arc���C�u�������̃}�E�X�C�x���g�^�C�v:	�����N���b�N
#define ARC_MIDDLE_BUTTON	0x01
//@brief Arc���C�u�������̃}�E�X�C�x���g�^�C�v:	�E�N���b�N
#define ARC_RIGHT_BUTTON	0x02

//@brief Arc���C�u�������̃R���g���[���X�^�C���K��l
#define ARC_DEFAULT_STYLE	( WS_CHILD | WS_VISIBLE | BS_FLAT )
