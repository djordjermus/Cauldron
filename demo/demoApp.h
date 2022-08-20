#include "cauldron-common/_include.h"
#include "cauldron-gui/_include.h"
#pragma once
namespace gui = cauldron::gui;
namespace common = cauldron::common;
class demoApp {
public:
	void run();

private:
	gui::control parent;
	gui::label label;
	gui::fillbar fillbar1;
	gui::fillbar fillbar2;
	gui::button button1;
	gui::button button2;
	gui::checkInput checkInput[3];
	gui::checkInput radioInput[3];
	gui::picture picture;
	gui::scrollBar scrollBar1;
	gui::scrollBar scrollBar2;
	gui::textInput textInput[2];
	std::shared_ptr<gui::theme> theme =
		nullptr;
	void onPaintWhite(gui::control& sender, gui::control::paintData& e);
	void setBoundsOnMouseUp(gui::control& sender, gui::control::mouseUpData& e);
	void onFillbarScroll(gui::control& sender, gui::control::scrollData& e);
	void onPaintLabel(gui::control& sender, gui::control::paintData& e);
	void clicked(gui::control& sender, common::eventData& e);
	void valueChanged(gui::control& sender, gui::fillbar::valueChangedData& e);
	void fillbarMD(gui::control& sender, gui::fillbar::mouseDownData& e);
	void valueChangedCI(gui::control& sender, gui::checkInput::valueChangedData& e);
	void limitWindowSize(gui::control& sender, gui::control::sizingData& e);
};