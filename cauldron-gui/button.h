#include "anchoredControl.h"
#include "theme.h"
#include <memory>
#pragma once
namespace cauldron::gui {

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // B U T T O N   C O N T R O L - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	class button : public anchoredControl {
	public:
		button();

		//
		// Getters

		std::wstring getText() const;
		std::shared_ptr<theme> getTheme() const;
		std::shared_ptr<paint::font> getFont() const;
		paint::alignment getHorizontalAlign() const;
		paint::alignment getVerticalAlign() const;

		//
		// Setters

		virtual void setText(const std::wstring& text);
		virtual void setTheme(std::shared_ptr<theme> theme);
		virtual void setFont(std::shared_ptr<paint::font> font);
		virtual void setHorizontalAlign(paint::alignment align);
		virtual void setVerticalAlign(paint::alignment align);

		//
		// Event handlers

		common::observable<void, control&, common::eventData&>& onClick();
		
	private:

		//
		// Data

		std::wstring _text =
			L"";
		std::shared_ptr<theme> _theme;
		std::shared_ptr<paint::font> _font;
		paint::alignment _horizontal =
			paint::alignment::center;
		paint::alignment _vertical =
			paint::alignment::center;
		common::observable<void, control&, common::eventData&> _on_click =
			common::observable<void, control&, common::eventData&>();
		bool _pressed =
			false;

		//
		// Event handlers

		static void onPaintButton(control& sender, paintData& e);
		static void onMouseDownButton(control& sender, mouseDownData& e);
		static void onDoubleClickButton(control& sender, doubleClickData& e);
		static void onMouseUpButton(control& sender, mouseUpData& e);
		static void onCursorLeaveButton(control& sender, cursorLeaveData& e);
		static void onKeyDownButton(control& sender, keyDownData& e);
		static void onKeyUpButton(control& sender, keyUpData& e);
	};
}
