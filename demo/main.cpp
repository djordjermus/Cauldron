#include "cauldron-common/_include.h"
#include "cauldron-platform/_include.h"
#include "cauldron-gui/_include.h"
#include "cauldron-gui/group.h"
#include "pizzaForm.h"
#include <locale>
using namespace cauldron::common;
namespace plt = cauldron::platform;
namespace gui = cauldron::gui;

pizzaForm app = pizzaForm();
int main() {
	setlocale(LC_CTYPE, "");
	app.start();
	return 0;
}



















void terminateOnClick(gui::control& sender, gui::control::mouseUpData& e) {
	sender.terminate();
}
void pizzaForm::start() {

	//
	// MAIN WINDOW SETUP
	gui::window::style window_style =
		gui::window::style::bordered |
		gui::window::style::captioned |
		gui::window::style::resizable |
		gui::window::style::minimize_button;
	bounds2<i32> window_bounds =
		{ {200, 200}, {640, 360} };
	
	onClose().subscribe(
		gui::control::terminateOnClose);
	onSizing().subscribe(
		callback<void, control&, sizingData&>::
		make<pizzaForm, &pizzaForm::onSizingPizzaForm>(this));
	onPaint().subscribe(
		callback<void, control&, paintData&>::
		make<pizzaForm, &pizzaForm::onPaintPizzaForm>(this));


	setStyle(window_style);
	setBounds(window_bounds);
	setCaption(L"Pizza online");
	setFocusStyle(gui::control::focusStyle::unfocusable);
	setVisible();

	//
	// TEXT INPUT NAME SETUP
	adopt(_ti_name);
	_ti_name.setFocusStyle(gui::control::focusStyle::focusable);
	_ti_name.setAnchor({0.f, 0.f, 0.5f, 0.f});
	_ti_name.setOffset({ { 10, 10 }, {-20, 30} });
	_ti_name.setHint(L"Ime poručioca");
	_ti_name.onValidate().subscribe(validateName);
	_ti_name.setSelect({0, 0});
	_ti_name.setVisible();

	//
	// TEXT INPUT LASTNAME SETUP
	adopt(_ti_lastname);
	_ti_lastname.setAnchor({ 0.5f, 0.f, 1.f, 0.f });
	_ti_lastname.setOffset({ { 10, 10 }, {-20, 30} });
	_ti_lastname.setHint(L"Prezime poručioca");
	_ti_lastname.onValidate().subscribe(validateLastName);
	_ti_lastname.setVisible();

	//
	// TYPE RADIO BUTTONS SETUP
	adopt(_gr_type);
	_gr_type.setAnchor({ 0, 0, 0.315f, 0 });
	_gr_type.setOffset({ {10, 50}, {-20, 150} });
	_gr_type.setVisible();
	
	_gr_type.adopt(_lb_type);
	_lb_type.setAnchor({ 0.f, 0.f, 1.f, 0.f });
	_lb_type.setOffset({ {1, 1}, {-2, 21} });
	_lb_type.setText(L"Izaberite tip pice");
	_lb_type.setVisible();

	_group_type = std::make_shared<std::vector<gui::checkInput*>>();
	for (auto& ci : _ci_type)
		_group_type->push_back(&ci);
	for (auto& ci : _ci_type)
		ci.setRadioGroup(_group_type);

	for (i32 i = 0; i < (sizeof(_ci_type) / sizeof(*_ci_type)); i++) {
		_gr_type.adopt(_ci_type[i]);
		_ci_type[i].setValue(i == 0);
		_ci_type[i].setAnchor({ 0, 0, 1, 0 });
		_ci_type[i].setOffset({ { 10.f, 30.f + i * 30}, { -20.f, 18.f } });
		_ci_type[i].setText(
			i == 0 ? L"Vezuvio" :
			i == 1 ? L"Margarita" :
			i == 2 ? L"Čikago pica" :
			i == 3 ? L"New York pica" : L"N/A"
		);
		_ci_type[i].setVisible();
	}

	//
	// SIZE RADIO BUTTONS SETUP
	adopt(_gr_size);
	_gr_size.setAnchor({ 0.33f, 0.0f, 0.655f, 0 });
	_gr_size.setOffset({ {10, 50}, {-20, 150} });
	_gr_size.setVisible();

	_gr_size.adopt(_lb_size);
	_lb_size.setAnchor({ 0.f, 0.f, 1.f, 0.f });
	_lb_size.setOffset({ {1, 1}, {-2, 21} });
	_lb_size.setText(L"Izaberite veličinu pice");
	_lb_size.setVisible();

	_group_size = std::make_shared<std::vector<gui::checkInput*>>();
	for (auto& ci : _ci_size)
		_group_size->push_back(&ci);
	for (auto& ci : _ci_size)
		ci.setRadioGroup(_group_size);

	for (i32 i = 0; i < (sizeof(_ci_size) / sizeof(*_ci_size)); i++) {
		_gr_size.adopt(_ci_size[i]);
		_ci_size[i].setValue(i == 0);
		_ci_size[i].setAnchor({ 0, 0, 1, 0 });
		_ci_size[i].setOffset({ { 10.f, 30.f + i * 30}, { -20.f, 18.f } });
		_ci_size[i].setText(
			i == 0 ? L"24cm - mala" :
			i == 1 ? L"36cm - srednja" :
			i == 2 ? L"48cm - velika" : L"N/A"
		);
		_ci_size[i].setVisible();
	}

	//
	// OPTIONS CHECK INPUT SETUP
	adopt(_gr_options);
	_gr_options.setAnchor({ 0.67f, 0.0f, 1.0f, 0 });
	_gr_options.setOffset({ {10, 50}, {-20, 150} });
	_gr_options.setVisible();

	_gr_options.adopt(_lb_options);
	_lb_options.setAnchor({ 0.f, 0.f, 1.f, 0.f });
	_lb_options.setOffset({ {1, 1}, {-2, 21} });
	_lb_options.setText(L"Izaberite dodatne opcije");
	_lb_options.setVisible();

	_group_size = std::make_shared<std::vector<gui::checkInput*>>();
	for (auto& ci : _ci_size)
		_group_size->push_back(&ci);
	for (auto& ci : _ci_size)
		ci.setRadioGroup(_group_size);

	for (i32 i = 0; i < (sizeof(_ci_options) / sizeof(*_ci_options)); i++) {
		_gr_options.adopt(_ci_options[i]);
		_ci_options[i].setValue(i == 0);
		_ci_options[i].setAnchor({ 0, 0, 1, 0 });
		_ci_options[i].setOffset({ { 10.f, 30.f + i * 30}, { -20.f, 18.f } });
		_ci_options[i].setText(
			i == 0 ? L"dodatne masline" :
			i == 1 ? L"dadatan sir" :
			i == 2 ? L"punjena kora" : L"N/A"
		);
		_ci_options[i].setVisible();
	}

	//
	// TEXT INPUT ADDRESS SETUP
	adopt(_ti_address);
	_ti_address.setAnchor({ 0.0f, 0.f, 1.f, 0.f });
	_ti_address.setOffset({ { 10, 210 }, {-20, 30} });
	_ti_address.setHint(L"Adresa poručioca");
	_ti_address.setVisible();

	// SUBMIT BUTTON SETUP
	adopt(_btn_submit);
	_btn_submit.setAnchor({ 0, 1, 1, 1 });
	_btn_submit.setOffset({ {10, -50}, { -20, 40} });
	_btn_submit.setText(L"Naruči");
	_btn_submit.onClick().subscribe(
		callback<void, control&, eventData&>::
		make<pizzaForm, &pizzaForm::onSubmit>(this));
	_btn_submit.setVisible();


	// Pump
	plt::message msg;
	while (isValid()) {
		msg.awaitPull();
		msg.dispatch();
	}
}

