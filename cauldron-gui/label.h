#include "anchoredControl.h"
#include "theme.h"
#include <string>
#include <memory>
#pragma once
namespace cauldron::gui {
	class label : public anchoredControl {
	public:
		label();

		std::wstring getText() const;
		std::shared_ptr<paint::font> getFont() const;
		std::shared_ptr<theme> getTheme() const;
		paint::textAlign getHorizontalAlignment() const;
		paint::textAlign getVerticalAlignment() const;

		void setText(const std::wstring& new_text);
		void setFont(std::shared_ptr<paint::font> new_font);
		void setTheme(std::shared_ptr<theme> new_brush);
		void setHorizontalAlignment(paint::textAlign align);
		void setVerticalAlignment(paint::textAlign align);

	private:
		std::wstring _text =
			L"";
		std::shared_ptr<theme> _theme =
			nullptr;
		std::shared_ptr<paint::font> _font =
			nullptr;
		paint::textAlign _horizontal_align =
			paint::textAlign::center;
		paint::textAlign _vertical_align =
			paint::textAlign::center;

		static void paintLabelText(control& sender, paintData& e);
	};
}