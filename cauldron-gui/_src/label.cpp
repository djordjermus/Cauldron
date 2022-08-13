#include "../label.h"
namespace cauldron::gui {
	using namespace cauldron::common;



	label::label() :
		anchoredControl(){
		
		onPaint().subscribe(label::paintLabelText);
	}

	std::wstring label::getText() const {
		return _text;
	}
	std::shared_ptr<paint::font> label::getFont() const {
		return _font;
	}
	std::shared_ptr<theme> label::getTheme() const {
		return _theme;
	}
	paint::textAlign label::getHorizontalAlignment() const {
		return _horizontal_align;
	}
	paint::textAlign label::getVerticalAlignment() const {
		return _vertical_align;
	}

	void label::setText(const std::wstring& new_text) {
		_text = new_text;
		refresh();
	}
	void label::setFont(std::shared_ptr<paint::font> new_font) {
		_font = new_font;
		refresh();
	}
	void label::setTheme(std::shared_ptr<theme> new_brush) {
		_theme = new_brush;
		refresh();
	}
	void label::setHorizontalAlignment(paint::textAlign align) {
		_horizontal_align = align;
		refresh();
	}
	void label::setVerticalAlignment(paint::textAlign align) {
		_vertical_align = align;
		refresh();
	}
	void label::paintLabelText(control& sender, paintData& e) {
		label& lb = static_cast<label&>(sender);
		if (lb._font == nullptr)
			return;
		if (lb._theme == nullptr)
			return;

		theme::select select = theme::parse(lb.isEnabled(), lb.isCursorOver(), false, lb.isFocused());

		std::shared_ptr<const paint::brush> bg = lb._theme->getBackground(select);
		std::shared_ptr<const paint::brush> fg = lb._theme->getForeground(select);

		if(bg != nullptr)
			e.getPaint().fillRect({ {}, sender.getClientSize()}, *bg);
		if(fg != nullptr)
			e.getPaint().write(
				lb._text.c_str(),
				lb._text.length(),
				{ {0.0f, 0.0f}, lb.getClientSize().as<f32>() },
				*lb._font,
				*fg,
				lb._horizontal_align,
				lb._vertical_align);
	}
}