#include "../checkInput.h"
#include "../defaults.h"
namespace cauldron::gui {
	using namespace cauldron::common;



	checkInput::checkInput() :
		anchoredControl(), _theme(defaults::getTheme()), _font(defaults::getFont()) {

		setFocusStyle(focusStyle::focusable);

		onCursorEnter()	.subscribe(refreshOnEvent<cursorEnterData&>);
		onCursorLeave()	.subscribe(refreshOnEvent<cursorLeaveData&>);
		onGainFocus()	.subscribe(refreshOnEvent<gainFocusData&>);
		onLoseFocus()	.subscribe(refreshOnEvent<loseFocusData&>);
		onKeyUp()		.subscribe(onCheckInputKeyUp);
		onMouseUp()		.subscribe(onCheckInputMouseUp);
		onPaint()		.subscribe(onCheckInputPaint);
	}
	checkInput::valueChangedData::valueChangedData(bool value) :
		_value(value) {}
	bool checkInput::valueChangedData::getNewValue() const {
		return _value;
	}

	std::shared_ptr<theme> checkInput::getTheme() const {
		return _theme;
	}
	std::shared_ptr<paint::font> checkInput::getFont() const {
		return _font;
	}
	std::wstring checkInput::getText() const {
		return _text;
	}
	bool checkInput::getValue() const {
		return _value;
	}
	std::shared_ptr<std::vector<checkInput*>> checkInput::getRadioGroup() const {
		return _group;
	}

	void checkInput::setTheme(std::shared_ptr<theme> new_theme) {
		_theme = new_theme;
		refresh();
	}
	void checkInput::setFont(std::shared_ptr<paint::font> new_font) {
		_font = new_font;
		refresh();
	}
	void checkInput::setText(const std::wstring new_text) {
		_text = new_text;
		refresh();
	}
	void checkInput::setValue(bool new_value) {
		if (_value != new_value) {
			_value = new_value;
			valueChangedData e(_value);
			_on_value_changed.notify(*this, e);
			refresh();
		}
	}
	void checkInput::setRadioGroup(std::shared_ptr<std::vector<checkInput*>> radio_group) {
		_group = radio_group;
	}

	observable<void, control&, checkInput::valueChangedData&>& checkInput::onValueChanged() {
		return _on_value_changed;
	}

	void checkInput::normalizeGroup(std::shared_ptr<std::vector<checkInput*>> radio_group, checkInput* set) {
		for (auto* ci : *radio_group) {
			if (ci != nullptr && ci != set && ci->_value == true)
				ci->setValue(false);
		}
		if(set)
			set->setValue(true);
	}


	void checkInput::onCheckInputPaint(control& sender, paintData& e) {
		checkInput& ci = static_cast<checkInput&>(sender);
		if (ci._theme == nullptr)
			return;

		paint& gfx = e.getPaint();

		vector2<i32> size = sender.getClientSize();
		theme::select sel = theme::parse(
			ci.isEnabled(),
			ci.isCursorOver(),
			false,
			ci.isFocused());

		std::shared_ptr<const paint::brush> bg = ci._theme->getBackground(sel);
		std::shared_ptr<const paint::brush> fg = ci._theme->getForeground(sel);
		std::shared_ptr<const paint::brush> ol = ci._theme->getOutline(sel);

		// Background
		if (bg != nullptr)
			gfx.fillRect({ {}, size }, *bg);

		// Outline
		bounds2<f32> box_bounds = { 0.0f, 0.0f, (f32)size.y - 1, (f32)size.y - 1 };
		if (ol != nullptr) {
			paint::pen pen(*ol, 1.0f);
			gfx.drawRect(box_bounds, pen);

			// Check
			if (ci._value != 0 && fg != nullptr) {
				bounds2<f32> fill_bounds = box_bounds;
				fill_bounds.from = fill_bounds.from + vector2<f32>(2, 2);
				fill_bounds.to = fill_bounds.to - vector2<f32>(1, 1);
				gfx.fillRect(fill_bounds, *fg);
			}
		}

		// Text
		bounds2<f32> text_bounds = {box_bounds.to.x + 2, box_bounds.from.y, (f32)size.x, (f32)size.y};
		if (fg != nullptr && ci._font != nullptr && ci._font->isValid()) {
			gfx.write(
				ci._text.c_str(),
				ci._text.length(),
				text_bounds,
				*ci._font,
				*fg,
				paint::alignment::near,
				paint::alignment::center);
		}
		
	}
	void checkInput::onCheckInputMouseUp(control& sender, mouseUpData& e) {
		checkInput& ci = static_cast<checkInput&>(sender);
		if (ci._group == nullptr)
			ci.setValue(!ci.getValue());
		else
			normalizeGroup(ci._group, &ci); // Clear every box except for self
		
	}
	void checkInput::onCheckInputKeyUp(control& sender, keyUpData& e) {
		if (e.getKey() != key::space)
			return;

		checkInput& ci = static_cast<checkInput&>(sender);
		if (ci._group == nullptr)
			ci.setValue(!ci.getValue());
		else
			normalizeGroup(ci._group, &ci); // Clear every box except for self
	}

}