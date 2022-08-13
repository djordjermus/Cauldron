#if defined(_WIN32) || defined(_WIN64)
#include "../control.h"
#include "../paint.h"
#include <iostream>
#include <windows.h>

namespace cauldron::gui {
	using namespace cauldron::common;



	//
	// STATE

	using state = control::state;
	
	state::state(core_t* core) :
		_core(core) {}

	const state state::hidden(
		(core_t*)SW_HIDE);
	const state state::normal(
		(core_t*)SW_SHOWNORMAL);
	const state state::minimized(
		(core_t*)SW_SHOWMINIMIZED);
	const state state::maximized(
		(core_t*)SW_SHOWMAXIMIZED);



	//
	// STYLE

	using style = control::style;

	style::style(option options) :
		_core(optionsToCore(options)) {}
	style::style(core_t* core) :
		_core(core) {}
	style::option style::getOptions() const {
		return coreToOptions(_core);
	}

	style::option style::coreToOptions(core_t* core) {
		style::option acc = option::none;
		u64 val = (u64)core;

		// BOREDERED
		if ((val & WS_BORDER) == WS_BORDER) {
			acc = acc | option::bordered;

			// RESIZABLE
			if ((val & WS_SIZEBOX) == WS_SIZEBOX)
				acc = acc | option::resizable;

			// CAPTIONED
			if ((val & WS_CAPTION) == WS_CAPTION) {
				acc = acc | option::captioned;

				// MINIMIZE BUTTON
				if ((val & WS_MINIMIZEBOX) == WS_MINIMIZEBOX)
					acc = acc | option::minimize_button;

				// MAXIMIZE BUTTON
				if ((val & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX)
					acc = acc | option::maximize_button;
			}
		}

		// CHILD
		else if ((val & WS_CHILD) == WS_CHILD) {
			acc = acc | option::child;
		}

		// POPUP / RESIZABLE
		else if ((val & WS_SIZEBOX) == WS_SIZEBOX) {
			acc = acc | option::resizable;
		}

		return acc;
	}
	style::core_t* style::optionsToCore(option options) {
		u64 acc = 0;

		// BORDERED
		if ((options & option::bordered) == option::bordered) {
			acc |= WS_BORDER;

			// RESIZABLE
			if ((options & option::resizable) == option::resizable)
				acc |= WS_SIZEBOX;

			// CAPTIONED
			if ((options & option::captioned) == option::captioned) {
				acc |= WS_CAPTION;

				// MINIMIZE BUTTON
				if ((options & option::minimize_button) == option::minimize_button)
					acc |= WS_SYSMENU | WS_MINIMIZEBOX;

				// MAXIMIZE BUTTON
				if ((options & option::maximize_button) == option::maximize_button)
					acc |= WS_SYSMENU | WS_MAXIMIZEBOX;
			}
		}

		// CHILD WINDOW
		else if ((options & option::child) == option::child) {
			acc |= WS_CHILD;
		}

		// POPUP WINDOW
		else {
			acc |= WS_POPUP;

			// RESIZABLE
			if ((options & option::resizable) == option::resizable)
				acc |= WS_SIZEBOX;
		}
		return (core_t*)acc;
	}



	//
	// FOCUS STYLE

	using focusStyle = control::focusStyle;

	const focusStyle focusStyle::invalid(
		(core_t*)0x00);
	const focusStyle focusStyle::focusable(
		(core_t*)0x01);
	const focusStyle focusStyle::unfocusable(
		(core_t*)0x02);
	const focusStyle focusStyle::defer_to_child(
		(core_t*)0x03);

	focusStyle::focusStyle() : _core() {}
	focusStyle::focusStyle(core_t* core) :
		_core(core) {}



	//
	// CONTROL

	class ctrlint {
	public:
		static control::vector_t coordsFromParam(u64);
		static i32 scrollFromParams(u64);
		static control::sizingData::edge edgeFromParam(HWND, UINT, WPARAM, LPARAM);
		static key keyFromMsg(HWND, UINT, WPARAM, LPARAM);

		static control* get(HWND);
		static ATOM getAtom();
		static HWND makeHwnd();
		static LRESULT controlProcedure(HWND, UINT, WPARAM, LPARAM);

		static LRESULT wmCreate(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmClose(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmDestroy(HWND, UINT, WPARAM, LPARAM);

		static LRESULT wmActivate(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmGainFocus(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmLoseFocus(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmEnabled(HWND, UINT, WPARAM, LPARAM);

		static LRESULT wmMove(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmMoving(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmSize(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmSizing(HWND, UINT, WPARAM, LPARAM);

		static LRESULT wmKeyDown(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmKeyUp(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmChar(HWND, UINT, WPARAM, LPARAM);

		static LRESULT wmCursorMove(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmCursorLeave(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmScroll(HWND, UINT, WPARAM, LPARAM);

		static LRESULT wmMouseDown(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmMouseUp(HWND, UINT, WPARAM, LPARAM);
		static LRESULT wmDoubleClick(HWND, UINT, WPARAM, LPARAM);

		static LRESULT wmPaint(HWND, UINT, WPARAM, LPARAM);
	};

	control::control() :
		_core((core_t*)ctrlint::makeHwnd()), _backbuffer(1, 1) {
		::SetWindowLongPtrW(
			(HWND)_core,
			GWLP_USERDATA,
			(LONG_PTR)this);

	}
	control::~control() {
		if (isValid())
			terminate();
	}



	// OPERATORS

	void control::terminate() {
		if(::IsWindow((HWND)_core))
			::DestroyWindow((HWND)_core);
	}
	void control::refresh() {
		::InvalidateRect((HWND)_core, nullptr, FALSE);
	}



	// GETTERS

	bool control::isValid() const {
		return ::IsWindow((HWND)_core);
	}

	control* control::getParent() const {
		return _parent;
	}
	i32 control::getChildCount() const {
		return _children.size();
	}
	control* control::getChild(u32 index) const {
		if (index < _children.size())
			return _children[index];
		else
			return nullptr;
	}

	control::bounds_t control::getBounds() const {
		RECT rect = {};
		::GetWindowRect(
			(HWND)_core,
			&rect);

		POINT pts[] = {
			{rect.left, rect.top},
			{rect.right, rect.bottom}
		};
		if (_parent != nullptr) {
			::MapWindowPoints(
				nullptr,
				(HWND)_parent->_core,
				pts,
				sizeof(pts) / sizeof(pts[0]));
		}

		return bounds_t(
			pts[0].x,
			pts[0].y,
			pts[1].x,
			pts[1].y);
	}
	control::vector_t control::getClientSize() const {
		RECT rect = {};
		::GetClientRect(
			(HWND)_core,
			&rect);
		return vector_t(
			rect.right - rect.left,
			rect.bottom - rect.top);
	}
	std::wstring control::getCaption() const {
		constexpr u64 max_ch = 256;
		wch read[max_ch];
		::GetWindowTextW((HWND)_core, read, max_ch);
		return read;
	}
	state control::getState() const {
		WINDOWPLACEMENT wp = {};
		::GetWindowPlacement((HWND)_core, &wp);
		return state((state::core_t*)wp.showCmd);
	}
	style control::getStyle() const {
		return style((style::option)
			::GetWindowLongW((HWND)_core, GWL_STYLE));
	}
	focusStyle control::getFocusStyle() const {
		return _focus_style;
	}
	bool control::isActive() const {
		return ::GetActiveWindow() == (HWND)_core;
	}
	bool control::isFocused() const {
		return ::GetFocus() == (HWND)_core;
	}
	f32 control::getOpacity() const {
		COLORREF	color_ref	= 0;
		BYTE		opacity		= 0;
		DWORD		flag		= 0;
		if (::GetLayeredWindowAttributes((HWND)_core, &color_ref, &opacity, &flag) != FALSE)
			return opacity / 255.0f;
		else
			return 1.0f;
	}
	bool control::isEnabled() const {
		return _enabled;
	}
	bool control::isCursorOver() const {
		return _cursor_inside;
	}
	bool control::isDoubleBuffered() const {
		return _double_buffered;
	}


	
	// SETTERS

	void control::setBounds(const bounds_t& new_bounds) {
		::SetWindowPos(
			(HWND)_core,
			nullptr,
			new_bounds.from.x, 
			new_bounds.from.y,
			new_bounds.to.x - new_bounds.from.x,
			new_bounds.to.y - new_bounds.from.y,
			SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOZORDER);
		auto sz = new_bounds.size();

		// Update state 
		if (_state == state::hidden && sz.x != 0 && sz.y != 0)
			setState(state::normal);
	}
	void control::setCaption(const std::wstring& new_caption) {
		::SetWindowTextW(
			(HWND)_core,
			new_caption.c_str());
	}
	void control::adopt(control* adopt) {
		// Test adopted control
		if (adopt == nullptr || !adopt->isValid() || adopt->_parent == this)
			return;

		control* child		= adopt;
		control* old_parent	= adopt->_parent;

		// SET REFERENCE TO NEW PARENT
		child->_parent = this;
		this->_children.emplace_back(child);


		::SetParent((HWND)child->_core, (HWND)this->_core);
		// APPEND TO NEW PARENT CHILD VECTOR
		::SetWindowLongW((HWND)child->_core, GWL_EXSTYLE, 0); // CLEAR "WS_EX_LAYERED"
		child->setStyle(child->getStyle().getOptions() | style::option::child);

		// REMOVE FROM OLD PARENT CHILD VECTOR
		if (old_parent != nullptr) {
			for(
				auto it = old_parent->_children.begin(),
				jt = old_parent->_children.end();
				it != jt;
				it++) {
					
				if (*it == child) {
					old_parent->_children.erase(it);
					break;
				}
			}
		}

		// NOTIFY CHANGE PARENT
		changeParentData cpd(child, old_parent, this);
		child->_on_change_parent.notify(*child, cpd);

		// NOTIFY DISOWN
		if (old_parent != nullptr && old_parent->isValid()) {
			disownData dd(child, old_parent, this);
			old_parent->_on_disown.notify(*old_parent, dd);
		}

		// NOTIFY ADOPT
		adoptData ad(child, old_parent, this);
		this->_on_adopt.notify(*this, ad);
		
		// REPAINT
		if (child != nullptr)
			child->refresh();
	}
	void control::disown(control* disown) {
	}

	void control::setState(state new_state) {
		WINDOWPLACEMENT wp = {};
		::GetWindowPlacement((HWND)_core, &wp);
		::ShowWindowAsync((HWND)_core, (int)new_state.getCore());
	}
	void control::setStyle(style new_style) {
		static UINT swp_flags = 
			SWP_ASYNCWINDOWPOS | 
			SWP_FRAMECHANGED | 
			SWP_NOACTIVATE |
			SWP_NOREPOSITION | 
			SWP_NOZORDER |
			SWP_NOMOVE | 
			SWP_NOSIZE;

		::SetWindowLongW(
			(HWND)_core,
			GWL_STYLE,
			(LONG)new_style.getCore());

		::SetWindowPos(
			(HWND)_core,
			nullptr, 
			0, 0, 0, 0,
			swp_flags);
	}
	void control::setFocusStyle(focusStyle new_focus_style) {
		_focus_style = new_focus_style;
	}
	void control::setActive(bool active) {
		if (active)
			::SetActiveWindow((HWND)_core);
		else if (::GetActiveWindow() == (HWND)_core)
			::SetActiveWindow((HWND)_core);
	}
	void control::setFocus(bool focus) {
		if (focus)
			::SetFocus((HWND)_core);
		else if (::GetFocus() == (HWND)_core)
			::SetFocus(nullptr);
	}
	void control::setOpacity(f32 opacity) {
		::SetLayeredWindowAttributes(
			(HWND)_core,
			0,
			opacity * 255.0f,
			LWA_ALPHA);

		refresh();
		
	}
	void control::setEnabled(bool enabled) {
		::EnableWindow((HWND)_core, enabled);
	}
	void control::setDoubleBuffered(bool double_buffered) {
		_double_buffered = double_buffered;
	}



	// EVENT DATA

	using changeParentData = control::changeParentData;
	changeParentData::changeParentData(control* child, control* old_parent, control* new_parent) :
		_child(child), _old_parent(old_parent), _new_parent(new_parent) {}

	control* changeParentData::getChild() const {
		return _child;
	}
	control* changeParentData::getOldParent() const {
		return _old_parent;
	}
	control* changeParentData::getNewParent() const {
		return _new_parent;
	}

	using adoptData = control::adoptData;
	adoptData::adoptData(control* child, control* old_parent, control* new_parent) :
		changeParentData(child, old_parent, new_parent) {}

	using disownData = control::disownData;
	disownData::disownData(control* child, control* old_parent, control* new_parent) :
		changeParentData(child, old_parent, new_parent) {}

	using moveData = control::moveData;
	moveData::moveData(const vector_t& top_left) :
		_top_left(top_left) {}
	control::vector_t moveData::getTopLeft() const {
		return _top_left;
	}
	using movingData = control::movingData;
	movingData::movingData(bounds_t& ref_bounds) :
		_bounds(ref_bounds) {}
	control::bounds_t movingData::getBounds() const {
		return _bounds;
	}
	void movingData::setBounds(const bounds_t& final_bounds) {
		_bounds = final_bounds;
	}

	using sizeData = control::sizeData;
	sizeData::sizeData(const vector_t& client_size) :
		_client_size(client_size) {}
	control::vector_t sizeData::getClientSize() const {
		return _client_size;
	}
	using sizingData = control::sizingData;
	sizingData::sizingData(bounds_t& ref_bounds, edge sized_edge) :
		_bounds(ref_bounds), _sized_edge(sized_edge) {}
	control::bounds_t sizingData::getBounds() const {
		return _bounds;
	}
	sizingData::edge sizingData::getSizedEdges() const {
		return _sized_edge;
	}
	void sizingData::setBounds(const bounds_t& final_bounds) {
		_bounds = final_bounds;
	}

	using keyData = control::keyData;
	keyData::keyData(key key) : _key(key) {}

	key keyData::getKey() {
		return _key;
	}
	using keyDownData = control::keyDownData;
	keyDownData::keyDownData(key key) :
		keyData(key) {}

	using keyUpData = control::keyUpData;
	keyUpData::keyUpData(key key) :
		keyData(key) {}

	using characterData = control::characterData;
	characterData::characterData(wch character) :
		_character(character) {}
	wch characterData::getChar() const {
		return _character;
	}

	using cursorData = control::cursorData;
	cursorData::cursorData(const vector_t& cursor_position) :
		_cursor_position(cursor_position) {}

	control::vector_t cursorData::getCursorPos() const {
		return _cursor_position;
	}
	using cursorEnterData = control::cursorEnterData;
	cursorEnterData::cursorEnterData(const vector_t& cursor_position) :
		cursorData(cursor_position) {}
	using cursorMoveData = control::cursorMoveData;
	cursorMoveData::cursorMoveData(const vector_t& cursor_position) :
		cursorData(cursor_position) {}
	using cursorLeaveData = control::cursorLeaveData;
	cursorLeaveData::cursorLeaveData(const vector_t& cursor_position) :
		cursorData(cursor_position) {}

	using scrollData = control::scrollData;
	scrollData::scrollData(const vector_t& cursor_position, i32 scroll_distance) :
		cursorData(cursor_position), _scroll_distance(scroll_distance) {}
	i32 scrollData::getScrollDistance() const {
		return _scroll_distance;
	}

	using mouseData = control::mouseData;
	mouseData::mouseData(const vector_t& cursor_position, key button) :
		cursorData(cursor_position), _button(button) {}
	key mouseData::getButton() {
		return _button;
	}
	using mouseDownData = control::mouseDownData;
	mouseDownData::mouseDownData(const vector_t& cursor_position, key button) :
		mouseData(cursor_position, button) {}
	using mouseUpData = control::mouseUpData;
	mouseUpData::mouseUpData(const vector_t& cursor_position, key button) :
		mouseData(cursor_position, button) {}
	using doubleClickData = control::doubleClickData;
	doubleClickData::doubleClickData(const vector_t& cursor_position, key button) :
		mouseData(cursor_position, button) {}

	using paintData = control::paintData;
	paintData::paintData(paint& paint) :
		_paint(paint) {}

	paint& paintData::getPaint() const {
		return _paint;
	}



	// EVENT HANDLERS

	observable<void, control&, control::closeData&>& control::onClose() {
		return _on_close;
	}
	observable<void, control&, control::terminateData&>& control::onTerminate() {
		return _on_terminate;
	}

	observable<void, control&, control::activateData&>& control::onActivate() {
		return _on_activate;
	}
	observable<void, control&, control::deactivateData&>& control::onDeactivate() {
		return _on_deactivate;
	}
	observable<void, control&, control::gainFocusData&>& control::onGainFocus() {
		return _on_gainFocus;
	}
	observable<void, control&, control::loseFocusData&>& control::onLoseFocus() {
		return _on_loseFocus;
	}
	common::observable<void, control&, control::enabledData&>& control::onEnabled() {
		return _on_enabled;
	}
	common::observable<void, control&, control::disabledData&>& control::onDisabled() {
		return _on_disabled;
	}

	observable<void, control&, control::changeParentData&>& control::onChangeParent() {
		return _on_change_parent;
	}
	observable<void, control&, control::adoptData&>& control::onAdopt() {
		return _on_adopt;
	}
	observable<void, control&, control::disownData&>& control::onDisown() {
		return _on_disown;
	}

	observable<void, control&, control::moveData&>& control::onMove() {
		return _on_move;
	}
	observable<void, control&, control::movingData&>& control::onMoving() {
		return _on_moving;
	}
	observable<void, control&, control::sizeData&>& control::onSize() {
		return _on_size;
	}
	observable<void, control&, control::sizingData&>& control::onSizing() {
		return _on_sizing;
	}

	observable<void, control&, control::keyDownData&>& control::onKeyDown() {
		return _on_key_down;
	}
	observable<void, control&, control::keyUpData&>& control::onKeyUp() {
		return _on_key_up;
	}
	observable<void, control&, control::characterData&>& control::onCharacter() {
		return _on_character;
	}

	observable<void, control&, control::cursorEnterData&>& control::onCursorEnter() {
		return _on_cursor_enter;
	}
	observable<void, control&, control::cursorMoveData&>& control::onCursorMove() {
		return _on_cursor_move;
	}
	observable<void, control&, control::cursorLeaveData&>& control::onCursorLeave() {
		return _on_cursor_leave;
	}

	observable<void, control&, control::scrollData&>& control::onScroll() {
		return _on_scroll;
	}

	observable<void, control&, control::mouseDownData&>& control::onMouseDown() {
		return _on_mouse_down;
	}
	observable<void, control&, control::mouseUpData&>& control::onMouseUp() {
		return _on_mouse_up;
	}
	observable<void, control&, control::doubleClickData&>& control::onDoubleClick() {
		return _on_double_click;
	}
	observable<void, control&, paintData&>& control::onPaint() {
		return _on_paint;
	}
	
	void control::terminateOnClose(control& sender, control::closeData& e) {
		sender.terminate();
	}
	control::bounds_t control::adjustBoundsForStyle(const bounds_t& original, style style) {
		RECT rect = { original.from.x, original.from.y, original.to.x , original.to.y };
		::AdjustWindowRectEx(
			&rect,
			(DWORD)style.getCore(),
			FALSE,
			0);
		return bounds_t(rect.left, rect.top, rect.right, rect.bottom);
	}
	void control::debugHandler(control& sender, paintData& e) {
		static paint::solidBrush debug_brush(0xFF00FFFF);
		static paint::pen debug_pen(debug_brush, 2.0f);
		e.getPaint().drawRect({ {}, sender.getClientSize() }, debug_pen);
	}
	void control::adjustBackbufferSize() {
		vector_t size = getClientSize();
		if (size.x != _backbuffer.getWidth() || size.y != _backbuffer.getHeight())
			_backbuffer.swap(paint::bitmap(size.x, size.y));
	}


	// CTRLINT

	control::vector_t ctrlint::coordsFromParam(u64 param) {
		return control::vector_t(
			((param >>  0) & 0xFFFF),
			((param >> 16) & 0xFFFF));
	}
	i32 ctrlint::scrollFromParams(u64 param) {
		return ((i16)(u16)(param >> 16)) / 120;
	}
	control::sizingData::edge ctrlint::edgeFromParam(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		switch (w) {
		case WMSZ_LEFT:
			return sizingData::edge::left;
		case WMSZ_RIGHT:
			return sizingData::edge::right;

		case WMSZ_BOTTOM:
			return sizingData::edge::bottom;
		case WMSZ_BOTTOMLEFT:
			return sizingData::edge::bottom | sizingData::edge::left;
		case WMSZ_BOTTOMRIGHT:
			return sizingData::edge::bottom | sizingData::edge::right;

		case WMSZ_TOP:
			return sizingData::edge::top;
		case WMSZ_TOPLEFT:
			return sizingData::edge::top | sizingData::edge::left;
		case WMSZ_TOPRIGHT:
			return sizingData::edge::top | sizingData::edge::right;
		}
		return sizingData::edge::none;
	}
	key ctrlint::keyFromMsg(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		switch (msg) {
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
			return key::leftMouseButton;

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
			return key::rightMouseButton;

		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
			return key::middleMouseButton;

		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_XBUTTONDBLCLK:
			return ((w >> 16) & 0xFFFF) == 0x0001 ?
				key::extraMouseButton1 : key::extraMouseButton2;
		}
		return key::nullkey;
	}

	control* ctrlint::get(HWND hwnd) {
		return
			(control*)
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA);
	}

	ATOM ctrlint::getAtom() {
		static ATOM ret = 0;

		// initialize ret
		if (ret == 0) {
			WNDCLASSEXW wc		= {};
			wc.cbSize			= sizeof(wc);
			wc.lpfnWndProc		= controlProcedure;
			wc.lpszClassName	= L"CLD_WND_CLS_99999";
			wc.cbWndExtra		= sizeof(control*);
			wc.hCursor			= ::LoadCursorW(nullptr, IDC_ARROW);
			wc.style			= CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

			ret = ::RegisterClassExW(&wc);
		}

		// Throw if failed to initialize ret
		if (ret == 0)
			throw;

		return ret;
	}
	HWND ctrlint::makeHwnd() {
		HWND ret = ::CreateWindowExW(
			WS_EX_LAYERED, (LPCWSTR)getAtom(), L"", 0u,
			0, 0, 0, 0, 
			nullptr, nullptr, nullptr, nullptr);
		::SetLayeredWindowAttributes(
			ret,
			0,
			255,
			LWA_ALPHA);
		
		return ret;
	}
	LRESULT ctrlint::controlProcedure(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		switch (msg) {
		case WM_MOUSEMOVE:
			return wmCursorMove(hwnd, msg, w, l);

		case WM_MOUSELEAVE:
			return wmCursorLeave(hwnd, msg, w, l);

		case WM_MOUSEWHEEL:
			return wmScroll(hwnd, msg, w, l);

		case WM_CHAR:
			return wmChar(hwnd, msg, w, l);
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			return wmKeyDown(hwnd, msg, w, l);
		case WM_SYSKEYUP:
		case WM_KEYUP:
			return wmKeyUp(hwnd, msg, w, l);

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
			return wmMouseDown(hwnd, msg, w, l);

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
			return wmMouseUp(hwnd, msg, w, l);

		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_XBUTTONDBLCLK:
			return wmDoubleClick(hwnd, msg, w, l);

		case WM_PAINT:
			return wmPaint(hwnd, msg, w, l);
		case WM_ACTIVATE:
			return wmActivate(hwnd, msg, w, l);
		case WM_KILLFOCUS:
			return wmLoseFocus(hwnd, msg, w, l);
		case WM_SETFOCUS:
			return wmGainFocus(hwnd, msg, w, l);

		case WM_SIZE:
			return wmSize(hwnd, msg, w, l);
		case WM_MOVE:
			return wmMove(hwnd, msg, w, l);
		case WM_SIZING:
			return wmSizing(hwnd, msg, w, l);
		case WM_MOVING:
			return wmMoving(hwnd, msg, w, l);

		case WM_CREATE:
			return wmCreate(hwnd, msg, w, l);
		case WM_CLOSE:
			return wmClose(hwnd, msg, w, l);
		case WM_DESTROY:
			return wmDestroy(hwnd, msg, w, l);
		case WM_ENABLE:
			return wmEnabled(hwnd, msg, w, l);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmCreate(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			(LONG_PTR)nullptr);

		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmClose(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender) {
			control::closeData e;
			sender->onClose().notify(*sender, e);
		}

		return 0;
	}
	LRESULT ctrlint::wmDestroy(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender) {
			control::terminateData e;
			sender->onTerminate().notify(*sender, e);
		}
		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			(LONG_PTR)nullptr);
		return DefWindowProcW(hwnd, msg, w, l);
	}

	LRESULT ctrlint::wmActivate(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender) {
			if (w != 0) {
				control::activateData e;
				sender->onActivate().notify(*sender, e);
			}
			else {
				control::deactivateData e;
				sender->onDeactivate().notify(*sender, e);
			}
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmGainFocus(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender == nullptr)
			return 0;

		focusStyle fs = sender->_focus_style;
		if (fs == focusStyle::focusable) {
			if (sender) {
				control::gainFocusData e;
				sender->onGainFocus().notify(*sender, e);
			}
		}
		else if (fs == focusStyle::unfocusable) {
			::SetFocus(nullptr);
		}
		else if (fs == focusStyle::defer_to_child) {
			::SetFocus(GetWindow(hwnd, GW_CHILD));
		}

		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmLoseFocus(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender!= nullptr && sender->_focus_style == focusStyle::focusable) {
			control::loseFocusData e;
			sender->onLoseFocus().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmEnabled(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			sender->_enabled = w == TRUE;

			if (w == TRUE) {
				control::enabledData e;
				sender->onEnabled().notify(*sender, e);
			}
			else {
				control::disabledData e;
				sender->onDisabled().notify(*sender, e);
			}
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}

	LRESULT ctrlint::wmMove(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::moveData e(coordsFromParam(l));
			sender->onMove().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmMoving(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			RECT* rect = (RECT*)l;
			control::bounds_t bounds = control::bounds_t(rect->left, rect->top, rect->right, rect->bottom);
			control::movingData e(bounds);
			sender->onMoving().notify(*sender, e);

			rect->left		= bounds.from.x;
			rect->top		= bounds.from.y;
			rect->right		= bounds.to.x;
			rect->bottom	= bounds.to.y;
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmSize(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::sizeData e(coordsFromParam(l));
			sender->onSize().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmSizing(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			RECT* rect = (RECT*)l;
			control::bounds_t bounds = control::bounds_t(rect->left, rect->top, rect->right, rect->bottom);
			control::sizingData e(bounds, edgeFromParam(hwnd, msg, w, l));
			sender->onSizing().notify(*sender, e);
			rect->left		= bounds.from.x;
			rect->top		= bounds.from.y;
			rect->right		= bounds.to.x;
			rect->bottom	= bounds.to.y;
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}

	LRESULT ctrlint::wmKeyDown(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::keyDownData e((key::core_t*)w);
			sender->onKeyDown().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmKeyUp(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::keyUpData e((key::core_t*)w);
			sender->onKeyUp().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmChar(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::characterData e(w);
			sender->onCharacter().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}

	LRESULT ctrlint::wmCursorMove(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			if (sender->_cursor_inside) {
				control::cursorMoveData e(coordsFromParam(l));
				sender->onCursorMove().notify(*sender, e);
			}
			else {
				TRACKMOUSEEVENT tme = {
					sizeof(tme),
					TME_LEAVE,
					hwnd,
					0u
				};
				::TrackMouseEvent(&tme);
				sender->_cursor_inside = true;
				control::cursorEnterData e(coordsFromParam(l));
				sender->onCursorEnter().notify(*sender, e);
			}
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmCursorLeave(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			sender->_cursor_inside = false;
			control::cursorLeaveData e(coordsFromParam(l));
			sender->onCursorLeave().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmScroll(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::scrollData e(coordsFromParam(l), scrollFromParams(w));
			sender->onScroll().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	
	LRESULT ctrlint::wmMouseDown(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		::SetFocus(hwnd);

		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::mouseDownData e(coordsFromParam(l), keyFromMsg(hwnd, msg, w, l));
			sender->onMouseDown().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmMouseUp(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::mouseUpData e(coordsFromParam(l), keyFromMsg(hwnd, msg, w, l));
			sender->onMouseUp().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	LRESULT ctrlint::wmDoubleClick(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {
			control::doubleClickData e(coordsFromParam(l), keyFromMsg(hwnd, msg, w, l));
			sender->onDoubleClick().notify(*sender, e);
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
	
	LRESULT ctrlint::wmPaint(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
		control* sender = get(hwnd);
		if (sender != nullptr) {

			// Handle double buffered paint
			if (sender->_double_buffered) {

				// Adjust backbuffer size
				sender->adjustBackbufferSize();

				// Notify paint
				paint gfx(sender->_backbuffer);
				control::paintData e(gfx);
				sender->onPaint().notify(*sender, e);
				
				// Blit backbuffer to control
				paint blit(*sender);
				blit.drawImage({ {}, sender->getClientSize() }, sender->_backbuffer);
			}

			// Handle direct paint
			else {
				paint gfx(*sender);
				control::paintData e(gfx);
				sender->onPaint().notify(*sender, e);
			}
		}
		return DefWindowProcW(hwnd, msg, w, l);
	}
}

#endif