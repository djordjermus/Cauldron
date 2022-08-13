#include "anchoredControl.h"
#include "theme.h"
#include <string>
#pragma once
namespace cauldron::gui {
	class checkInput : public anchoredControl {
	public:
		checkInput();
		class valueChangedData : public common::eventData {
		public:
			valueChangedData(bool value);
			bool getNewValue() const;

		private:
			bool _value;
		};

		std::shared_ptr<theme> getTheme() const;
		bool getValue() const;

		common::observable<void, control&, valueChangedData&>& onValueChanged();

		virtual void setTheme(std::shared_ptr<theme> new_theme);
		virtual void setFont(std::shared_ptr<paint::font> new_font);
		virtual void setText(const std::wstring new_text);
		virtual void setValue(bool new_value);
		virtual void setRadioGroup(std::shared_ptr<std::vector<checkInput*>> radio_group);

		static void normalizeGroup(std::shared_ptr<std::vector<checkInput*>> radio_group, checkInput* set);

	private:
		std::shared_ptr<theme> _theme =
			nullptr;
		std::shared_ptr<paint::font> _font =
			nullptr;

		std::shared_ptr<std::vector<checkInput*>> _group =
			nullptr;

		std::wstring _text =
			L"";
		bool _value =
			false;

		common::observable<void, control&, valueChangedData&> _on_value_changed =
			common::observable<void, control&, valueChangedData&>();

		static void onPaintCheckInput(control& sender, paintData& e);
		static void onMouseUpCheckInput(control& sender, mouseUpData& e);
	};
}