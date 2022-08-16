#include "../fillbar.h"
#include "../defaults.h"
namespace cauldron::gui {
	using namespace cauldron::common;



	fillbar::fillbar() :
		anchoredControl(), _theme(defaults::getTheme()) {

		onPaint().subscribe(paintFillbar);
	}

	using valueChangedData = fillbar::valueChangedData;
	valueChangedData::valueChangedData(f64 old_value, f64 new_value) :
		_old(old_value), _new(new_value) {
	}
	f64 valueChangedData::getOldValue() const {
		return _old;
	}
	f64 valueChangedData::getNewValue() const {
		return _new;
	}


	f64 fillbar::getValue() const {
		return _value;
	}
	bool fillbar::isPaintedAsFocusedWhenFull() const {
		return _paint_focused;
	}
	orientation fillbar::getOrientation() const {
		return _orientation;
	}
	std::shared_ptr<theme> fillbar::getTheme() const {
		return _theme;
	}

	void fillbar::setValue(f64 value) {
		f64 new_val = value > 1.0f ? 1.0f : value < 0.0f ? 0.0f : value;
		if (_value != new_val) {
			valueChangedData e(_value, new_val);
			_value = new_val;
			_on_value_changed.notify(*this, e);

			refresh();
		}
	}
	void fillbar::setPaintAsFocusedWhenFull(bool enable) {
		_paint_focused = enable;
		refresh();
	}
	void fillbar::setOrientation(orientation new_orientation) {
		_orientation = new_orientation;
		refresh();
	}
	void fillbar::setTheme(std::shared_ptr<theme> new_theme) {
		_theme = new_theme;
		refresh();
	}

	observable<void, control&, valueChangedData&>& fillbar::onValueChanged() {
		return _on_value_changed;
	}

	void fillbar::paintFillbar(control& sender, paintData& e) {
		fillbar& fb = static_cast<fillbar&>(sender);
		if (fb._theme == nullptr)
			return;

		theme::select sel = theme::parse(
			fb.isEnabled(), 
			false, 
			false, 
			fb._paint_focused && (fb._value == 1.0f));

		std::shared_ptr<const paint::brush> bg = fb._theme->getBackground(sel);
		std::shared_ptr<const paint::brush> fg = fb._theme->getForeground(sel);
		std::shared_ptr<const paint::brush> ol = fb._theme->getOutline(sel);

		paint& p = e.getPaint();
		p.setSmoothing(false);

		vector2<f32> size = sender.getClientSize().as<f32>();
		bounds2<f32> bounds = bounds2<f32>(0.0f, 0.0f, size.x, size.y);
		
		// FILL EMPTY AND FILL
		if (fg != nullptr) {
			bounds2<f32> fill_bounds =
				bounds2<f32>(0.0f, 0.0f, 0.0f, 0.0f);
			bounds2<f32> empty_bounds =
				bounds2<f32>(0.0f, 0.0f, size.x, size.y);

			if (fb._orientation == orientation::horizontal ||
				(fb._orientation == orientation::automatic && size.x >= size.y)) {

				fill_bounds.from.x	= 1.0f;
				fill_bounds.from.y	= 1.0f;
				fill_bounds.to.x	= (size.x - 1.0f) * fb._value;
				fill_bounds.to.y	= size.y - 1.0f;

				// FILL BACKGROUND
				empty_bounds = { fill_bounds.to.x, 1.0f, size.x - 1.0f, size.y - 1.0f};
			}
			else if (fb._orientation == orientation::vertical ||
				(fb._orientation == orientation::automatic && size.y >= size.x)) {

				fill_bounds.from.x	= 1.0f;
				fill_bounds.from.y	= (size.y - 1.0f) * (1.0f - fb._value);
				fill_bounds.to.x	= size.x - 1.0f;
				fill_bounds.to.y	= size.y - 1.0f;

				// FILL BACKGROUND
				empty_bounds = { 1.0f, 1.0f, size.x - 1.0f, fill_bounds.to.y };
			}

			if (bg != nullptr)
				p.fillRect(empty_bounds, *bg);

			if (fg != nullptr)
				p.fillRect(fill_bounds, *fg);
		}

		// Draw edge
		if (ol != nullptr) {
			paint::pen pen(*ol, 2.0f);
			p.drawRect({ {}, size }, pen);
		}
	}
}
