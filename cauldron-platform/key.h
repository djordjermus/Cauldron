#include "cauldron-common/primitives.h"
#include "cauldron-common/macro.coreManip.h"
#pragma once
namespace cauldron {

	class key {
	public:
		class core_t;

		static const key invalid;

		static const key nullkey;
		static const key leftMouseButton;
		static const key rightMouseButton;
		static const key middleMouseButton;
		static const key extraMouseButton1;
		static const key extraMouseButton2;
		static const key backspace;
		static const key tab;
		static const key clear;
		static const key enter;
		static const key shift;
		static const key control;
		static const key alt;
		static const key pause;
		static const key capslock;
		static const key escape;
		static const key space;
		static const key pageUp;
		static const key pageDown;
		static const key end;
		static const key home;

		static const key 
			an0, an1, an2, an3, an4, an5, an6, an7, an8, an9;
		static const key 
			a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;

		static const key 
			np0, np1, np2, np3, np4, np5, np6, np7, np8, np9;
		static const key 
			multiply, add, separator, subtract, decimal, divide;

		static const key 
			f1,  f2,  f3,  f4,  f5,  f6,  f7,  f8,  f9,  f10, f11, f12;
			static const key
			f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24;

		static const key numberlock;
		static const key scrollLock;
		static const key shiftLeft;
		static const key shiftRight;
		static const key controlLeft;
		static const key controlRight;
		static const key altLeft;
		static const key altRight;
		static const key semicolon;
		static const key plus;
		static const key comma;
		static const key minus;
		static const key period;
		static const key slash;
		static const key tilde;
		static const key sqOpenBracket;
		static const key backslash;
		static const key sqCloseBracket;
		static const key quote;

		key(core_t* core);
		key(const key& copy);
		key(const key&& copy) noexcept;

		~key() = default;

		key& operator=(const key& copy);
		key& operator=(const key&& copy) noexcept;


		INLINE_CORE_GET(core_t, _core);
		INLINE_CORE_CMP(key, core_t, _core);

		static const key& find(core_t* core);

	private:
		static const key* key_array[256]; 
		core_t* _core;
	};
}