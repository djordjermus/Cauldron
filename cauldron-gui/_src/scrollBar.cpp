#include "../scrollBar.h"
#include "cauldron-common/math.h"
namespace cauldron::gui {
	using namespace cauldron::common;



	scrollBar::scrollBar() :
		anchoredControl() {
		onScroll()		.subscribe(onScrollScrollBar);
		onMouseDown()	.subscribe(onMouseDownScrollBar);
		onPaint()		.subscribe(onPaintScrollBar);
		onCursorEnter()	.subscribe(refreshOnEvent<cursorEnterData>);
		onCursorLeave()	.subscribe(refreshOnEvent<cursorLeaveData>);
		onGainFocus()	.subscribe(refreshOnEvent<gainFocusData>);
		onLoseFocus()	.subscribe(refreshOnEvent<loseFocusData>);
	}

	scrollBar::valueChangedData::valueChangedData(f64 old_val, f64 new_val) :
		eventData(), _new(new_val), _old(old_val) {}
	f64 scrollBar::valueChangedData::getNewValue() const {
		return _new;
	}
	f64 scrollBar::valueChangedData::getOldValue() const {
		return _old;
	}


	f64 scrollBar::getValue() const {
		return _value;
	}
	f64 scrollBar::getHandleSize() const {
		return _handle_size;
	}
	f64 scrollBar::getStep() const {
		return _step;
	}
	orientation scrollBar::getOrientation() const {
		return _orientation;
	}
	std::shared_ptr<theme> scrollBar::getTheme() const {
		return _theme;
	}

	void scrollBar::setValue(f64 value) {
		f64 new_val = Math::clamp(value, 0.0, 1.0);
		if (_value != new_val) {
			valueChangedData e(_value, new_val);
			_value = new_val;
			refresh();
			_on_value_changed.notify(*this, e);
		}
	}
	void scrollBar::setHandleSize(f64 size) {
		_handle_size = Math::clamp(size, 0.01, 1.0);
		refresh();
	}
	void scrollBar::setOrientation(orientation orientation) {
		_orientation = orientation;
		refresh();
	}
	void scrollBar::setStep(f64 step) {
		_step = step;
	}
	void scrollBar::setTheme(std::shared_ptr<theme> theme) {
		_theme = theme;
		refresh();
	}
	observable<void, control&, scrollBar::valueChangedData&>& scrollBar::onValueChanged() {
		return _on_value_changed;
	}

	void scrollBar::onPaintScrollBar(control& sender, paintData& e) {
		scrollBar& sb = static_cast<scrollBar&>(sender);
		if (sb._theme == nullptr)
			return;

		paint& gfx = e.getPaint();
		vector2<f32> size = sender.getClientSize();
		gfx.setClip({ {}, size });
		theme::select select = theme::parse(sb.isEnabled(), sb.isCursorOver(), false, false);

		std::shared_ptr<const paint::brush> bg = sb._theme->getBackground(select);
		std::shared_ptr<const paint::brush> fg = sb._theme->getForeground(select);
		std::shared_ptr<const paint::brush> ol = sb._theme->getOutline(select);
		
		// FILL BACKGROUND
		if (bg != nullptr)
			gfx.fillRect({ 1.0f, 1.0f, size.x - 1.0f, size.y - 1.0f }, *bg);

		// FILL HANDLE
		if (fg != nullptr) {
			bounds2<f32> handle_bounds;
			f64 h_offset	= 2.0f;
			f64 h_size		= 0.0f;
			
			if (
				sb._orientation == orientation::horizontal ||
				(sb._orientation == orientation::automatic && (size.x >= size.y))) {

				h_size = (size.x - 4.0f) * sb._handle_size;

				handle_bounds.from.x	= Math::lerp(sb._value, h_offset, (f64)(size.x - h_size - h_offset));
				handle_bounds.to.x		= Math::lerp(sb._value, h_size + 2.0f, size.x - h_offset);
				handle_bounds.from.y	= 2;
				handle_bounds.to.y		= size.y - 2;

			}
			else if (
				sb._orientation == orientation::vertical ||
				(sb._orientation == orientation::automatic && (size.y >= size.x))) {

				h_size = (size.y - 4.0f) * sb._handle_size;

				handle_bounds.from.x	= 2;
				handle_bounds.to.x		= size.x - 2;
				handle_bounds.from.y	= Math::lerp(sb._value, h_offset, (f64)(size.y - h_size - h_offset));
				handle_bounds.to.y		= Math::lerp(sb._value, h_size + 2.0f, size.y - h_offset);
			}

			gfx.fillRect(handle_bounds, *fg);


		}

		// DRAW OUTLINE
		if (ol != nullptr) {
			paint::pen pen(*ol, 1.0f);
			gfx.drawRect({ 0.0f, 0.0f, size.x - 1.0f, size.y - 1.0f }, pen);
		}
	}
	void scrollBar::onScrollScrollBar(control& sender, scrollData& e) {
		scrollBar& sb = static_cast<scrollBar&>(sender);
		sb.setValue(sb._value - e.getScrollDistance() * sb._step);
	}
	void scrollBar::onMouseDownScrollBar(control& sender, mouseDownData& e) {
		if (e.getButton() != key::leftMouseButton)
			return;

		scrollBar& sb		= static_cast<scrollBar&>(sender);
		vector2<i32> size	= sender.getClientSize();
		i32 y				= e.getCursorPos().y;
		f32 val				= (f32)y / size.y;
		sb.setValue(val);
	}
}