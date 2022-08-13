#include "../button.h"
#include <iostream>

namespace cauldron::gui {
	using namespace cauldron::common;
	button::button() :
		anchoredControl() {

		onGainFocus()	.subscribe(refreshOnEvent<gainFocusData>);
		onLoseFocus()	.subscribe(refreshOnEvent<loseFocusData>);
		onCursorEnter()	.subscribe(refreshOnEvent<cursorEnterData>);
		onCursorLeave()	.subscribe(onCursorLeaveButton);
		onMouseDown()	.subscribe(onMouseDownButton);
		onMouseUp()		.subscribe(onMouseUpButton);
		onDoubleClick()	.subscribe(onDoubleClickButton);
		onPaint()		.subscribe(onPaintButton);
	}
	std::shared_ptr<theme> button::getTheme() const {
		return _theme;
	}

	void button::setTheme(std::shared_ptr<theme> new_theme) {
		_theme = new_theme;
		refresh();
	}
	void button::setText(const std::wstring& new_text) {
		_text = new_text;
		refresh();
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
			btn._mouse_dn,
			btn.isFocused());

		btn._theme->getBackground(sel);
		std::shared_ptr<const paint::brush> bg = btn._theme->getBackground(sel);
		std::shared_ptr<const paint::brush> fg = btn._theme->getForeground(sel);
		std::shared_ptr<const paint::brush> ol = btn._theme->getOutline(sel);
		paint::pen pen(*ol, 2.0f);
		paint::font f(L"trebuchet ms", 16.f, paint::font::style::bold);

		paint& paint = e.getPaint();
		paint.setSmoothing(true);

		// BACKGROUND
		if (fg != nullptr) {
			paint.fillRect(border, *fg);
		}

		// TEXT
		if (bg != nullptr) {
			paint.write(
				btn._text.c_str(),
				btn._text.length(),
				border, 
				f, 
				*bg, 
				paint::textAlign::center, 
				paint::textAlign::center);
		}

		// FOREGROUND
		if (ol != nullptr) {
			bounds2<f32> outline_border = bounds2<f32>(0.0f, 0.0f, size.x - 1.0f, size.y - 1.0f);
			paint.drawRect(outline_border, pen);
		}
	}
	void button::onMouseDownButton(control& sender, mouseDownData& e) {
		button& btn = static_cast<button&>(sender);
		btn._mouse_dn = true;
		btn.refresh();
	}
	void button::onDoubleClickButton(control& sender, doubleClickData& e) {
		button& btn = static_cast<button&>(sender);
		btn._mouse_dn = true;
		btn.refresh();
	}
	void button::onMouseUpButton(control& sender, mouseUpData& e) {
		button& btn = static_cast<button&>(sender);
		if (btn._mouse_dn) {
			btn._mouse_dn = false;
			eventData e;
			btn._on_click.notify(btn, e);
		}
		btn.refresh();
	}
	void button::onCursorLeaveButton(control& sender, cursorLeaveData& e) {
		button& btn = static_cast<button&>(sender);
		btn._mouse_dn = false;
		btn.refresh();

	}
}