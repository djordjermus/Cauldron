#include "anchoredControl.h"
#include "theme.h"
#include <string>
#pragma once
namespace cauldron::gui {
	class textInput : public anchoredControl {
	public:
		textInput();

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


		static void onPaintTextInput(control& sender, paintData& e);
		static void onMouseDownTextInput(control& sender, mouseDownData& e);
		static void onMouseUpTextInput(control& sender, mouseUpData& e);
	};
}