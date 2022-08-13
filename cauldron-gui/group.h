#include "anchoredControl.h"
#include "theme.h"
#pragma once
namespace cauldron::gui {
	class group : public anchoredControl {
	public:
		group();

		std::shared_ptr<theme> getTheme() const;
		void setTheme(std::shared_ptr<theme> theme);

	private:
		std::shared_ptr<theme> _theme;
		static void onPaintGroup(control& sender, paintData& e);
	};
}