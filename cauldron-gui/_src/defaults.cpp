#include "../defaults.h"
namespace cauldron::gui::defaults {
	std::shared_ptr<paint::font> getFont() {
		static std::shared_ptr<paint::font> ret = 
			std::make_shared<paint::font>(L"consolas", 16.0f);
		return ret;
	}
	std::shared_ptr<paint::font> getHintFont() {
		static std::shared_ptr<paint::font> ret =
			std::make_shared<paint::font>(L"consolas", 16.0f, paint::font::style::italic);
		return ret;
	}

	// TODO Implement a good light theme
	std::shared_ptr<theme> getLightTheme() {
		static std::shared_ptr<theme> ret =
			std::make_shared<gui::theme>(

				// BACKGROUND
				std::make_shared<gui::paint::solidBrush>(0xCCCCCCFF), // NORMAL
				std::make_shared<gui::paint::solidBrush>(0xCCCCCCFF), // DISABLED
				std::make_shared<gui::paint::solidBrush>(0xCCCCCCFF), // HOVER
				std::make_shared<gui::paint::solidBrush>(0xCCCCCCFF), // MOUSE DOWN
				std::make_shared<gui::paint::solidBrush>(0xCCCCCCFF), // FOCUS

				// FOREGROUND
				std::make_shared<gui::paint::solidBrush>(~0xCCCCCCFF + 0xFF), // NORMAL
				std::make_shared<gui::paint::solidBrush>(~0x777777FF + 0xFF), // DISABLED
				std::make_shared<gui::paint::solidBrush>(~0xFFFFFFFF + 0xFF), // HOVER
				std::make_shared<gui::paint::solidBrush>(~0xDDDDDDFF + 0xFF), // MOUSE DOWN
				std::make_shared<gui::paint::solidBrush>(~0xAACCEEFF + 0xFF), // FOCUS

				// OUTLINE
				std::make_shared<gui::paint::solidBrush>(~0xCCCCCC + 0xFF - 0x60606000),
				std::make_shared<gui::paint::solidBrush>(~0x777777 + 0xFF - 0x60606000),
				std::make_shared<gui::paint::solidBrush>(~0xFFFFFF + 0xFF - 0x60606000),
				std::make_shared<gui::paint::solidBrush>(~0xDDDDDD + 0xFF - 0x60606000),
				std::make_shared<gui::paint::solidBrush>(~0xAACCEE + 0xFF - 0x60606000));
		return ret;
	}
	std::shared_ptr<theme> getTheme() {
		static std::shared_ptr<theme> ret = 
			std::make_shared<gui::theme>(

			// BACKGROUND
			std::make_shared<gui::paint::solidBrush>(0x141414FF), // NORMAL
			std::make_shared<gui::paint::solidBrush>(0x141414FF), // DISABLED
			std::make_shared<gui::paint::solidBrush>(0x141414FF), // HOVER
			std::make_shared<gui::paint::solidBrush>(0x141414FF), // MOUSE DOWN
			std::make_shared<gui::paint::solidBrush>(0x141414FF), // FOCUS

			// FOREGROUND
			std::make_shared<gui::paint::solidBrush>(0xCCCCCCFF), // NORMAL
			std::make_shared<gui::paint::solidBrush>(0x777777FF), // DISABLED
			std::make_shared<gui::paint::solidBrush>(0xFFFFFFFF), // HOVER
			std::make_shared<gui::paint::solidBrush>(0xDDDDDDFF), // MOUSE DOWN
			std::make_shared<gui::paint::solidBrush>(0xAACCEEFF), // FOCUS

			// OUTLINE
			std::make_shared<gui::paint::solidBrush>(0xCCCCCCFF - 0x60606000),
			std::make_shared<gui::paint::solidBrush>(0x777777FF - 0x60606000),
			std::make_shared<gui::paint::solidBrush>(0xFFFFFFFF - 0x60606000),
			std::make_shared<gui::paint::solidBrush>(0xDDDDDDFF - 0x60606000),
			std::make_shared<gui::paint::solidBrush>(0xAACCEEFF - 0x60606000));
		return ret;
	}
}