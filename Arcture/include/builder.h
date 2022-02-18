#pragma once

#include "deflate.h"
#include "defstrct.h"
#include "control.h"

namespace arc {

	//@brief �R���g���[�������}�l�[�W���[�N���X
	class Builder {

	private:
		HWND				hwnd;
		ITable*				table;
		ControlInfoArray*	info;
		int*				cm;
		
	public:
		/*
		@param _hwnd:	�E�B���h�E�n���h��
		@param _tbl:	�C���X�^���X�e�[�u���̃|�C���^
		@param _info:	�R���g���[���W���|�C���^
		@param _cm:		�R���g���[�����i�[�|�C���^
		*/
		Builder(HWND _hwnd, ITable* _tbl, ControlInfoArray* _info, int* _cm) {

			hwnd	= _hwnd;
			table	= _tbl;
			info	= _info;
			cm		= _cm;

		}
		
		#pragma region buttons

		/*
		@brief �J�X�^���R���g���[���̍쐬
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param style:		�X�^�C��
		*/
		ARC_Control* AddCustomControl(Point position, Size size, int id, int style = ARC_DEFAULT_STYLE) {

			HWND control_hwnd = CreateWindowEx(
				0,
				"STATIC",
				"",
				style | SS_OWNERDRAW,
				position.x,
				position.y,
				size.width,
				size.height,
				hwnd,
				(HMENU)id,
				table->hInst,
				NULL
			);

			ARC_Control control(id, control_hwnd, hwnd, position, size);

			info->c[*cm] = control;
			*cm += 1;

			return &info->c[*cm - 1];

		}

		/*
		@brief �{�^���R���g���[���̍쐬
		@param text:		�\���e�L�X�g
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param _click:		�N���b�N�C�x���g�֐�
		@param style:		�X�^�C��
		*/
		template <typename S>
		ARC_ButtonControl* AddButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE) {

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

			ARC_ButtonControl control(id, control_hwnd, hwnd, position, size, _click);

			info->c[*cm] = control;
			*cm += 1;

			return (ARC_ButtonControl*)&info->c[*cm - 1];

		}

		/*
		@brief ���W�I�{�^���R���g���[���̍쐬
		@param text:		�\���e�L�X�g
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param _click:		�N���b�N�C�x���g�֐�
		@param style:		�X�^�C��
		*/
		template <typename S>
		ARC_RadioButtonControl* AddRadioButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_RADIOBUTTON) {

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

			ARC_RadioButtonControl control(id, control_hwnd, position, size, hwnd, _click);

			info->c[*cm] = control;
			*cm += 1;

			return (ARC_RadioButtonControl*)&info->c[*cm - 1];

		}

		/*
		@brief �I�[�g���W�I�{�^���R���g���[���̍쐬
		@param text:		�\���e�L�X�g
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param _click:		�N���b�N�C�x���g�֐�
		@param style:		�X�^�C��
		*/
		template <typename S>
		ARC_RadioButtonControl* AddAutoRadioButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_AUTORADIOBUTTON) {

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

			ARC_RadioButtonControl control(id, control_hwnd, hwnd, position, size, _click);

			info->c[*cm] = control;
			*cm += 1;

			return (ARC_RadioButtonControl*)&info->c[*cm - 1];

		}

		/*
		@brief �`�F�b�N�{�b�N�X�R���g���[���̍쐬
		@param text:		�\���e�L�X�g
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param _click:		�N���b�N�C�x���g�֐�
		@param style:		�X�^�C��
		*/
		template <typename S>
		ARC_CheckboxControl* AddCheckBoxButton(S text, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_AUTOCHECKBOX) {

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

			ARC_CheckboxControl control(id, control_hwnd, hwnd, position, size, _click);

			info->c[*cm] = control;
			*cm += 1;

			return (ARC_CheckboxControl*)&info->c[*cm - 1];


		}

		/*
		@brief �C���[�W�{�^���R���g���[���̍쐬
		@param text:		�\���e�L�X�g
		@param image:		�\���r�b�g�}�b�v
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param _click:		�N���b�N�C�x���g�֐�
		@param style:		�X�^�C��
		*/
		template <typename S>
		ARC_ButtonControl* AddImageButton(S text, HBITMAP image, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_BITMAP) {

			ARC_ButtonControl* info = AddButton(text, position, size, id, _click, style);
			SendMessage(info->hWnd(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
			return info;

		}
		/*
		@brief �C���[�W�{�^���R���g���[���̍쐬
		@param text:		�\���e�L�X�g
		@param image:		�\���摜�̃t�@�C���p�X
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param _click:		�N���b�N�C�x���g�֐�
		@param style:		�X�^�C��
		*/
		template <typename S>
		ARC_ButtonControl* AddImageButton(S text, S image_path, Point position, Size size, int id, void(*_click)(void) = nullptr, int style = ARC_DEFAULT_STYLE | BS_BITMAP) {

			HBITMAP hBmp = (HBITMAP)LoadImage(NULL, image_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			return AddImageButton(text, hBmp, position, size, id, _click, style);

		}

		#pragma endregion

		/*
		@brief �e�L�X�g�{�b�N�X�R���g���[���̍쐬
		@param text:		�\���e�L�X�g
		@param position:	�z�u�ʒu
		@param size:		�T�C�Y
		@param id:			ID
		@param _click:		�N���b�N�C�x���g�֐�
		@param style:		�X�^�C��
		*/
		template <typename S>
		ARC_TextBoxControl* AddTextBox(S text, Point position, Size size, int id, int style = ARC_DEFAULT_STYLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT) {

			HWND control_hwnd = CreateWindowEx(
				0,
				"EDIT",
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

			SendMessage(control_hwnd, EM_SETLIMITTEXT, (WPARAM)63, 0);

			ARC_TextBoxControl control(id, control_hwnd, hwnd, position, size);

			info->c[*cm] = control;
			*cm += 1;

			return (ARC_TextBoxControl*)&info->c[*cm - 1];

		}

	};

}
