#include "anchoredControl.h"
#include "theme.h"
#include "cauldron-common/eventData.h"
#include <string>
#pragma once
namespace cauldron::gui {
	class textInput : public anchoredControl {
	public:
		textInput();

		class validationData : public cauldron::common::eventData {
		public:
			validationData(const common::vector2<i32>& select, cwstr insert);
		
			i32 getFirstSelected() const;
			i32 getSelectRange() const;
			cwstr getInsertedText() const;
			bool isCanceled() const;
			void cancel();

		private:
			common::vector2<i32> _select;
			cwstr _text;
			bool _canceled;
		};

		std::shared_ptr<theme> getTheme() const;
		std::shared_ptr<const paint::font> getTextFont() const;
		std::shared_ptr<const paint::font> getHintFont() const;
		std::wstring getText() const;
		std::wstring getHint() const;
		common::vector2<i32> getSelect() const;

		virtual void setTheme(std::shared_ptr<theme> new_theme);
		virtual void setTextFont(std::shared_ptr<paint::font>);
		virtual void setHintFont(std::shared_ptr<paint::font>);
		virtual void setText(const std::wstring& new_text);
		virtual void setHint(const std::wstring& new_hint);
		virtual void setSelect(const common::vector2<i32> new_select);

		common::observable<void, control&, validationData&>& onValidate();

		static void validateNotDigit(gui::control& sender, gui::textInput::validationData& e);
		static void validateNotLetter(gui::control& sender, gui::textInput::validationData& e);
		static void validateNotWhitespace(gui::control& sender, gui::textInput::validationData& e);
	private:
		std::shared_ptr<theme> _theme =
			nullptr;

		std::wstring _text = 
			L"";
		std::wstring _hint =
			L"";

		std::shared_ptr<const paint::font> _text_font;
		std::shared_ptr<const paint::font> _hint_font;

		paint::alignment _horizontal =
			paint::alignment::near;
		paint::alignment _vertical =
			paint::alignment::near;

		common::vector2<i32> _select =
			common::vector2<i32>(-1, -1);

		common::observable<void, control&, validationData&> _on_validate =
			common::observable<void, control&, validationData&>();

		void deleteSelection();
		void deleteSingle(bool next);
		void insert(const wchar_t* text);

		static void onPaintTextInput(control& sender, paintData& e);
		static void onMouseDownTextInput(control& sender, mouseDownData& e);
		static void onMouseUpTextInput(control& sender, mouseUpData& e);
		static void onKeyDownTextInput(control& sender, keyDownData& e);
		static void onCharTextInput(control& sender, characterData& e);
		static void onLoseFocusTextInput(gui::control& sender, loseFocusData& e);
	};
}