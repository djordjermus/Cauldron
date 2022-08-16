#include "anchoredControl.h"
#include "theme.h"
#include <string>
#include <memory>
#pragma once
namespace cauldron::gui {

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // L A B E L   C O N T R O L - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	class label : public anchoredControl {
	public:
		label();

		//
		// Getters

		std::wstring getText() const;
		std::shared_ptr<theme> getTheme() const;
		std::shared_ptr<paint::font> getFont() const;
		paint::alignment getHorizontalAlignment() const;
		paint::alignment getVerticalAlignment() const;

		//
		// Setters

		void setText(const std::wstring& new_text);
		void setTheme(std::shared_ptr<theme> new_brush);
		void setFont(std::shared_ptr<paint::font> new_font);
		void setHorizontalAlignment(paint::alignment align);
		void setVerticalAlignment(paint::alignment align);

	private:
		
		//
		// Data

		std::wstring _text =
			L"";
		std::shared_ptr<theme> _theme;
		std::shared_ptr<paint::font> _font;
		paint::alignment _horizontal_align =
			paint::alignment::center;
		paint::alignment _vertical_align =
			paint::alignment::center;

		// Handlers

		static void paintLabelText(control& sender, paintData& e);
	};
}