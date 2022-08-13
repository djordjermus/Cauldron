#include "anchoredControl.h"
#include "theme.h"
#include "orientation.h"
#pragma once
namespace cauldron::gui {
	class scrollBar : public anchoredControl {
	public:
		scrollBar();

		class valueChangedData : public common::eventData {
		public:
			valueChangedData(f64 old_val, f64 new_val);
			f64 getNewValue() const;
			f64 getOldValue() const;

		private:
			f64 _old;
			f64 _new;
		};

		f64 getValue() const;
		f64 getHandleSize() const;
		f64 getStep() const;
		orientation getOrientation() const;
		std::shared_ptr<theme> getTheme() const;

		virtual void setValue(f64 value);
		virtual void setHandleSize(f64 size);
		virtual void setOrientation(orientation orientation);
		virtual void setStep(f64 step);
		virtual void setTheme(std::shared_ptr<theme> theme);

		common::observable<void, control&, valueChangedData&>& onValueChanged();

	private:
		f64 _value =
			0.0f;
		f64 _handle_size =
			0.1f;
		f64 _step =
			0.05f;

		orientation _orientation =
			orientation::automatic;
		std::shared_ptr<theme> _theme =
			nullptr;
		common::observable<void, control&, valueChangedData&> _on_value_changed =
			common::observable<void, control&, valueChangedData&>();

		static void onPaintScrollBar(control& sender, paintData& e);
		static void onScrollScrollBar(control& sender, scrollData& e);
		static void onMouseDownScrollBar(control& sender, mouseDownData& e);
	};
}