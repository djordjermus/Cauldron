#include "anchoredControl.h"
#include "theme.h"
#include "scrollBar.h"
#pragma once
namespace cauldron::gui {
	class listBox : public anchoredControl {
	public:
		listBox();

		std::shared_ptr<theme> getTheme() const;
		scrollBar& getScrollBar();

		virtual void setTheme(std::shared_ptr<theme> theme);
		void setScrollBarState(bool enabled);

	private:
		scrollBar _scroll_bar;
		std::shared_ptr<theme> _theme;
		
		void scrollView(control& sender, scrollBar::valueChangedData& e);
		static void onPaintListBox(control& sender, paintData& e);
	};
}