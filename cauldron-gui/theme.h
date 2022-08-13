#include "paint.h"
#include <memory>
#pragma once
namespace cauldron::gui {
	class theme {
	public:
		struct desc;
		enum class select : i32;

		theme(
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
			std::shared_ptr<paint::brush> ol_focus);

		std::shared_ptr<const paint::brush> getBackground(select sel);
		std::shared_ptr<const paint::brush> getForeground(select sel);
		std::shared_ptr<const paint::brush> getOutline(select sel);

		static select parse(bool enabled, bool hovering, bool hold, bool focused);

		struct desc {
			std::unique_ptr<paint::brush> background[5] = { nullptr };
			std::unique_ptr<paint::brush> foreground[5] = { nullptr };
			std::unique_ptr<paint::brush> outline[5] = { nullptr };
		};
		enum class select : i32 {
			normal,
			disabled,
			hover,
			hold,
			focus
		};

	private:
		std::shared_ptr<paint::brush> _background[5];
		std::shared_ptr<paint::brush> _foreground[5];
		std::shared_ptr<paint::brush> _outline[5];
	};

}