#include "../theme.h"
namespace cauldron::gui {
	theme::theme(
		std::shared_ptr<paint::brush> bg_normal,
		std::shared_ptr<paint::brush> bg_disabled,
		std::shared_ptr<paint::brush> bg_hover,
		std::shared_ptr<paint::brush> bg_hold,
		std::shared_ptr<paint::brush> bg_focus,

		std::shared_ptr<paint::brush> fg_normal,
		std::shared_ptr<paint::brush> fg_disabled,
		std::shared_ptr<paint::brush> fg_hover,
		std::shared_ptr<paint::brush> fg_hold,
		std::shared_ptr<paint::brush> fg_focus,

		std::shared_ptr<paint::brush> ol_normal,
		std::shared_ptr<paint::brush> ol_disabled,
		std::shared_ptr<paint::brush> ol_hover,
		std::shared_ptr<paint::brush> ol_hold,
		std::shared_ptr<paint::brush> ol_focus) : 
		_background{
			bg_normal,
			bg_disabled,
			bg_hover,
			bg_hold,
			bg_focus },
		_foreground{
			fg_normal,
			fg_disabled,
			fg_hover,
			fg_hold,
			fg_focus },
		_outline{
			ol_normal,
			ol_disabled,
			ol_hover,
			ol_hold,
			ol_focus } {}
	
	std::shared_ptr<const paint::brush> theme::getBackground(select sel) {
		if ((i32)sel >= 0 && (i32)sel < 5)
			return _background[(i32)sel];
		return
			nullptr;
	}

	std::shared_ptr<const paint::brush> theme::getForeground(select sel) {
		if ((i32)sel >= 0 && (i32)sel < 5)
			return _foreground[(i32)sel];
		return
			nullptr;
	}
	std::shared_ptr<const paint::brush> theme::getOutline(select sel) {
		if ((i32)sel >= 0 && (i32)sel < 5)
			return _outline[(i32)sel];
		return
			nullptr;
	}

	theme::select theme::parse(bool enabled, bool hovering, bool hold, bool focused) {
		if (!enabled)
			return select::disabled;



		if (hovering)
			if (hold)
				return select::hold;
			else
				return select::hover;
		else if (hold)
			return select::hover;


		if (focused)
			return select::focus;

		return select::normal;
	}
}