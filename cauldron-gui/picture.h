#include "anchoredControl.h"
#include <memory>
#pragma once
namespace cauldron::gui {
	class picture : public anchoredControl {
	public:
		picture();
		enum mode : i32;

		std::shared_ptr<paint::image> getImage() const;
		mode getMode() const;
		std::shared_ptr<paint::brush> getBackground() const;

		virtual void setImage(std::shared_ptr<paint::image> new_image);
		virtual void setMode(mode new_mode);
		virtual void setBackground(std::shared_ptr<paint::brush> background);

		enum mode : i32 {
			// Stretches image on x and y axes
			stretch	= 0,
			// Fits image into bounds of the picture control without cutting of any part of it
			fit		= 1,
			// Image takes whole space of the control without altering its aspect ratio
			clip	= 2
		};
	private:
		std::shared_ptr<paint::image> _image =
			nullptr;
		std::shared_ptr<paint::brush> _brush =
			nullptr;
		mode _mode =
			mode::stretch;

		static void onPaintPicture(control& sender, paintData& e);
	};
}