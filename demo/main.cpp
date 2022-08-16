#include "cauldron-common/_include.h"
#include "cauldron-platform/_include.h"
#include "cauldron-gui/_include.h"
#include "demoApp.h"
#include "matrix.h"
#include <iostream>
#include <iomanip>
#include "cauldron-ecs/_include.h"

using namespace cauldron::common;
namespace plt = cauldron::platform;
namespace gui = cauldron::gui;
namespace ecs = cauldron::ecs;

demoApp app;
int main() {
	
	app.run();
	return 0;
}

void demoApp::run() {

	gui::control::style window_style =
		gui::control::style::bordered |
		gui::control::style::resizable |
		gui::control::style::captioned |
		gui::control::style::minimize_button |
		gui::control::style::maximize_button;

	bounds2<i32> window_bounds =
		gui::control::adjustBoundsForStyle({ {200, 200}, {640, 480} }, window_style);

	parent.setStyle(window_style);
	parent.setBounds(window_bounds);
	parent.setState(gui::control::state::normal);
	parent.setCaption(L"Cauldron a2.0.3");
	parent.setFocusStyle(gui::control::focusStyle::unfocusable);
	parent.onPaint().subscribe(
		callback<void, gui::control&, gui::control::paintData&>::
		make<demoApp, &demoApp::onPaintWhite>(this));
	parent.onSizing().subscribe(
		callback<void, gui::control&, gui::control::sizingData&>::
		make<demoApp, &demoApp::limitWindowSize>(this));
	parent.onClose().subscribe(gui::control::terminateOnClose);

	parent.adopt(&label);
	label.setText(L"Hello world from an anchored gui::label");
	label.setAnchor({ 0.25f, 0.f, 0.75f, 0.f });
	label.setOffset({ 5, 5, -5, 40 });
	
	parent.adopt(&fillbar1);
	fillbar1.setValue(0.0);
	fillbar1.setAnchor({ 0.0f, 1.0f, 1.0f, 1.0f });
	fillbar1.setOffset({ 2, -36, -40, -20 });
	fillbar1.setPaintAsFocusedWhenFull(false);
	fillbar1.onScroll().subscribe(
		callback<void, gui::control&, gui::control::scrollData&>::
		make<demoApp, &demoApp::onFillbarScroll>(this));
	
	parent.adopt(&fillbar2);
	fillbar2.setValue(0.0);
	fillbar2.setAnchor({ 1.0f, 0.f, 1.0f, 1.0f });
	fillbar2.setOffset({ -36, 2, -20, -40 });
	fillbar2.onScroll().subscribe(
		callback<void, gui::control&, gui::control::scrollData&>::
		make<demoApp, &demoApp::onFillbarScroll>(this));
	
	button1.onClick().subscribe(
		callback<void, gui::control&, eventData&>::
		make<demoApp, &demoApp::clicked>(this));
	parent.adopt(&button1);
	button1.setText(L"button 1");
	button1.setDoubleBuffered(true);
	button1.setFocusStyle(gui::control::focusStyle::focusable);
	button1.setAnchor({ 0.0f, 0.1f, 0.0f, 0.1f });
	button1.setOffset({ { 5, 0}, {200, 30 } });
	
	parent.adopt(&button2);
	button2.setText(L"button 2");
	button2.setFocusStyle(gui::control::focusStyle::focusable);
	button2.setAnchor({ 0.0f, 0.1f, 0.0f, 0.1f });
	button2.setOffset({ { 5, 40}, {200, 30 } });
	
	for (i32 i = 0; i < 3; i++) {
		parent.adopt(&checkInput[i]);
		checkInput[i].setAnchor({ 0.0f, 0.1f, 0.0f, 0.1f });
		checkInput[i].setOffset({ { 5.0f, 80.0f + 26 * i}, {130.0f, 16.0f } });
		checkInput[i].setFocusStyle(gui::control::focusStyle::focusable);
		checkInput[i].setText(L"check input");
		checkInput[i].setDoubleBuffered(true);
	}
	std::shared_ptr<std::vector<gui::checkInput*>> radio_group = std::make_shared<std::vector<gui::checkInput*>>();
	radio_group->push_back(&radioInput[0]);
	radio_group->push_back(&radioInput[1]);
	radio_group->push_back(&radioInput[2]);
	for (i32 i = 0; i < 3; i++) {
		parent.adopt(&radioInput[i]);
		radioInput[i].setRadioGroup(radio_group);
		radioInput[i].setAnchor({ 0.0f, 0.1f, 0.0f, 0.1f });
		radioInput[i].setOffset({ { 5.0f, 80.0f + 26 * (i + 4)}, {130.0f, 16.0f} });
		radioInput[i].setFocusStyle(gui::control::focusStyle::focusable);
		radioInput[i].setText(L"radio input");
		radioInput[i].setDoubleBuffered(true);
	}
	gui::checkInput::normalizeGroup(radio_group, checkInput);
	
	parent.adopt(&picture);
	picture.setAnchor({ 0.33f, 0.33f, 0.67f, 0.67f });
	picture.setOffset({ 20, 20, -20, -20});
	picture.setImage(std::make_shared<gui::paint::image>(L"C:\\Users\\Admin\\Desktop\\img.png"));
	picture.setMode(gui::picture::mode::fit);
	picture.setBackground(std::make_shared<gui::paint::solidBrush>(0x141414FF));
	
	parent.adopt(&scrollBar1);
	scrollBar1.setFocusStyle(gui::control::focusStyle::focusable);
	scrollBar1.setAnchor({ 1.0f, 0.0f, 1.0f, 1.0f });
	scrollBar1.setOffset({ -18, 2, -2, -26 });
	
	parent.adopt(&scrollBar2);
	scrollBar2.setFocusStyle(gui::control::focusStyle::focusable);
	scrollBar2.setAnchor({ 0.0f, 1.0f, 1.0f, 1.0f });
	scrollBar2.setOffset({ 2, -18, -26, -2 });

	parent.refresh();
	plt::message m;
	while (parent.isValid()) {
		m.awaitPull();
		m.dispatch();
	}
}

