#pragma once

#include "defstrct.h"

#define _IMP_CHECKED(__hwnd)														\
	BOOL Checked(BOOL value = ARC_NULL) {											\
																					\
		if (value != ARC_NULL) {													\
			SendMessage(__hwnd, BM_SETCHECK, value, 0);								\
			return value;															\
		}																			\
		else {																		\
			return SendMessage(__hwnd, BM_GETCHECK, NULL, NULL);					\
		}																			\
																					\
	}

namespace arc {

	//@brief �R���g���[���N���X
	class ARC_Control {

	protected:

		int		_id;
		HWND	_hwnd, _parent;
		Point	_location;
		Size	_size;
		ARC_RGB	bcolor;

	public:

		void(*Update)(void);
		void(*Click)(void);

		/*
		@brief �����̃R���X�g���N�^���g�p�����ꍇ���������삵�Ȃ��ꍇ������܂��B
		*/
		ARC_Control(void) {



		}
		/*
		@param id_:		�R���g���[��ID
		@param hwnd_:	�R���g���[���n���h��
		@param parent_:	�e�R���g���[���n���h��
		@param loc_:	�z�u�ʒu
		@param size_:	�T�C�Y
		@param _click:	�N���b�N�C�x���g�֐�
		*/
		ARC_Control(int id_, HWND hwnd_, HWND parent_, Point loc_, Size size_, void(*_click)(void) = nullptr) {

			this->_id = id_;
			this->_hwnd = hwnd_;
			this->_parent = parent_;
			this->_location = loc_;
			this->_size = size_;
			this->Click = _click;

		}

		//@brief �R���g���[�����t�H�[�J�X
		void Focus(void) {

			SetFocus(this->_hwnd);

		}

		//@brief �R���g���[��ID���擾
		int ID(void) {

			return _id;

		}

		//@brief �R���g���[���n���h�����擾
		HWND hWnd(void) {

			return _hwnd;

		}

		//@brief �e�R���g���[���n���h�����擾
		HWND Parent(void) {

			return _parent;

		}

		//@brief �z�u�ʒu���擾
		Point Location(void) {

			return _location;

		}

		//@brief �T�C�Y���擾
		Size Size(void) {

			return _size;

		}

		/*
		@brief �R���g���[���� "�L����/������" ��ݒ�E�擾
		@param value:	TRUE �ŗL����, FALSE �Ŗ�����, ARC_NULL �Œl�̎擾
		*/
		BOOL Enable(BOOL value = ARC_NULL) {

			if (value != ARC_NULL) {
				return ARC_SET_ENABLE(_hwnd, value);
			}
			else {
				return ARC_GET_ENABLE(_hwnd);
			}

		}

		/*
		@brief �R���g���[���� �t�H���g ��ݒ�E�擾
		@param value:	HFONT�^�Őݒ�, nullptr �Œl�̎擾
		*/
		HFONT Font(HFONT value = nullptr) {

			if (value != nullptr) {
				SendMessage(_hwnd, WM_SETFONT, (LPARAM)value, true);
				return value;
			}
			else {
				return reinterpret_cast<HFONT>(SendMessage(_hwnd, WM_GETFONT, 0, 0));
			}

		}

		/*
		@brief �R���g���[���� �w�i�F ��ݒ�E�擾
		@param value:	ARC_RGB�^�Őݒ�, ARC_NULL �Œl�̎擾
		*/
		ARC_RGB BackColor(ARC_RGB value = ARC_NULL) {

			if (value.IsNull()) {
				bcolor = value;
				InvalidateRect(_hwnd, NULL, TRUE);
				return value;
			}
			else {
				return bcolor;
			}

		}

	};

	typedef struct { ARC_Control c[0xFF]; }ControlInfoArray;

	#pragma region buttons

	//@brief �{�^���R���g���[��
	class ARC_ButtonControl : public ARC_Control {

	private:

		ARC_RGB	tcolor;

	public:

		using ARC_Control::ARC_Control;

		/*
		@brief �R���g���[���� �����F ��ݒ�E�擾
		@param value:	ARC_RGB�^�Őݒ�, ARC_NULL �Œl�̎擾
		*/
		ARC_RGB TextColor(ARC_RGB value = ARC_NULL) {

			if (value.IsNull()) {
				tcolor = value;
				InvalidateRect(hWnd(), NULL, TRUE);
				return value;
			}
			else {
				return tcolor;
			}

		}

	};

	//@brief ���W�I�{�^���R���g���[��
	class ARC_RadioButtonControl : public ARC_ButtonControl {

	public:

		using ARC_ButtonControl::ARC_ButtonControl;

		/*
		@brief �R���g���[���� �`�F�b�N��� ��ݒ�E�擾
		@param value:	TRUE �Ń`�F�b�N, FALSE �ŃA���`�F�b�N, ARC_NULL �Œl�̎擾
		*/
		_IMP_CHECKED(hWnd())

	};

	//@brief �`�F�b�N�{�b�N�X�R���g���[��
	class ARC_CheckboxControl : public ARC_ButtonControl {

	public:

		using ARC_ButtonControl::ARC_ButtonControl;

		_IMP_CHECKED(hWnd())

	};

	#pragma endregion

	//@brief �e�L�X�g�{�b�N�X�R���g���[��
	class ARC_TextBoxControl : public ARC_Control {

	private:

		char* _text;

	public:

		using ARC_Control::ARC_Control;

		//@brief �e�L�X�g���͂� ���s ��L����
		void SetMultiLineMode(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_MULTILINE);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

		//@brief �e�L�X�g�{�b�N�X���� �X�N���[���o�[ ��L����
		void SetScrollBar(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_AUTOHSCROLL);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

		//@brief �e�L�X�g���͂� �����̂� �ɐ���
		void SetOnlyNumberMode(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_NUMBER);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

	};
}
