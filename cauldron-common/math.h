#include "primitives.h"
#pragma once
namespace cauldron::common {
	class Math final {
	public:
		static constexpr f64 pi = 3.14159265358979323846;
		static constexpr f64 tau = 3.14159265358979323846 * 2.0;

		static f64 clamp(f64 value, f64 minimum, f64 maximum);
		static f32 clamp(f32 value, f32 minimum, f32 maximum);
		static i64 clamp(i64 value, i64 minimum, i64 maximum);
		static i32 clamp(i32 value, i32 minimum, i32 maximum);
		static u64 clamp(u64 value, u64 minimum, u64 maximum);
		static u32 clamp(u32 value, u32 minimum, u32 maximum);
		
		static f64 lerp(f64 coefficient, f64 zero, f64 one);
		static f64 inverseLerp(f64 point, f64 from, f64 to);
		static f64 remap(f64 p1, f64 x1, f64 y1, f64 x2, f64 y2);

		static f32 lerp(f32 coefficient, f32 zero, f32 one);
		static f32 inverseLerp(f32 point, f32 from, f32 to);
		static f32 remap(f32 p1, f32 x1, f32 y1, f32 x2, f32 y2);

		static f64 sin(f64 radians);
		static f64 cos(f64 radians);
		static f64 tan(f64 radians);
		static f64 cot(f64 radians);
		static f64 asin(f64 value);
		static f64 acos(f64 value);
		static f64 atan(f64 value);
		static f64 acot(f64 value);

		static f32 sin(f32 radians);
		static f32 cos(f32 radians);
		static f32 tan(f32 radians);
		static f32 cot(f32 radians);
		static f32 asin(f32 value);
		static f32 acos(f32 value);
		static f32 atan(f32 value);
		static f32 acot(f32 value);

	private:
		Math()						 = delete;
		Math(const Math&)			  = delete;
		Math(const Math&&)			 = delete;
		Math& operator=(const Math&)   = delete;
		Math& operator=(const Math&&)  = delete;
		~Math()						= delete;
	};
}