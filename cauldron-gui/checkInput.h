#include "anchoredControl.h"
#include "theme.h"
#include <string>
#pragma once
namespace cauldron::gui {


	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // C H E C K   I N P U T - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	class checkInput : public anchoredControl {
	public:
		checkInput();

		// Event data

		class valueChangedData : public common::eventData {
		public:
			valueChangedData(bool value);
			bool getNewValue() const;

		private:
			bool _value;
		};

		// Getters

		std::shared_ptr<theme> getTheme() const;
		std::shared_ptr<paint::font> getFont() const;
		std::wstring getText() const;
		bool getValue() const;
		std::shared_ptr<std::vector<checkInput*>> getRadioGroup() const;

		//
		// Setters

		virtual void setTheme(std::shared_ptr<theme> new_theme);
		virtual void setFont(std::shared_ptr<paint::font> new_font);
		virtual void setText(const std::wstring new_text);
		virtual void setValue(bool new_value);
		virtual void setRadioGroup(std::shared_ptr<std::vector<checkInput*>> radio_group);

		common::observable<void, control&, valueChangedData&>& onValueChanged();

		static void normalizeGroup(std::shared_ptr<std::vector<checkInput*>> radio_group, checkInput* set);

	private:
		std::shared_ptr<theme> _theme;
		std::shared_ptr<paint::font> _font;

		std::shared_ptr<std::vector<checkInput*>> _group =
			nullptr;

		std::wstring _text =
			L"";
		bool _value =
			false;

		common::observable<void, control&, valueChangedData&> _on_value_changed =
			common::observable<void, control&, valueChangedData&>();

		static void onCheckInputPaint(control& sender, paintData& e);
		static void onCheckInputMouseUp(control& sender, mouseUpData& e);
		static void onCheckInputKeyUp(control& sender, keyUpData& e);
	};
}