#include "cauldron-platform/_include.h"
#include "cauldron-gui/_include.h"
#pragma once
using namespace cauldron::common;
namespace gui = cauldron::gui;
namespace plt = cauldron::platform;
class pizzaForm : public gui::window {
public:
	pizzaForm() = default;
	void start();
private:

	// DATA

	gui::textInput	_ti_name;
	gui::textInput	_ti_lastname;

	gui::anchoredGroup _gr_type;
	gui::label _lb_type;
	std::shared_ptr<std::vector<gui::checkInput*>> _group_type;
	gui::checkInput _ci_type[4];

	gui::anchoredGroup _gr_size;
	gui::label _lb_size;
	std::shared_ptr<std::vector<gui::checkInput*>> _group_size;
	gui::checkInput _ci_size[3];

	gui::anchoredGroup _gr_options;
	gui::label _lb_options;
	gui::checkInput _ci_options[3];

	gui::textInput	_ti_address;

	gui::button		_btn_submit;

	void onPaintPizzaForm(control& sender, paintData& e);
	void onSizingPizzaForm(control& sender, sizingData& e);
	void onSubmit(control& sender, eventData& e);
	static void validateName(control& sender, gui::textInput::validationData& e);
	static void validateLastName(control& sender, gui::textInput::validationData& e);
};