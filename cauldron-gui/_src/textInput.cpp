#include "../textInput.h"
#include "../defaults.h"
#include "cauldron-common/vectors.ostream.h"
#include <sstream>
#include <wchar.h>
namespace cauldron::gui {
	using namespace cauldron::common;



	textInput::textInput() :
		anchoredControl(), 
		_theme(defaults::getTheme()), 
		_text_font(defaults::getFont()), 
		_hint_font(defaults::getHintFont()) {
	
		onPaint()		.subscribe(onPaintTextInput);
		onGainFocus()	.subscribe(refreshOnEvent<gainFocusData>);
		onLoseFocus()	.subscribe(onLoseFocusTextInput);
		onCursorLeave()	.subscribe(refreshOnEvent<cursorLeaveData>);
		onCursorEnter()	.subscribe(refreshOnEvent<cursorEnterData>);
		onMouseDown()	.subscribe(onMouseDownTextInput);
		onMouseUp()		.subscribe(onMouseUpTextInput);
		onKeyDown()		.subscribe(onKeyDownTextInput);
		onCharacter()	.subscribe(onCharTextInput);
	}

	textInput::validationData::validationData(const common::vector2<i32>& select, cwstr insert) :
		eventData(), _select(select), _text(insert), _canceled(false) { }
	i32 textInput::validationData::getFirstSelected() const {
		return _select.x;
	}
	i32 textInput::validationData::getSelectRange() const {
		return _select.y;
	}
	cwstr textInput::validationData::getInsertedText() const {
		return _text;
	}
	bool textInput::validationData::isCanceled() const {
		return _canceled;
	}
	void textInput::validationData::cancel() {
		_canceled = true;
	}



	std::shared_ptr<theme> textInput::getTheme() const {
		return _theme;
	}
	std::shared_ptr<const paint::font> textInput::getTextFont() const {
		return _text_font;
	}
	std::shared_ptr<const paint::font> textInput::getHintFont() const {
		return _hint_font;
	}
	std::wstring textInput::getText() const {
		return _text;
	}
	std::wstring textInput::getHint() const {
		return _hint;
	}
	vector2<i32> textInput::getSelect() const {
		return _select;
	}

	void textInput::setTheme(std::shared_ptr<theme> new_theme) {
		_theme = new_theme;
		refresh();
	}
	void textInput::setTextFont(std::shared_ptr<paint::font> new_font) {
		_text_font = new_font;
		refresh();
	}
	void textInput::setHintFont(std::shared_ptr<paint::font> new_font) {
		_hint_font = new_font;
		refresh();
	}
	void textInput::setText(const std::wstring& new_text) {
		_text = new_text;
		refresh();
	}
	void textInput::setHint(const std::wstring& new_hint) {
		_hint = new_hint;
		refresh();
	}
	void textInput::setSelect(const vector2<i32> new_select) {
		_select = new_select;
		if (_select.x > (i64)_text.length())
			_select.x = _text.length();
		if (_select.x < 0) 
			_select.x = 0;

		if (_select.y < 0) 
			_select.y = 0;
		if (_select.x + _select.y > _text.length())
			_select.y = _text.length() - _select.x;
		refresh();
	}
	common::observable<void, control&, textInput::validationData&>& textInput::onValidate() {
		return _on_validate;
	}
	void textInput::validateNotDigit(gui::control& sender, gui::textInput::validationData& e) {
		const wchar_t* rd = e.getInsertedText();
		while (*rd != L'\0') {
			if (iswdigit(*rd)) {
				e.cancel();
				return;
			}
			rd++;
		}
	}
	void textInput::validateNotLetter(gui::control& sender, gui::textInput::validationData& e) {
		const wchar_t* rd = e.getInsertedText();
		while (*rd != L'\0') {
			if (iswalpha(*rd)) {
				e.cancel();
				return;
			}
			rd++;
		}
	}
	void textInput::validateNotWhitespace(gui::control& sender, gui::textInput::validationData& e) {
		const wchar_t* rd = e.getInsertedText();
		while (*rd != L'\0') {
			if (iswspace(*rd)) {
				e.cancel();
				return;
			}
			rd++;
		}
	}

