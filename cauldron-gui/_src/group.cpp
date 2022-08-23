#include "../group.h"
#include "../defaults.h"
#include <Windows.h>
namespace cauldron::gui {
	bool group::adopt(control& ctrl) { return adopt(this, &ctrl); }
	bool group::adopt(group* groupControl, control* child) {
		control* gr = dynamic_cast<control*>(groupControl);
		if (gr != nullptr) {
			if (::SetParent((HWND)child->getCore(), (HWND)gr->getCore()) == FALSE)
				return false;

			control* old = child->_parent;
			::SetWindowLongW((HWND)child->getCore(), GWL_STYLE, WS_CHILD);
			child->_parent = gr;
			control::changeParentData e(child, old, gr);
			child->onChangeParent().notify(*child, e);

			return true;
		}
		return false;
	}

	anchoredGroup::anchoredGroup() : 
		_theme(defaults::getTheme()) {
		onPaint().subscribe(onPaintAnchoredGroup);
	}
	std::shared_ptr<theme> anchoredGroup::getTheme() const {
		return _theme;
	}
	bool anchoredGroup::setTheme(std::shared_ptr<theme> theme) {
		_theme = theme;
		refresh();
		return true;
	}
	void anchoredGroup::onPaintAnchoredGroup(control& sender, paintData& e) {
		anchoredGroup& ag = static_cast<anchoredGroup&>(sender);
		if (ag._theme == nullptr)
			return;

		std::shared_ptr<const paint::brush> bg = 
			ag._theme->getBackground(theme::select::normal);
		std::shared_ptr<const paint::brush> ol =
			ag._theme->getOutline(theme::select::normal);

		auto sz = sender.getClientSize();
		if (bg != nullptr);
			e.getPaint().fillRect({ {}, sz }, *bg);
		if (ol != nullptr) {
			e.getPaint().drawRect({ {}, sz - common::v2i32(1, 1)}, paint::pen(*ol, 1.0f));
		}
	}
}