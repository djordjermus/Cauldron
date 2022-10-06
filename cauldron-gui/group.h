#pragma once
#include "anchoredControl.h"
#include "theme.h"
namespace cauldron::gui {

	// Keeps track of child controls
	// Derived classes must also derive from gui::control
	class group {
	public:
		group() = default;
		virtual bool adopt(control& ctrl);
		
	private:
		static bool adopt(group* groupControl, control* child);

		std::vector<control*> _children;
	};

	class anchoredGroup : public anchoredControl, public group {
	public:
		anchoredGroup();

		std::shared_ptr<theme> getTheme() const;

		virtual bool setTheme(std::shared_ptr<theme> theme);

	private:
		std::shared_ptr<theme> _theme;
		static void onPaintAnchoredGroup(control& sender, paintData& e);
	};
}