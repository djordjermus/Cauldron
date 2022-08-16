#include "anchoredControl.h"
#include "theme.h"
#include "orientation.h"
#include <memory>
#pragma once
namespace cauldron::gui {

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // F I L L B A R   C O N T R O L - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	class fillbar : public anchoredControl {
	public:

		fillbar();

		//
		// Event data

		class valueChangedData : public common::eventData {
		public:
			valueChangedData(f64 old_value, f64 new_value);

			f64 getOldValue() const;
			f64 getNewValue() const;

		private:
			f64 _old;
			f64 _new;
		};

		//
		// Getters

		f64 getValue() const;
		bool isPaintedAsFocusedWhenFull() const;
		orientation getOrientation() const;
		std::shared_ptr<theme> getTheme() const;

		//
		// Setters

		virtual void setValue(f64 value);
		virtual void setPaintAsFocusedWhenFull(bool enable);
		virtual void setOrientation(orientation new_orientation);
		virtual void setTheme(std::shared_ptr<theme> new_theme);

		//
		// Event handlers

		common::observable<void, control&, valueChangedData&>& onValueChanged();

	private:

		//
		// Data

		f64 _value =
			0.0f;
		std::shared_ptr<theme> _theme;

		bool _paint_focused =
			true;
		orientation _orientation =
			orientation::automatic;
		common::observable<void, control&, valueChangedData&> _on_value_changed =
			common::observable<void, control&, valueChangedData&>();

		static void paintFillbar(control& sender, paintData& e);

	};
}