#include "cauldron-gui/defaults.h"
void pizzaForm::onPaintPizzaForm(control& sender, paintData& e) {
	auto br = gui::defaults::getTheme()->getBackground(gui::theme::select::normal);
	auto sz = sender.getClientSize();
	if (br != nullptr)
		e.getPaint().fillRect({ {}, sz }, *br);

}
void pizzaForm::onSizingPizzaForm(control& sender, sizingData& e) {
	gui::control::limitSizingWidth(e, { 640, 999999999 });
	gui::control::limitSizingHeight(e, { 360, 999999999 });
}

void pizzaForm::validateName(control& sender, gui::textInput::validationData& e) {
	gui::textInput::validateNotDigit(sender, e);
	gui::textInput::validateNotWhitespace(sender, e);
}
void pizzaForm::validateLastName(control& sender, gui::textInput::validationData& e) {
	gui::textInput::validateNotDigit(sender, e);
	gui::textInput::validateNotWhitespace(sender, e);
}

#include <io.h>
#include <stdio.h>
#include <fcntl.h>
void pizzaForm::onSubmit(control& sender, eventData& e) {
	FILE* out = nullptr;
	_wfopen_s(&out, L"zapisnik.txt", L"a");
	if (out == nullptr)
		return;
	auto ret = _setmode(_fileno(out), _O_WTEXT);
	fwprintf(
		out, 
		L"Narudzbina:\n\tIME: %ls\n\tPREZIME: %ls\n\tADRESA: %ls\n\t", 
		_ti_name.getText().c_str(),
		_ti_lastname.getText().c_str(),
		_ti_address.getText().c_str());

	gui::checkInput* pizza_type = nullptr;
	for (auto& p : _ci_type) {
		if (p.getValue()) {
			pizza_type = &p;
			break;
		}
	}
	if (pizza_type != nullptr)
		fwprintf(out, L"TYPE: %ls\n\t", pizza_type->getText().c_str());

	gui::checkInput* pizza_size = nullptr;
	for (auto& p : _ci_size) {
		if (p.getValue()) {
			pizza_size = &p;
			break;
		}
	}
	if (pizza_size != nullptr)
		fwprintf(out, L"SIZE: %ls\n\t", pizza_size->getText().c_str());

	if (pizza_size != nullptr)
		fwprintf(out, L"OPT: ");
	for (auto& p : _ci_options) {
		if (p.getValue()) 
			fwprintf(out, L"%ls, ", p.getText().c_str());
	}
	fwprintf(out, L"\n");
	fclose(out);
}