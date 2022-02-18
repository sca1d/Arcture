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

	#pragma pack(push, 1)
	//@brief コントロールクラス
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
		@brief ※このコンストラクタを使用した場合正しく動作しない場合があります。
		*/
		ARC_Control(void) {



		}
		/*
		@param id_:		コントロールID
		@param hwnd_:	コントロールハンドル
		@param parent_:	親コントロールハンドル
		@param loc_:	配置位置
		@param size_:	サイズ
		@param _click:	クリックイベント関数
		*/
		ARC_Control(int id_, HWND hwnd_, HWND parent_, Point loc_, Size size_, void(*_click)(void) = nullptr) {

			this->_id = id_;
			this->_hwnd = hwnd_;
			this->_parent = parent_;
			this->_location = loc_;
			this->_size = size_;
			this->Click = _click;

		}

		//@brief コントロールをフォーカス
		void Focus(void) {

			SetFocus(this->_hwnd);

		}

		//@brief コントロールIDを取得
		int ID(void) {

			return _id;

		}

		//@brief コントロールハンドルを取得
		HWND hWnd(void) {

			return _hwnd;

		}

		//@brief 親コントロールハンドルを取得
		HWND Parent(void) {

			return _parent;

		}

		//@brief 配置位置を取得
		Point Location(void) {

			return _location;

		}

		//@brief サイズを取得
		Size Size(void) {

			return _size;

		}

		/*
		@brief コントロールの "有効化/無効化" を設定・取得
		@param value:	TRUE で有効化, FALSE で無効化, ARC_NULL で値の取得
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
		@brief コントロールの フォント を設定・取得
		@param value:	HFONT型で設定, nullptr で値の取得
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
		@brief コントロールの 背景色 を設定・取得
		@param value:	ARC_RGB型で設定, ARC_NULL で値の取得
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
	#pragma pack(pop)

	#pragma pack(push, 1)
	typedef struct { ARC_Control c[0xFF]; }ControlInfoArray;
	#pragma pack(pop)

	#pragma region buttons

	//@brief ボタンコントロール
	class ARC_ButtonControl : public ARC_Control {

	private:

		ARC_RGB	tcolor;

	public:

		using ARC_Control::ARC_Control;

		/*
		@brief コントロールの 文字色 を設定・取得
		@param value:	ARC_RGB型で設定, ARC_NULL で値の取得
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

	//@brief ラジオボタンコントロール
	class ARC_RadioButtonControl : public ARC_ButtonControl {

	public:

		using ARC_ButtonControl::ARC_ButtonControl;

		/*
		@brief コントロールの チェック状態 を設定・取得
		@param value:	TRUE でチェック, FALSE でアンチェック, ARC_NULL で値の取得
		*/
		_IMP_CHECKED(hWnd())

	};

	//@brief チェックボックスコントロール
	class ARC_CheckboxControl : public ARC_ButtonControl {

	public:

		using ARC_ButtonControl::ARC_ButtonControl;

		_IMP_CHECKED(hWnd())

	};

	#pragma endregion

	//@brief テキストボックスコントロール
	class ARC_TextBoxControl : public ARC_Control {

	private:

		char* _text;

	public:

		using ARC_Control::ARC_Control;

		//@brief テキスト入力の 改行 を有効化
		void SetMultiLineMode(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_MULTILINE);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

		//@brief テキストボックス内の スクロールバー を有効化
		void SetScrollBar(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_AUTOHSCROLL);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

		//@brief テキスト入力を 数字のみ に制限
		void SetOnlyNumberMode(void) {

			SetWindowLong(this->_hwnd, GWL_STYLE, ES_NUMBER);
			ShowWindow(this->_hwnd, SW_SHOW);

		}

	};
}
