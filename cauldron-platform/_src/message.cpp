#if defined(_WIN32) || defined(_WIN64)
#include "../message.h"
#include "cauldron-common/primitives.h"
#include <windows.h>

namespace cauldron::platform {
	static constexpr u64 message_user_request = 0xBFFF;

	message::message() :
		_core((core_t*)new MSG()) {}
	message::~message() {
		if (_core != nullptr) {
			delete (MSG*)_core;
			_core = nullptr;
		}
	}

	bool message::isInitialized() const {
		return _core != nullptr;
	}
	bool message::awaitPull() {
		BOOL result = ::GetMessageW((LPMSG)_core, nullptr, 0, 0);
		return result < -1 || result > 0;
	}
	bool message::immedaitePull() {
		return ::PeekMessageW((LPMSG)_core, nullptr, 0, 0, PM_REMOVE) != 0;
	}
	void message::dispatch() {
		if (((LPMSG)_core)->message == message_user_request) {
			auto proc = (void(*)(void*))((LPMSG)_core)->wParam;
			auto arg = (void*)((LPMSG)_core)->lParam;
			proc(arg);
		}
		::TranslateMessage((LPMSG)_core);
		::DispatchMessageW((LPMSG)_core);
	}

	void message::generateMessageQueue() {
		MSG msg = {};
		::PeekMessageW(&msg, nullptr, 0, 0, PM_NOREMOVE);
	}
	bool message::postLPV(thread::id* target, void(*procedure)(void*), void* argument) {
		return ::PostThreadMessageW(
			(DWORD)target,
			message_user_request,
			(WPARAM)procedure,
			(LPARAM)argument) != 0;
	}

}
#endif