void demoApp::onPaintWhite(gui::control& sender, gui::control::paintData& e) {
	static gui::paint::solidBrush sb(0x141414FF);
	e.getPaint().fillRect({ {}, sender.getClientSize() }, sb);
}
void demoApp::setBoundsOnMouseUp(gui::control& sender, gui::control::mouseUpData& e) {
	sender.setBounds({ 200, 200, 500, 500 });
}
void demoApp::onFillbarScroll(gui::control& sender, gui::control::scrollData& e) {
	gui::fillbar& fb = static_cast<gui::fillbar&>(sender);
	fb.setValue(fb.getValue() + e.getScrollDistance() * 0.02);
}
void demoApp::onPaintLabel(gui::control& sender, gui::control::paintData& e) {
	static gui::paint::solidBrush br(0xFF00FFFF);
	e.getPaint().fillArc({ {}, sender.getClientSize() }, { 0, Math::tau / 6.0f }, br);
}
void demoApp::clicked(gui::control& sender, eventData& e) {
	std::cout << "CLICKED!\n";
}
void demoApp::valueChanged(gui::control& sender, gui::fillbar::valueChangedData& e) {
	std::cout << "VALUE CHANGED: " << e.getNewValue() << '\n';
}
void demoApp::fillbarMD(gui::control& sender, gui::fillbar::mouseDownData& e) {
	gui::fillbar& fb = static_cast<gui::fillbar&>(sender);
	fb.setPaintAsFocusedWhenFull(!fb.isPaintedAsFocusedWhenFull());
}
void demoApp::valueChangedCI(gui::control& sender, gui::checkInput::valueChangedData& e) {
	std::cout << "VALUE CHANGED: " << e.getNewValue() << "\n";
}
void demoApp::limitWindowSize(gui::control& sender, gui::control::sizingData& e) {
	gui::control::limitSizingWidth(e, { 640, 1280 });
	gui::control::limitSizingHeight(e, { 480, 720 });
}