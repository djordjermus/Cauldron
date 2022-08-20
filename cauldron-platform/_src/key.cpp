#if defined(_WIN32) || defined(_WIN64)
#include "../key.h"
#include <Windows.h>
namespace cauldron {
	const key key::invalid				((core_t*)0xFF);
	const key key::nullkey				((core_t*)0x00);
	const key key::leftMouseButton		((core_t*)0x01);
	const key key::rightMouseButton		((core_t*)0x02);
	const key key::middleMouseButton	((core_t*)0x03);
	const key key::extraMouseButton1	((core_t*)0x05);
	const key key::extraMouseButton2	((core_t*)0x06);
	const key key::backspace			((core_t*)0x08);
	const key key::tab					((core_t*)0x09);
	const key key::clear				((core_t*)0x0C);
	const key key::enter				((core_t*)0x0D);
	const key key::shift				((core_t*)0x10);
	const key key::control				((core_t*)0x11);
	const key key::alt					((core_t*)0x12);
	const key key::pause				((core_t*)0x13);
	const key key::capslock				((core_t*)0x14);
	const key key::escape				((core_t*)0x1B);
	const key key::space				((core_t*)0x20);
	const key key::pageUp				((core_t*)0x21);
	const key key::pageDown				((core_t*)0x22);
	const key key::end					((core_t*)0x23);
	const key key::home					((core_t*)0x24);
	const key key::arrowLeft			((core_t*)0x25);
	const key key::arrowUp				((core_t*)0x26);
	const key key::arrowRight			((core_t*)0x27);
	const key key::arrowDown			((core_t*)0x28);
	const key key::select				((core_t*)0x29);
	const key key::print				((core_t*)0x2A);
	const key key::execute				((core_t*)0x2B);
	const key key::printScreen			((core_t*)0x2C);
	const key key::insert				((core_t*)0x2D);
	const key key::del					((core_t*)0x2E);
	const key key::help					((core_t*)0x2F);

	const key 
		key::an0((core_t*)0x30), 
		key::an1((core_t*)0x31), 
		key::an2((core_t*)0x32), 
		key::an3((core_t*)0x33), 
		key::an4((core_t*)0x34), 
		key::an5((core_t*)0x35), 
		key::an6((core_t*)0x36), 
		key::an7((core_t*)0x37), 
		key::an8((core_t*)0x38), 
		key::an9((core_t*)0x39);
	const key 
		key::a((core_t*)0x41), 
		key::b((core_t*)0x42), 
		key::c((core_t*)0x43), 
		key::d((core_t*)0x44), 
		key::e((core_t*)0x45), 
		key::f((core_t*)0x46), 
		key::g((core_t*)0x47), 
		key::h((core_t*)0x48), 
		key::i((core_t*)0x49), 
		key::j((core_t*)0x4A), 
		key::k((core_t*)0x4B), 
		key::l((core_t*)0x4C), 
		key::m((core_t*)0x4D), 
		key::n((core_t*)0x4E), 
		key::o((core_t*)0x4F), 
		key::p((core_t*)0x50), 
		key::q((core_t*)0x51), 
		key::r((core_t*)0x52), 
		key::s((core_t*)0x53), 
		key::t((core_t*)0x54), 
		key::u((core_t*)0x55), 
		key::v((core_t*)0x56), 
		key::w((core_t*)0x57), 
		key::x((core_t*)0x58), 
		key::y((core_t*)0x59), 
		key::z((core_t*)0x5A);

	const key 
		key::np0((core_t*)0x60),
		key::np1((core_t*)0x61), 
		key::np2((core_t*)0x62), 
		key::np3((core_t*)0x63), 
		key::np4((core_t*)0x64), 
		key::np5((core_t*)0x65), 
		key::np6((core_t*)0x66), 
		key::np7((core_t*)0x67), 
		key::np8((core_t*)0x68), 
		key::np9((core_t*)0x69);
	const key 
		key::multiply	((core_t*)0x6A),
		key::add		((core_t*)0x6B),
		key::separator	((core_t*)0x6C),
		key::subtract	((core_t*)0x6D),
		key::decimal	((core_t*)0x6E),
		key::divide		((core_t*)0x6F);

