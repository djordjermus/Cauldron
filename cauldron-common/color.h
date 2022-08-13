#include "vectors.types.h"
#pragma once
namespace cauldron::common {
	struct rgba8;
	struct rgb10a2;
	struct rgba32;

	// [rgba] 8 bit unsigned normalized channels
	struct rgba8 final {
	public:
		union {
			struct { u8 b, g, r, a; };
			u32 value;
		};

		// CONSTRUCTORS

		rgba8();
		rgba8(u32 code);
		rgba8(u8 red, u8 green, u8 blue, u8 alpha);

		// CASTING

		operator rgb10a2();
		operator rgba32();

		// METHODS

		float4 toRGBA() const;
		float4 toHSVA() const;
		float4 toHSLA() const;
		float4 toCMYK() const;

		// FUNCTIONS

		static rgba8 fromRGBA(f32 red, f32 green, f32 blue, f32 alpha);
		static rgba8 fromHSVA(f32 hue, f32 saturation, f32 value, f32 alpha);
		static rgba8 fromHSLA(f32 hue, f32 saturation, f32 value, f32 alpha);
		static rgba8 fromCMYK(f32 cyan, f32 magenta, f32 yellow, f32 key);
	};

	// [rgb] 10 bit unsigned normalized channels
	// [a] 2 bit unsigned normalized channel
	struct rgb10a2 final {
	public:
		u32 r : 10;
		u32 g : 10;
		u32 b : 10;
		u32 a : 2;

		// CONSTRUCTORS

		rgb10a2();
		rgb10a2(u32 r, u32 g, u32 b, u32 a);
		rgb10a2(u32 code); // LOSS OF DATA

		// CASTING

		operator rgba8();
		operator rgba32();

		// METHODS

		float4 toRGBA() const;
		float4 toHSVA() const;
		float4 toHSLA() const;
		float4 toCMYK() const;

		// FUNCTIONS

		static rgb10a2 fromRGBA(f32 red, f32 green, f32 blue, f32 alpha);
		static rgb10a2 fromHSVA(f32 hue, f32 saturation, f32 value, f32 alpha);
		static rgb10a2 fromHSLA(f32 hue, f32 saturation, f32 value, f32 alpha);
		static rgb10a2 fromCMYK(f32 cyan, f32 magenta, f32 yellow, f32 key);
	};

	// [rgba] 32 bit f32 channels
	struct rgba32 final {
	public:
		f32 r, g, b, a;

		// CONSTRUCTORS

		rgba32();
		rgba32(u32 code);
		rgba32(f32 red, f32 green, f32 blue, f32 alpha);

		// CASTING

		operator rgba8();
		operator rgb10a2();

		// METHODS

		float4 toRGBA() const;
		float4 toHSVA() const;
		float4 toHSLA() const;
		float4 toCMYK() const;

		// FUNCTIONS

		static rgba32 fromRGBA(f32 red, f32 green, f32 blue, f32 alpha);
		static rgba32 fromHSVA(f32 hue, f32 saturation, f32 value, f32 alpha);
		static rgba32 fromHSLA(f32 hue, f32 saturation, f32 value, f32 alpha);
		static rgba32 fromCMYK(f32 cyan, f32 magenta, f32 yellow, f32 key);
	};
}