	void textInput::deleteSelection() {
		if (_select.y == 0)
			return;
		u64 last = _select.x + _select.y;
		std::wstringstream ss;
		ss << _text.substr(0, _select.x);
		ss << _text.substr(_select.x + _select.y);
		setText(ss.str());
		setSelect({ _select.x, 0 });
	}
	void textInput::deleteSingle(bool next) {
		if (_select.y != 0)
			return;

		i32 offset = (1 - next);
		if (_select.x - offset < 0) return;
		if (_select.x + _select.y + next > _text.length()) return;

		std::wstringstream ss;
		ss << _text.substr(0, _select.x - offset);
		ss << _text.substr(_select.x + _select.y + next);
		setText(ss.str());
		setSelect({ _select.x - offset, 0 });
	}
	void textInput::insert(const wchar_t* text) {
		validationData e(_select, text);
		_on_validate.notify(*this, e);
		if (e.isCanceled())
			return;

		deleteSelection();
		std::wstringstream ss;
		ss << _text.substr(0, _select.x);
		ss << text;
		ss << _text.substr(_select.x + _select.y);
		setText(ss.str());
		setSelect({ _select.x + (i32)wcslen(text), 0});
	}

	void textInput::onPaintTextInput(control& sender, paintData& e) {
		textInput& ti = static_cast<textInput&>(sender);

		if (ti._theme == nullptr)
			return;

		vector2<f32> size		= sender.getClientSize();
		paint& gfx				= e.getPaint();
		theme::select select	= theme::parse(ti.isEnabled(), ti.isCursorOver(), false, ti.isFocused());

		std::shared_ptr<const paint::brush> bg = ti._theme->getBackground(select);
		std::shared_ptr<const paint::brush> fg = ti._theme->getForeground(select);
		std::shared_ptr<const paint::brush> ol = ti._theme->getOutline(select);

		// Background
		if (bg != nullptr)
			gfx.fillRect({ {}, size }, *bg);
		
		// Outline
		if (ol != nullptr) {
			paint::pen pen(*ol, 1.0f);
			gfx.drawRect({ 0.0f, 0.0f, size.x - 1.0f, size.y - 1.0f }, pen);
		}
		
		bounds2<f32> tx_bounds = { 6.0f, 6.0f, size.x - 7.0f, size.y - 7.0f };

		// Text or hint
		if (fg != nullptr) {
			// TEXT
			if (ti._text.length() != 0) {
				i32 sel_begin = ti._select.x;
				i32 sel_end = ti._select.x + ti._select.y;
				i32 sel_len = ti._select.y;

				bool pre = sel_begin != 0;
				bool sel = sel_len != 0;
				bool post = sel_end != (ti._text.length());

				if (ti._text_font != nullptr) {
					std::wstring measure = ti._text;
					u64 i = 0;
					while ((i = measure.find(L' ')) != std::wstring::npos)
						measure.replace(i, 1, L"_");
					bounds2<f32> bounds = tx_bounds;
					bounds2<f32> used = { };
					
					bounds2<f32> pre_bounds		= {};
					bounds2<f32> select_bounds	= {};
					bounds2<f32> post_bounds	= {};
					bounds2<f32> letter = gfx.measureWrite(
						L"A", 1, bounds, *ti._text_font, ti._horizontal, ti._vertical);

					if (pre) {
					pre_bounds =
						gfx.measureWrite(
							measure.c_str(),
							sel_begin,
							bounds,
							*ti._text_font,
							ti._horizontal,
							ti._vertical);
					}

					if (sel) {
					select_bounds =
						gfx.measureWrite(
							measure.c_str() + sel_begin,
							sel_len,
							bounds,
							*ti._text_font,
							ti._horizontal,
							ti._vertical);
						if (pre) {
							select_bounds.from.x	= pre_bounds.to.x + select_bounds.from.x - 6.0f;
							select_bounds.to.x		= pre_bounds.to.x + select_bounds.to.x - 6.0f;
						}
					}
					else if (pre) {
						select_bounds.from.x = pre_bounds.to.x - 0.5f;
						select_bounds.to.x	 = pre_bounds.to.x + 0.5f;
					}
					else {
						select_bounds.from.x	= 5.5f;
						select_bounds.to.x		= 6.5f;
					}
					
					if (post) {
						post_bounds =
							gfx.measureWrite(
								measure.c_str() + sel_end,
								measure.length() - sel_end,
								bounds,
								*ti._text_font,
								ti._horizontal,
								ti._vertical);
						if (sel) {
							post_bounds.from.x	= select_bounds.to.x + post_bounds.from.x - 6.0f;
							post_bounds.to.x	= select_bounds.to.x + post_bounds.to.x - 6.0f;
						}
						else if (pre) {
							post_bounds.from.x	= pre_bounds.to.x + post_bounds.from.x - 6.0f;
							post_bounds.to.x	= pre_bounds.to.x + post_bounds.to.x - 6.0f;
						}
					}
					if (select_bounds.size().x == 0) {
						select_bounds.from.x	-= 1;
						select_bounds.to.x		+= 1;
					}
					if (select_bounds.size().y == 0) {
						select_bounds.from.y = letter.from.y;
						select_bounds.to.y = letter.to.y;
					}

					// PRE SELECT WRITE
					if(pre)
						gfx.write(
							ti._text.c_str(),
							sel_begin,
							pre_bounds,
							*ti._text_font,
							*fg,
							ti._horizontal,
							ti._vertical);

					// SELECT
					bounds2<f32> fill = select_bounds;
					gfx.fillRect(select_bounds, *fg);
					gfx.write(
						ti._text.c_str() + sel_begin,
						sel_len,
						select_bounds,
						*ti._text_font,
						*bg,
						ti._horizontal,
						ti._vertical);

					// POST SELECT WRITE
					if(post)
						gfx.write(
							ti._text.c_str() + sel_end,
							ti._text.length() - sel_end,
							post_bounds,
							*ti._text_font,
							*fg,
							ti._horizontal,
							ti._vertical);
				}
			}

			// HINT
			else {
				if (ti._hint_font != nullptr)
					gfx.write(
						ti._hint.c_str(),
						ti._hint.length(),
						tx_bounds,
						*ti._hint_font, 
						*fg, 
						ti._horizontal, 
						ti._vertical);
			}
		}
	}
	void textInput::onMouseDownTextInput(control& sender, mouseDownData& e) {
		// Return if not LMB
		if (e.getButton() != key::leftMouseButton)
			return;

		textInput& ti		= static_cast<textInput&>(sender);
		vector2<f32> size	= sender.getClientSize();

		// Calculate mouse press point
		i32 ix =
			paint(sender).pointToCaretIndex(
			ti._text.c_str(),
			ti._text.length(),
			{ 4.0f, 4.0f, size.x - 5.0f, size.y - 5.0f },
			*ti._text_font,
			ti._horizontal,
			ti._vertical,
			e.getCursorPos());

		ti.setSelect(vector2<i32>(ix, 0));
	}
	void textInput::onMouseUpTextInput(control& sender, mouseUpData& e) {
		// Return if not LMB
		if (e.getButton() != key::leftMouseButton)
			return;

		textInput& ti = static_cast<textInput&>(sender);
		vector2<f32> size = sender.getClientSize();

		// Calculate mouse release point
		i32 ix =
			paint(sender).pointToCaretIndex(
				ti._text.c_str(),
				ti._text.length(),
				{ 4.0f, 4.0f, size.x - 5.0f, size.y - 5.0f },
				*ti._text_font,
				ti._horizontal,
				ti._vertical,
				e.getCursorPos());

		if (ti._select.x < ix) { 
			ti.setSelect(vector2<i32>(ti._select.x, ix - ti._select.x + 1));
		}
		else if (ti._select.x > ix) {
			ti.setSelect(vector2<i32>(ix, ti._select.x - ix + 1));
		}
	}
	void textInput::onKeyDownTextInput(control& sender, keyDownData& e) {
		textInput& ti = static_cast<textInput&>(sender);

		// DELETE
		if (e.getKey() == key::backspace || e.getKey() == key::del) {
			u64 first	= ti._select.x;
			u64 last	= ti._select.x + ti._select.y;
			u64 length	= ti._select.y;

			// DELETE RANGE
			if(ti._select.y > 0)
				ti.deleteSelection();
			else
				ti.deleteSingle(e.getKey() == key::del);
		}

		// ARROW KEYS
		if (e.getKey() == key::arrowLeft)
			ti.setSelect({ ti._select.x - 1, 0 });
		if (e.getKey() == key::arrowRight)
			ti.setSelect({ ti._select.x + ti._select.y + 1, 0 });
	}
	void textInput::onCharTextInput(control& sender, characterData& e) {
		wchar_t ch = e.getChar();
		if (!(iswalnum(ch) || iswpunct(ch) || ch == L' '))
			return;

		textInput& ti = static_cast<textInput&>(sender);
		wchar_t ins[2] = { ch, L'\0'};
		ti.insert(ins);
	}
	void textInput::onLoseFocusTextInput(gui::control& sender, gui::control::loseFocusData& e) {
		static_cast<textInput&>(sender).setSelect({});
	}

}