	const key 
		key::f1 ((core_t*)0x70), 
		key::f2 ((core_t*)0x71), 
		key::f3 ((core_t*)0x72), 
		key::f4 ((core_t*)0x73), 
		key::f5 ((core_t*)0x74), 
		key::f6 ((core_t*)0x75), 
		key::f7 ((core_t*)0x76), 
		key::f8 ((core_t*)0x77), 
		key::f9 ((core_t*)0x78), 
		key::f10((core_t*)0x79), 
		key::f11((core_t*)0x7A), 
		key::f12((core_t*)0x7B),
		key::f13((core_t*)0x7C),
		key::f14((core_t*)0x7D),
		key::f15((core_t*)0x7E),
		key::f16((core_t*)0x7F), 
		key::f17((core_t*)0x80), 
		key::f18((core_t*)0x81), 
		key::f19((core_t*)0x82), 
		key::f20((core_t*)0x83), 
		key::f21((core_t*)0x84),
		key::f22((core_t*)0x85), 
		key::f23((core_t*)0x86), 
		key::f24((core_t*)0x87);

	const key key::numberlock		((core_t*)0x90);
	const key key::scrollLock		((core_t*)0x91);
	const key key::shiftLeft		((core_t*)0xA0);
	const key key::shiftRight		((core_t*)0xA1);
	const key key::controlLeft		((core_t*)0xA2);
	const key key::controlRight		((core_t*)0xA3);
	const key key::altLeft			((core_t*)0xA4);
	const key key::altRight			((core_t*)0xA5);
	const key key::semicolon		((core_t*)0xBA);
	const key key::plus				((core_t*)0xBB);
	const key key::comma			((core_t*)0xBC);
	const key key::minus			((core_t*)0xBD);
	const key key::period			((core_t*)0xBE);
	const key key::slash			((core_t*)0xBF);
	const key key::tilde			((core_t*)0xC0);
	const key key::sqOpenBracket	((core_t*)0xDB);
	const key key::backslash		((core_t*)0xDC);
	const key key::sqCloseBracket	((core_t*)0xDD);
	const key key::quote			((core_t*)0xDE);

	const key* key::key_array[256] = {
		&invalid,
		&nullkey,
		&leftMouseButton,
		&rightMouseButton,
		&middleMouseButton,
		&extraMouseButton1,
		&extraMouseButton2,
		&backspace,
		&tab,
		&clear,
		&enter,
		&shift,
		&control,
		&alt,
		&pause,
		&capslock,
		&escape,
		&space,
		&pageUp,
		&pageDown,
		&end,
		&home,
		&an0, &an1, &an2, &an3, &an4, &an5, &an6, &an7, &an8, &an9,
		&a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m,
		&n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z,
		&np0, &np1, &np2, &np3, &np4, &np5, &np6, &np7, &np8, &np9,
		&multiply, &add, &separator, &subtract, &decimal, &divide,

		&f1,  &f2,  &f3,  &f4,  &f5,  &f6,  &f7,  &f8,  &f9,  &f10, &f11, &f12,
		&f13, &f14, &f15, &f16, &f17, &f18, &f19, &f20, &f21, &f22, &f23, &f24,

		&numberlock,
		&scrollLock,
		&shiftLeft,
		&shiftRight,
		&controlLeft,
		&controlRight,
		&altLeft,
		&altRight,
		&semicolon,
		&plus,
		&comma,
		&minus,
		&period,
		&slash,
		&tilde,
		&sqOpenBracket,
		&backslash,
		&sqCloseBracket,
		&quote,
	};

	const key& key::find(core_t* core) {
		for (const key* el : key_array) 
			if (el != nullptr && el->_core == core) 
				return *el;
		
		return invalid;
	}

	key::key(core_t* core) : _core(core) {}
	key::key(const key& copy) : _core(copy._core) {}
	key::key(const key&& copy) noexcept : _core(copy._core) {}
	key& key::operator=(const key& copy) {
		_core = copy._core;
		return *this;
	}
	key& key::operator=(const key&& copy) noexcept {
		_core = copy._core;
		return *this;
	}
}
#endif
