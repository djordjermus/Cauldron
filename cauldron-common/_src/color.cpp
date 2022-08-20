#include "../color.h"
#include <cmath>

namespace cauldron::common {
#define GET_R(x) ((x >> 24) & 0xFF)
#define GET_G(x) ((x >> 16) & 0xFF)
#define GET_B(x) ((x >> 8) & 0xFF)
#define GET_A(x) ((x >> 0) & 0xFF)
#define MAX(x, y, z) (x > y ? (x > z ? x : z) : (y > z ? y : z))
#define MIN(x, y, z) (x < y ? (x < z ? x : z) : (y < z ? y : z))
#define MODULO(x, y) ((fmodf(fmodf(x, y) + y, y)))
#define DEG (60.0f / 360.0f)

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // C O N S T R U C T O R S - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	rgba8::rgba8() :
		r(), g(), b(), a() {}
	rgba8::rgba8(u32 code) :
		r(GET_R(code)),
		g(GET_G(code)),
		b(GET_B(code)),
		a(GET_A(code)) {}
	rgba8::rgba8(u8 red, u8 green, u8 blue, u8 alpha) :
		r(red),
		g(green),
		b(blue),
		a(alpha) {}

	rgb10a2::rgb10a2() :
		r(), g(), b(), a() {}
	rgb10a2::rgb10a2(u32 red, u32 green, u32 blue, u32 alpha) :
		r(red), g(green), b(blue), a(alpha) {}
	rgb10a2::rgb10a2(u32 code) :
		r(GET_R(code) * 4),
		g(GET_G(code) * 4),
		b(GET_B(code) * 4),
		a(GET_A(code) / 64) {}

