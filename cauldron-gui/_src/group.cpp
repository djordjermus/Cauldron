#include "../group.h"
#include "../defaults.h"
namespace cauldron::gui {
	using namespace cauldron::common;



	group::group() :
		anchoredControl(), _theme(defaults::getTheme()) {
		setFocusStyle(focusStyle::defer_to_child);

		onPaint()		.subscribe(onPaintGroup);
		onCursorEnter()	.subscribe(refreshOnEvent<cursorEnterData&>);
		onCursorLeave()	.subscribe(refreshOnEvent<cursorLeaveData&>);
		onGainFocus()	.subscribe(refreshOnEvent<gainFocusData&>);
		onLoseFocus()	.subscribe(refreshOnEvent<loseFocusData&>);
	}

	std::shared_ptr<theme> group::getTheme() const {
		return _theme;
	}
	void group::setTheme(std::shared_ptr<theme> theme) {
		_theme = theme;
		refresh();
	}
	void group::onPaintGroup(control& sender, paintData& e) {
		group& gr = static_cast<group&>(sender);
		if (gr._theme == nullptr)
			return;

		paint& gfx = e.getPaint();
		vector2<f32> size = sender.getClientSize();
		theme::select select = theme::parse(gr.isEnabled(), false, false, false);
		
		std::shared_ptr<const paint::brush> bg = gr._theme->getBackground(select);
		std::shared_ptr<const paint::brush> ol = gr._theme->getOutline(select);

		// BACKGROUND
		if (bg != nullptr)
			gfx.fillRect({ {}, size }, *bg);

		// OUTLINE
		if (ol != nullptr)
			gfx.drawRect({ {}, size - vector2<f32>(1, 1)}, *ol);
	}
}