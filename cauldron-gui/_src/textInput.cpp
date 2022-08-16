#include "../textInput.h"
#include "../defaults.h"
#include "cauldron-common/vectors.ostream.h"
#include <iostream>
namespace cauldron::gui {
	using namespace cauldron::common;



	textInput::textInput() :
		anchoredControl(), 
		_theme(defaults::getTheme()), 
		_text_font(defaults::getFont()), 
		_hint_font(defaults::getHintFont()) {
	
		onPaint()		.subscribe(onPaintTextInput);
		onGainFocus()	.subscribe(refreshOnEvent<gainFocusData&>);
		onLoseFocus()	.subscribe(refreshOnEvent<loseFocusData&>);
		onCursorLeave()	.subscribe(refreshOnEvent<cursorLeaveData&>);
		onCursorEnter()	.subscribe(refreshOnEvent<cursorEnterData&>);
		onMouseDown()	.subscribe(onMouseDownTextInput);
		onMouseUp()		.subscribe(onMouseUpTextInput);
	}



	std::shared_ptr<theme> textInput::getTheme() const {
		return _theme;
	}
	std::shared_ptr<const paint::font> textInput::getTextFont() const {
		return _text_font;
	}
	std::shared_ptr<const paint::font> textInput::getHintFont() const {
		return _hint_font;
	}
	std::wstring textInput::getText() const {
		return _text;
	}
	std::wstring textInput::getHint() const {
		return _hint;
	}
	vector2<i32> textInput::getSelect() const {
		return _select;
	}

	void textInput::setTheme(std::shared_ptr<theme> new_theme) {
		_theme = new_theme;
		refresh();
	}
	void textInput::setTextFont(std::shared_ptr<paint::font> new_font) {
		_text_font = new_font;
		refresh();
	}
	void textInput::setHintFont(std::shared_ptr<paint::font> new_font) {
		_hint_font = new_font;
		refresh();
	}
	void textInput::setText(const std::wstring& new_text) {
		_text = new_text;
		refresh();
	}
	void textInput::setHint(const std::wstring& new_hint) {
		_hint = new_hint;
		refresh();
	}
	void textInput::setSelect(const vector2<i32> new_select) {
		_select = new_select;
		if (_select.x > _select.y) {
			i32 temp = _select.x;
			_select.x = _select.y;
			_select.y = temp;
		}
		std::cout << "SELECT: " << _select << '\n';
		refresh();
	}

	void textInput::onPaintTextInput(control& sender, paintData& e) {
		textInput& ti = static_cast<textInput&>(sender);

		if (ti._theme == nullptr)
			return;

		vector2<f32> size		= sender.getClientSize();
		paint& gfx				= e.getPaint();
		theme::select select	= theme::parse(ti.isEnabled(), ti.isCursorOver(), false, ti.isFocused());

		std::shared_ptr<const paint::brush> bg = ti._theme->getBackground(select);
		std::shared_ptr<const paint::brush> fg = ti._theme->getForeground(select);
		std::shared_ptr<const paint::brush> og = ti._theme->getOutline(select);

		// Background
		if (bg != nullptr)
			gfx.fillRect({ {}, size }, *bg);
		
		// Outline
		if (og != nullptr) {
			paint::pen pen(*og, 1.0f);
			gfx.drawRect({ 0.0f, 0.0f, size.x - 1.0f, size.y - 1.0f }, pen);
		}
		
		bounds2<f32> tx_bounds = { 2.0f, 2.0f, size.x - 3.0f, size.y - 3.0f };

		// Select
		if (fg != nullptr) {

			// Calculate pre select length
			i32 pre_len = ti._text.length();
			if (pre_len > ti._select.x)
				pre_len = ti._select.x;

			// Calculate pre select bounds
			bounds2<f32> pre_bounds =
				paint::measureWrite(
					ti._text.c_str(), 
					pre_len,
					tx_bounds, 
					*ti._text_font,
					ti._horizontal,
					ti._vertical);

			// Calculate select length
			i32 sel_len = ti._select.y - ti._select.x;
			if (sel_len > ti._select.x)
				sel_len = ti._select.x;

			bounds2<f32> select_bounds =
				paint::measureWrite(
					ti._text.c_str(),
					ti._text.length(),
					tx_bounds,
					*ti._text_font,
					ti._horizontal,
					ti._vertical);
			
			// Paint select
			//gfx.fillRect();
		}

		// Text or hint
		if (fg != nullptr) {

			// TEXT
			if (ti._text.length() != 0) {
				if (ti._text_font != nullptr)
					gfx.write(
						ti._text.c_str(),
						ti._text.length(),
						tx_bounds,
						*ti._text_font, 
						*fg, 
						ti._horizontal, 
						ti._vertical);
			}

			// HINT
			else {
				if (ti._hint_font != nullptr)
					gfx.write(
						ti._hint.c_str(),
						ti._hint.length(),
						tx_bounds,
						*ti._hint_font, 
						*fg, 
						ti._horizontal, 
						ti._vertical);
			}
		}
	}
	void textInput::onMouseDownTextInput(control& sender, mouseDownData& e) {
		// Return if not LMB
		if (e.getButton() != key::leftMouseButton)
			return;

		textInput& ti		= static_cast<textInput&>(sender);
		vector2<f32> size	= sender.getClientSize();

		// Calculate mouse press point
		i32 ix =
			paint(sender).pointToCaretIndex(
			ti._text.c_str(),
			ti._text.length(),
			{ 2.0f, 2.0f, size.x - 3.0f, size.y - 3.0f },
			*ti._text_font,
			ti._horizontal,
			ti._vertical,
			e.getCursorPos());

		ti.setSelect(vector2<i32>(ix, ix));
	}
	void textInput::onMouseUpTextInput(control& sender, mouseUpData& e) {
		// Return if not LMB
		if (e.getButton() != key::leftMouseButton)
			return;

		textInput& ti = static_cast<textInput&>(sender);
		vector2<f32> size = sender.getClientSize();

		// Calculate mouse release point
		i32 ix =
			paint(sender).pointToCaretIndex(
				ti._text.c_str(),
				ti._text.length(),
				{ 2.0f, 2.0f, size.x - 3.0f, size.y - 3.0f },
				*ti._text_font,
				ti._horizontal,
				ti._vertical,
				e.getCursorPos());

		// Select region
		ti.setSelect(vector2<i32>(ti._select.x, ix));
	}

}