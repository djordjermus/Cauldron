#include "anchoredControl.h"
#include "theme.h"
#include <memory>
#pragma once
namespace cauldron::gui {
	class button : public anchoredControl {
	public:
		button();

		std::shared_ptr<theme> getTheme() const;

		virtual void setTheme(std::shared_ptr<theme> new_theme);
		virtual void setText(const std::wstring& new_text);

		common::observable<void, control&, common::eventData&>& onClick();
		
	private:
		std::wstring _text =
			L"";
		std::shared_ptr<theme> _theme =
			nullptr;
		bool _mouse_dn =
			false;
		common::observable<void, control&, common::eventData&> _on_click =
			common::observable<void, control&, common::eventData&>();

		static void onPaintButton(control& sender, paintData& e);
		static void onMouseDownButton(control& sender, mouseDownData& e);
		static void onDoubleClickButton(control& sender, doubleClickData& e);
		static void onMouseUpButton(control& sender, mouseUpData& e);
		static void onCursorLeaveButton(control& sender, cursorLeaveData& e);
	};
}
