#include "../scrollControl.h"
#include "../defaults.h"
namespace cauldron::gui {
	//using panControl = scrollControl::panControl;
	//
	//scrollControl::scrollControl() : _pan() {
	//	control::adopt(&_pan);
	//}
	//
	////std::shared_ptr<theme> scrollControl::getTheme() const {
	////	return _theme;
	////}
	//anchoredControl& scrollControl::getPanningControl() {
	//	return _pan;
	//}
	//
	////void scrollControl::setTheme(std::shared_ptr<theme> theme) {
	////	_theme = theme;
	////	refresh();
	////}
	//
	//void scrollControl::adopt(control* child) {
	//	_pan.adopt(child);
	//}
	//
	//
	//panControl::panControl() : _theme(defaults::getTheme()) {
	//	onPaint().subscribe(onPaintPanControl);
	//}
	//std::shared_ptr<theme> panControl::getTheme() const {
	//	return _theme;
	//}
	//
	//void panControl::setTheme(std::shared_ptr<theme> theme) {
	//	_theme = theme;
	//	refresh();
	//}
	//
	//void panControl::onPaintPanControl(control& sender, paintData& e) {
	//	panControl& pc = static_cast<panControl&>(sender);
	//	if (pc._theme == nullptr)
	//		return;
	//
	//	theme::select select = theme::parse(pc.isEnabled(), false, false, false);
	//	std::shared_ptr<const paint::brush> br = pc._theme->getBackground(select);
	//
	//	paint::solidBrush b(0x0000FFFF);
	//	auto sz = sender.getClientSize();
	//	if (br)
	//		e.getPaint().fillRect({ {}, sender.getClientSize()}, b);
	//
	//
	//}
}