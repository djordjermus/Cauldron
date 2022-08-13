#include "../picture.h"
namespace cauldron::gui {
	using namespace cauldron::common;



	picture::picture() :
		anchoredControl() {

		onPaint().subscribe(onPaintPicture);
	}
	std::shared_ptr<paint::image> picture::getImage() const {
		return _image;
	}
	picture::mode picture::getMode() const {
		return _mode;
	}
	std::shared_ptr<paint::brush> picture::getBackground() const {
		return _brush;
	}

	void picture::setImage(std::shared_ptr<paint::image> new_image) {
		_image = new_image;
		refresh();
	}
	void picture::setMode(mode new_mode) {
		_mode = new_mode;
		refresh();
	}
	void picture::setBackground(std::shared_ptr<paint::brush> background) {
		_brush = background;
		refresh();
	}

	void picture::onPaintPicture(control& sender, paintData& e) {
		picture& pic = static_cast<picture&>(sender);
		paint& gfx = e.getPaint();
		vector2<f32> size = sender.getClientSize();

		bounds2<f32> bounds = { {}, size };
		if (pic._image == nullptr) {
			if(pic._brush != nullptr)
				gfx.fillRect({ {}, size }, *pic._brush);
			return;
		}
		
		switch (pic._mode) {
		break; case mode::fit: {
				f32 img_ratio	= (f32)pic._image->getWidth() / (f32)pic._image->getHeight();
				f32 ctrl_ratio	= (f32)size.x / (f32)size.y;
			
				// Width > Height (CLIP WIDTH)
				if (img_ratio > ctrl_ratio) {
					f32 offset		= (size.y * (ctrl_ratio / img_ratio) - size.y) * 0.5f;
					bounds.from.y	-= offset;
					bounds.to.y		+= offset;
				}
				else {
					f32 offset		= (size.x / (ctrl_ratio / img_ratio) - size.x) * 0.5f;
					bounds.from.x	-= offset;
					bounds.to.x		+= offset;
				}
		}
		break; case mode::clip: {
				f32 img_ratio	= (f32)pic._image->getWidth() / (f32)pic._image->getHeight();
				f32 ctrl_ratio	= (f32)size.x / (f32)size.y;
			
				// Width > Height (CLIP WIDTH)
				if (img_ratio > ctrl_ratio) {
					f32 offset		= (size.x * (img_ratio / ctrl_ratio) - size.x) * 0.5f;
					bounds.from.x	-= offset;
					bounds.to.x		+= offset;
				}
				else {
					f32 offset		= (size.y * (ctrl_ratio / img_ratio) - size.y) * 0.5f;
					bounds.from.y	-= offset;
					bounds.to.y		+= offset;
				}
			}
		}

		// BACKGROUND
		if (pic._mode == mode::fit && pic._brush != nullptr) {
			// PRE IMAGE BACKGROUND
			if(bounds.from.x == 0)
				gfx.fillRect({ 0.0f, 0.0f, size.x, bounds.from.y }, *pic._brush);
			else 
				gfx.fillRect({ 0.0f, 0.0f, bounds.from.x, size.y }, *pic._brush);
			// POST IMAGE BACKGROUND
			if (bounds.to.x == size.x)
				gfx.fillRect({ 0.0f, bounds.to.y, size.x, size.y }, *pic._brush);
			else
				gfx.fillRect({ bounds.to.x, 0.0f, size.x, size.y }, *pic._brush);
		}
		// IMAGE
		if (pic._image != nullptr)
			gfx.drawImage(bounds, *pic._image);

	}
}