#include "../button.h"
#include "../defaults.h"
#include <iostream>

namespace cauldron::gui {
	using namespace cauldron::common;



	button::button() :
		anchoredControl(), _font(defaults::getFont()), _theme(defaults::getTheme()) {

		setFocusStyle(focusStyle::focusable);

		onGainFocus()	.subscribe(refreshOnEvent<gainFocusData>);
		onLoseFocus()	.subscribe(refreshOnEvent<loseFocusData>);
		onCursorEnter()	.subscribe(refreshOnEvent<cursorEnterData>);
		onCursorLeave()	.subscribe(onCursorLeaveButton);
		onMouseDown()	.subscribe(onMouseDownButton);
		onMouseUp()		.subscribe(onMouseUpButton);
		onKeyDown()		.subscribe(onKeyDownButton);
		onKeyUp()		.subscribe(onKeyUpButton);
		onDoubleClick()	.subscribe(onDoubleClickButton);
		onPaint()		.subscribe(onPaintButton);
	}
	std::wstring button::getText() const {
		return _text;
	}
	std::shared_ptr<theme> button::getTheme() const {
		return _theme;
	}
	std::shared_ptr<paint::font> button::getFont() const {
		return _font;
	}
	paint::alignment button::getHorizontalAlign() const {
		return _horizontal;
	}
	paint::alignment button::getVerticalAlign() const {
		return _vertical;
	}

	void button::setText(const std::wstring& new_text) {
		_text = new_text;
		refresh();
	}
	void button::setTheme(std::shared_ptr<theme> new_theme) {
		_theme = new_theme;
		refresh();
	}
	void button::setFont(std::shared_ptr<paint::font> font) {
		_font = font;
		refresh();
	}
	void button::setHorizontalAlign(paint::alignment align) {
		if (_horizontal != align) {
			_horizontal = align;
			refresh();
		}
	}
	void button::setVerticalAlign(paint::alignment align) {
		if (_vertical != align) {
			_vertical = align;
			refresh();
		}
	}

	observable<void, control&, eventData&>& button::onClick() {
		return _on_click;
	}

	void button::onPaintButton(control& sender, paintData& e) {
		button& btn = static_cast<button&>(sender);
		if (btn._theme == nullptr)
			return;

		vector2<f32> size = sender.getClientSize();
		bounds2<f32> border = { 0.0f, 0.0f, size.x, size.y };

		theme::select sel = theme::parse(
			btn.isEnabled(),
			btn.isCursorOver(),
			btn._pressed,
			btn.isFocused());

		btn._theme->getBackground(sel);
		std::shared_ptr<const paint::brush> bg = btn._theme->getBackground(sel);
		std::shared_ptr<const paint::brush> fg = btn._theme->getForeground(sel);
		std::shared_ptr<const paint::brush> ol = btn._theme->getOutline(sel);
		paint::pen pen(*ol, 2.0f);

		paint& paint = e.getPaint();
		paint.setSmoothing(true);

		// BACKGROUND
		if (fg != nullptr) {
			paint.fillRect(border, *fg);
		}

		// TEXT
		if (bg != nullptr && btn._font != nullptr) {
			paint.write(
				btn._text.c_str(),
				btn._text.length(),
				border, 
				*btn._font,
				*bg, 
				btn._horizontal, 
				btn._vertical);
		}

		// FOREGROUND
		if (ol != nullptr) {
			bounds2<f32> outline_border = bounds2<f32>(0.0f, 0.0f, size.x - 1.0f, size.y - 1.0f);
			paint.drawRect(outline_border, pen);
		}
	}
	void button::onMouseDownButton(control& sender, mouseDownData& e) {
		button& btn = static_cast<button&>(sender);
		btn._pressed = true;
		btn.refresh();
	}
	void button::onDoubleClickButton(control& sender, doubleClickData& e) {
		button& btn = static_cast<button&>(sender);
		btn._pressed = true;
		btn.refresh();
	}
	void button::onMouseUpButton(control& sender, mouseUpData& e) {
		button& btn = static_cast<button&>(sender);
		if (btn._pressed) {
			btn._pressed = false;
			eventData e;
			btn._on_click.notify(btn, e);
		}
		btn.refresh();
	}
	void button::onCursorLeaveButton(control& sender, cursorLeaveData& e) {
		button& btn = static_cast<button&>(sender);
		btn._pressed = false;
		btn.refresh();
	}

	void button::onKeyDownButton(control& sender, keyDownData& e) {
		button& btn = static_cast<button&>(sender);
		if (e.getKey() == key::space && btn._pressed == false) {
			btn._pressed = true;
			btn.refresh();
		}
	}
	void button::onKeyUpButton(control& sender, keyUpData& e) {
		button& btn = static_cast<button&>(sender);
		if (e.getKey() == key::space && btn._pressed == true) {
			btn._pressed = false;
			eventData e;
			btn._on_click.notify(btn, e);
			btn.refresh();
		}
	}
}