	rgba32::rgba32() :
		r(), g(), b(), a() {}
	rgba32::rgba32(u32 code) :
		r(GET_R(code) / 255.0f),
		g(GET_G(code) / 255.0f),
		b(GET_B(code) / 255.0f),
		a(GET_A(code) / 255.0f) {}
	rgba32::rgba32(f32 red, f32 green, f32 blue, f32 alpha) :
		r(red),
		g(green),
		b(blue),
		a(alpha) {}

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // C A S T I N G - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	rgba8::operator rgb10a2() {
		return rgb10a2::fromRGBA(
			r / 255.0f,
			g / 255.0f,
			b / 255.0f,
			a / 255.0f);
	}
	rgba8::operator rgba32() {
		return rgba32::fromRGBA(
			r / 255.0f,
			g / 255.0f,
			b / 255.0f,
			a / 255.0f);
	}
	rgb10a2::operator rgba8() {
		return rgba8::fromRGBA(
			r / 1023.0f,
			g / 1023.0f,
			b / 1023.0f,
			a / 3.0f);
	}
	rgb10a2::operator rgba32() {
		return rgba32::fromRGBA(
			r / 1023.0f,
			g / 1023.0f,
			b / 1023.0f,
			a / 3.0f);
	}
	rgba32::operator rgba8() {
		return rgba8::fromRGBA(r, g, b, a);
	}
	rgba32::operator rgb10a2() {
		return rgb10a2::fromRGBA(r, g, b, a);
	}

	v4f32 rgba8::toRGBA() const {
		return v4f32(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}
	v4f32 rgba8::toHSVA() const {
		f32 r = this->r / 255.0f;
		f32 g = this->g / 255.0f;
		f32 b = this->b / 255.0f;
		f32 a = this->a / 255.0f;

		f32 max = MAX(r, g, b);
		f32 min = MIN(r, g, b);
		f32 del = max - min;

		f32 v = max;
		f32 s = max == 0 ? 0 : del / max;

		if (del == 0)
			return v4f32(0, s, v, a);
		if (max == r)
			return v4f32(DEG * MODULO((g - b) / del + 6, 6), s, v, a);
		if (max == g)
			return v4f32(DEG * ((b - r) / del + 2), s, v, a);
		if (max == b)
			return v4f32(DEG * ((r - g) / del + 4), s, v, a);

		return v4f32();
	}
	v4f32 rgba8::toHSLA() const {
		f32 r = this->r / 255.0f;
		f32 g = this->g / 255.0f;
		f32 b = this->b / 255.0f;
		f32 a = this->a / 255.0f;

		f32 max = MAX(r, g, b);
		f32 min = MIN(r, g, b);
		f32 del = max - min;

		f32 l = (max + min) * 0.5f;
		f32 s = del / (1 - std::fabsf(2 * l - 1));

		if (del == 0) return v4f32(0, s, l, a);
		if (max == r) return v4f32(MODULO((g - b) / del, 6), s, l, a);
		if (max == g) return v4f32((b - r) / del + 2, s, l, a);
		if (max == b) return v4f32((r - g) / del + 4, s, l, a);
		return v4f32();
	}
	v4f32 rgba8::toCMYK() const {
		f32 r = this->r / 255.0f;
		f32 g = this->g / 255.0f;
		f32 b = this->b / 255.0f;
		f32 max = MAX(r, g, b);
		f32 k = 1 - max;
		return v4f32((1 - r - k) / max, (1 - g - k) / max, (1 - b - k) / max, k);
	}

	v4f32 rgb10a2::toRGBA() const {
		return v4f32(r / 1023.0f, g / 1023.0f, b / 1023.0f, a / 3.0f);
	}
	v4f32 rgb10a2::toHSVA() const {
		f32 r = this->r / 1023.0f;
		f32 g = this->g / 1023.0f;
		f32 b = this->b / 1023.0f;
		f32 a = this->a / 3.0f;

		f32 max = MAX(r, g, b);
		f32 min = MIN(r, g, b);
		f32 del = max - min;

		f32 v = max;
		f32 s = max == 0 ? 0 : del / (1 - std::fabsf(2 * v - 1));

		if (del == 0) return v4f32(0, s, v, a);
		if (max == r) return v4f32(MODULO((g - b) / del, 6), s, v, a);
		if (max == g) return v4f32((b - r) / del + 2, s, v, a);
		if (max == b) return v4f32((r - g) / del + 4, s, v, a);
		return v4f32();
	}
	v4f32 rgb10a2::toHSLA() const {
		f32 r = this->r / 1023.0f;
		f32 g = this->g / 1023.0f;
		f32 b = this->b / 1023.0f;
		f32 a = this->a / 3.0f;

		f32 max = MAX(r, g, b);
		f32 min = MIN(r, g, b);
		f32 del = max - min;

		f32 l = (max + min) * 0.5f;
		f32 s = del / (1 - std::fabsf(2 * l - 1));

		if (del == 0) return v4f32(0, s, l, a);
		if (max == r) return v4f32(MODULO((g - b) / del, 6), s, l, a);
		if (max == g) return v4f32((b - r) / del + 2, s, l, a);
		if (max == b) return v4f32((r - g) / del + 4, s, l, a);
		return v4f32();
	}
	v4f32 rgb10a2::toCMYK() const {
		f32 r = this->r / 1023.0f;
		f32 g = this->g / 1023.0f;
		f32 b = this->b / 1023.0f;
		f32 max = MAX(r, g, b);
		f32 k = 1 - max;
		return v4f32((1 - r - k) / max, (1 - g - k) / max, (1 - b - k) / max, k);
	}

	v4f32 rgba32::toRGBA() const {
		return v4f32(r, g, b, a);
	}
	v4f32 rgba32::toHSVA() const {
		f32 max = MAX(r, g, b);
		f32 min = MIN(r, g, b);
		f32 del = max - min;

		f32 v = max;
		f32 s = max == 0 ? 0 : del / (1 - std::fabsf(2 * v - 1));

		if (del == 0) return v4f32(0, s, v, a);
		if (max == r) return v4f32(MODULO((g - b) / del, 6), s, v, a);
		if (max == g) return v4f32((b - r) / del + 2, s, v, a);
		if (max == b) return v4f32((r - g) / del + 4, s, v, a);
		return v4f32();
	}
	v4f32 rgba32::toHSLA() const {
		f32 max = MAX(r, g, b);
		f32 min = MIN(r, g, b);
		f32 del = max - min;

		f32 l = (max + min) * 0.5f;
		f32 s = del / (1 - std::fabsf(2 * l - 1));

		if (del == 0) return v4f32(0, s, l, a);
		if (max == r) return v4f32(MODULO((g - b) / del, 6), s, l, a);
		if (max == g) return v4f32((b - r) / del + 2, s, l, a);
		if (max == b) return v4f32((r - g) / del + 4, s, l, a);
		return v4f32();
	}
	v4f32 rgba32::toCMYK() const {
		f32 max = MAX(r, g, b);
		f32 k = 1 - max;
		return v4f32((1 - r - k) / max, (1 - g - k) / max, (1 - b - k) / max, k);
	}

	rgba8 rgba8::fromRGBA(f32 red, f32 green, f32 blue, f32 alpha) {
		return rgba8(
			static_cast<u8>(red * 255u),
			static_cast<u8>(green * 255u),
			static_cast<u8>(blue * 255u),
			static_cast<u8>(alpha * 255u));
	}
	rgba8 rgba8::fromHSVA(f32 h, f32 s, f32 v, f32 a) {

		f32 c = v * s;
		f32 x = c * (1 - std::fabsf(MODULO(h / DEG, 2) - 1));
		f32 m = v - c;
		if (h < 1 * DEG) return rgba32((c + m), (x + m), (0 + m), a);
		if (h < 2 * DEG) return rgba32((x + m), (c + m), (0 + m), a);
		if (h < 3 * DEG) return rgba32((0 + m), (c + m), (x + m), a);
		if (h < 4 * DEG) return rgba32((0 + m), (x + m), (c + m), a);
		if (h < 5 * DEG) return rgba32((x + m), (0 + m), (c + m), a);
		if (h < 6 * DEG) return rgba32((c + m), (0 + m), (x + m), a);
		return rgba32();
	}
	rgba8 rgba8::fromHSLA(f32 h, f32 s, f32 l, f32 a) {
		f32 c = (1 - std::fabsf(2 * l - 1)) * s;
		f32 x = c * (1 - std::fabsf(MODULO(h / DEG, 2) - 1));
		f32 m = l - c * 0.5f;
		if (h < 1 * DEG) return rgba32((c + m), (x + m), (0 + m), a);
		if (h < 2 * DEG) return rgba32((x + m), (c + m), (0 + m), a);
		if (h < 3 * DEG) return rgba32((0 + m), (c + m), (x + m), a);
		if (h < 4 * DEG) return rgba32((0 + m), (x + m), (c + m), a);
		if (h < 5 * DEG) return rgba32((x + m), (0 + m), (c + m), a);
		if (h < 6 * DEG) return rgba32((c + m), (0 + m), (x + m), a);
		return rgba32();
	}
	rgba8 rgba8::fromCMYK(f32 c, f32 m, f32 y, f32 k) {
		f32 max = 1 - k;
		return rgb10a2(
			static_cast<u32>((1 - c) * max * 255u),
			static_cast<u32>((1 - m) * max * 255u),
			static_cast<u32>((1 - y) * max * 255u),
			static_cast<u32>(3u));
	}

	rgb10a2 rgb10a2::fromRGBA(f32 red, f32 green, f32 blue, f32 alpha) {
		return rgb10a2(
			static_cast<u32>(red * 1023u),
			static_cast<u32>(green * 1023u),
			static_cast<u32>(blue * 1023u),
			static_cast<u32>(alpha * 3u));
	}
	rgb10a2 rgb10a2::fromHSVA(f32 h, f32 s, f32 v, f32 a) {
		f32 c = v * s;
		f32 x = c * (1 - std::fabsf(MODULO(h / DEG, 2) - 1));
		f32 m = v - c;
		if (h < 1 * DEG) return rgba32((c + m), (x + m), (0 + m), a);
		if (h < 2 * DEG) return rgba32((x + m), (c + m), (0 + m), a);
		if (h < 3 * DEG) return rgba32((0 + m), (c + m), (x + m), a);
		if (h < 4 * DEG) return rgba32((0 + m), (x + m), (c + m), a);
		if (h < 5 * DEG) return rgba32((x + m), (0 + m), (c + m), a);
		if (h < 6 * DEG) return rgba32((c + m), (0 + m), (x + m), a);
		return rgba32();
	}
	rgb10a2 rgb10a2::fromHSLA(f32 h, f32 s, f32 l, f32 a) {
		f32 c = (1 - std::fabsf(2 * l - 1)) * s;
		f32 x = c * (1 - std::fabsf(MODULO(h / DEG, 2) - 1));
		f32 m = l - c * 0.5f;
		if (h < 1 * DEG) return rgba32((c + m), (x + m), (0 + m), a);
		if (h < 2 * DEG) return rgba32((x + m), (c + m), (0 + m), a);
		if (h < 3 * DEG) return rgba32((0 + m), (c + m), (x + m), a);
		if (h < 4 * DEG) return rgba32((0 + m), (x + m), (c + m), a);
		if (h < 5 * DEG) return rgba32((x + m), (0 + m), (c + m), a);
		if (h < 6 * DEG) return rgba32((c + m), (0 + m), (x + m), a);
		return rgba32();
	}
	rgb10a2 rgb10a2::fromCMYK(f32 c, f32 m, f32 y, f32 k) {
		f32 max = 1 - k;
		return rgb10a2(
			static_cast<u32>((1 - c) * max * 1023u),
			static_cast<u32>((1 - m) * max * 1023u),
			static_cast<u32>((1 - y) * max * 1023u),
			3u);
	}

	rgba32 rgba32::fromRGBA(f32 red, f32 green, f32 blue, f32 alpha) {
		return rgba32(red, green, blue, alpha);
	}
	rgba32 rgba32::fromHSVA(f32 h, f32 s, f32 v, f32 a) {
		f32 c = v * s;
		f32 x = c * (1 - std::fabsf(MODULO(h / DEG, 2) - 1));
		f32 m = v - c;
		if (h < 1 * DEG) return rgba32(c + m, x + m, 0 + m, a);
		if (h < 2 * DEG) return rgba32(x + m, c + m, 0 + m, a);
		if (h < 3 * DEG) return rgba32(0 + m, c + m, x + m, a);
		if (h < 4 * DEG) return rgba32(0 + m, x + m, c + m, a);
		if (h < 5 * DEG) return rgba32(x + m, 0 + m, c + m, a);
		if (h < 6 * DEG) return rgba32(c + m, 0 + m, x + m, a);
		return rgba32();
	}
	rgba32 rgba32::fromHSLA(f32 h, f32 s, f32 l, f32 a) {
		f32 c = (1 - std::fabsf(2 * l - 1)) * s;
		f32 x = c * (1 - std::fabsf(MODULO(h / DEG, 2) - 1));
		f32 m = l - c * 0.5f;
		if (h < 1 * DEG) return rgba32(c + m, x + m, 0 + m, a);
		if (h < 2 * DEG) return rgba32(x + m, c + m, 0 + m, a);
		if (h < 3 * DEG) return rgba32(0 + m, c + m, x + m, a);
		if (h < 4 * DEG) return rgba32(0 + m, x + m, c + m, a);
		if (h < 5 * DEG) return rgba32(x + m, 0 + m, c + m, a);
		if (h < 6 * DEG) return rgba32(c + m, 0 + m, x + m, a);
		return rgba32();
	}
	rgba32 rgba32::fromCMYK(f32 c, f32 m, f32 y, f32 k) {
		f32 max = 1 - k;
		return rgba32(
			(1 - c) * max,
			(1 - m) * max,
			(1 - y) * max,
			1.0f);
	}
}