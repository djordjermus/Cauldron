#include "../listBox.h"
namespace cauldron::gui {
	using namespace cauldron::common;



	listBox::listBox() : anchoredControl(), _scroll_bar() {
		onPaint().subscribe(onPaintListBox);

		adopt(&_scroll_bar);
		_scroll_bar.setAnchor({});
		_scroll_bar.setOffset({});
		_scroll_bar.setEnabled(false);
		_scroll_bar.onValueChanged().subscribe(
			callback<void, control&, scrollBar::valueChangedData&>::
			make<listBox, &listBox::scrollView>(this));
	}
	std::shared_ptr<theme> listBox::getTheme() const {
		return _theme;
	}
	scrollBar& listBox::getScrollBar() {
		return _scroll_bar;
	}

	void listBox::setTheme(std::shared_ptr<theme> theme) {
		_theme = theme;
		refresh();
	}
	void listBox::setScrollBarState(bool enabled) {
		if (enabled) {
			_scroll_bar.setEnabled(true);
			_scroll_bar.setAnchor({ 1.0f, 0.0f, 1.0f, 1.0f });
			_scroll_bar.setOffset({-16, 0, 0, 0});
			auto x = getClientSize();
			auto y = _scroll_bar.getClientSize();
			int z = 0;
			// TODO Size list elements
		}
		else {
			_scroll_bar.setEnabled(false);
			_scroll_bar.setAnchor({ 1.0f, 1.0f, 1.0f, 1.0f });
			_scroll_bar.setOffset({ });
			// TODO Size list elements
		}
		
	}
	void listBox::scrollView(control& sender, scrollBar::valueChangedData& e) {
		
	}
	void listBox::onPaintListBox(control& sender, paintData& e) {
		listBox& lb = static_cast<listBox&>(sender);
		if (lb._theme == nullptr)
			return;

		paint& gfx = e.getPaint();
		vector2<f32> size = sender.getClientSize();
		theme::select select = theme::parse(lb.isEnabled(), lb.isCursorOver(), false, lb.isFocused());

		std::shared_ptr<const paint::brush> bg = lb._theme->getBackground(select);
		std::shared_ptr<const paint::brush> fg = lb._theme->getForeground(select);
		std::shared_ptr<const paint::brush> ol = lb._theme->getOutline(select);

		// BACKGROUND
		if (bg != nullptr)
			gfx.fillRect({ {}, size}, *bg);

		// OUTLINE
		if (ol != nullptr) {
			paint::pen pen(*ol, 1.0f);
			gfx.drawRect({ {}, size - vector2<f32>(1, 1) }, pen);
		}
	}
}