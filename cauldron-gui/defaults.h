#include "paint.h"
#include "theme.h"
#include <memory>
#pragma once
namespace cauldron::gui::defaults {
	std::shared_ptr<paint::font> getFont();
	std::shared_ptr<paint::font> getHintFont();
	std::shared_ptr<theme> getLightTheme();
	std::shared_ptr<theme> getTheme();
}