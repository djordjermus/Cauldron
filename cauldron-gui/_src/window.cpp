
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include "../window.h"
#include "cauldron-common/math.h"
namespace cauldron::gui {
	static LONG convert(window::style style);
	static window::style convertToStyle(LONG val);
	window::window() {
		::SetWindowLongW((HWND)getCore(), GWL_EXSTYLE, WS_EX_LAYERED);
		::SetLayeredWindowAttributes(
			(HWND)getCore(),
			0,
			255,
			LWA_ALPHA);
	}

	f32 window::getOpacity() const {
		return _opacity;
	}

	//bool window::adopt(control* child) {
	//	::SetWindowLongW((HWND)child->getCore(), GWL_STYLE, WS_CHILD);
	//	::SetParent((HWND)child->getCore(), (HWND)getCore());
	//	control* old = child->_parent;
	//	child->_parent = this;
	//	control::changeParentData e(child, old, this);
	//	child->onChangeParent().notify(*child, e);
	//
	//	return true;
	//}
	bool window::setState(state state) {
		switch (state) {
		case state::hidden:
			return setVisible(false);
	
		case state::normal:
			return 
				setVisible(true);
	
		case state::minimized:
			return 
				setVisible(true) && 
				::ShowWindow((HWND)getCore(), SW_SHOWMINIMIZED) != FALSE;
	
		case state::maximized:
			setVisible(true);
			::ShowWindow((HWND)getCore(), SW_SHOWMAXIMIZED) != FALSE;
		}
		return false;
	}
	bool window::setStyle(style style) {
		return ::SetWindowLongW((HWND)getCore(), GWL_STYLE, convert(style)) != false;
		return true;
	}
	bool window::setOpacity(f32 opacity) {
		// Clamp value
		opacity = common::Math::clamp(opacity, 0.0f, 1.0f);

		// Set opacity
		bool ret = ::SetLayeredWindowAttributes(
			(HWND)getCore(),
			0,
			opacity * 255.0f,
			LWA_ALPHA) != FALSE;

		// Read opacity
		COLORREF	out_color_ref = 0;
		BYTE		out_opacity = 0;
		DWORD		out_flag = 0;

		if (::GetLayeredWindowAttributes((HWND)getCore(), &out_color_ref, &out_opacity, &out_flag) != FALSE)
			_opacity = out_opacity / 255.0f;
		else
			_opacity = 1.0f;

		refresh();

		return ret;
	}

	
	static LONG convert(window::style style) {
		u32 acc = 0;
	
		// BORDERED
		if ((style & window::style::bordered) == window::style::bordered) {
			acc |= WS_BORDER;
	
			// RESIZABLE
			if ((style & window::style::resizable) == window::style::resizable)
				acc |= WS_SIZEBOX;
	
			// CAPTIONED
			if ((style & window::style::captioned) == window::style::captioned) {
				acc |= WS_CAPTION;
	
				// MINIMIZE BUTTON
				if ((style & window::style::minimize_button) == window::style::minimize_button)
					acc |= WS_SYSMENU | WS_MINIMIZEBOX;
	
				// MAXIMIZE BUTTON
				if ((style & window::style::maximize_button) == window::style::maximize_button)
					acc |= WS_SYSMENU | WS_MAXIMIZEBOX;
			}
		}
	
		// POPUP WINDOW
		else {
			// RESIZABLE
			if ((style & window::style::resizable) == window::style::resizable)
				acc |= WS_SIZEBOX;
		}
		return acc;
	}
	static window::style convertToStyle(LONG val) {
		window::style acc = window::style::none;
		bool child = (val & WS_CHILD) == WS_CHILD;
		// BOREDERED
		if ((val & WS_BORDER) == WS_BORDER) {
			acc = acc | window::style::bordered;
	
			// RESIZABLE
			if ((val & WS_SIZEBOX) == WS_SIZEBOX)
				acc = acc | window::style::resizable;
	
			// CAPTIONED
			if ((val & WS_CAPTION) == WS_CAPTION) {
				acc = acc | window::style::captioned;
	
				// MINIMIZE BUTTON
				if ((val & WS_MINIMIZEBOX) == WS_MINIMIZEBOX)
					acc = acc | window::style::minimize_button;
	
				// MAXIMIZE BUTTON
				if ((val & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX)
					acc = acc | window::style::maximize_button;
			}
		}
	
		// RESIZABLE
		else if ((val & WS_SIZEBOX) == WS_SIZEBOX) {
			acc = acc | window::style::resizable;
		}
	
		return acc;
	}
}
#endif
