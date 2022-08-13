#include "../math.h"
#include <cmath>
namespace cauldron::common {
	template<class T>
	inline T clamp(T val, T min, T max) {
		return (val > max ? max : (val < min ? min : val));
	}
	template<class T>
	inline T lerp(T coefficient, T zero, T one) {
		return zero + coefficient * (one - zero);
	}
	template<class T>
	inline T inverseLerp(T point, T from, T to) {
		return (point - from) / (to - from);
	}

	f64 Math::clamp(f64 value, f64 minimum, f64 maximum) {
		return cauldron::common::clamp(value, minimum, maximum);
	}
	f32 Math::clamp(f32 value, f32 minimum, f32 maximum) {
		return cauldron::common::clamp(value, minimum, maximum);
	}
	i64 Math::clamp(i64 value, i64 minimum, i64 maximum) {
		return cauldron::common::clamp(value, minimum, maximum);
	}
	i32 Math::clamp(i32 value, i32 minimum, i32 maximum) {
		return cauldron::common::clamp(value, minimum, maximum);
	}
	u64 Math::clamp(u64 value, u64 minimum, u64 maximum) {
		return cauldron::common::clamp(value, minimum, maximum);
	}
	u32 Math::clamp(u32 value, u32 minimum, u32 maximum) {
		return cauldron::common::clamp(value, minimum, maximum);
	}



	f64 Math::lerp(f64 coefficient, f64 zero, f64 one) {
		return cauldron::common::lerp(coefficient, zero, one);
	}
	f64 Math::inverseLerp(f64 point, f64 from, f64 to) {
		return cauldron::common::inverseLerp(point, from, to);
	}
	f64 Math::remap(f64 p1, f64 x1, f64 y1, f64 x2, f64 y2) {
		return cauldron::common::lerp(cauldron::common::inverseLerp(p1, x1, y1), x2, y2);
	}



	f32 Math::lerp(f32 coefficient, f32 zero, f32 one) {
		return cauldron::common::lerp(coefficient, zero, one);
	}
	f32 Math::inverseLerp(f32 point, f32 from, f32 to) {
		return cauldron::common::inverseLerp(point, from, to);
	}
	f32 Math::remap(f32 p1, f32 x1, f32 y1, f32 x2, f32 y2) {
		return cauldron::common::lerp(cauldron::common::inverseLerp(p1, x1, y1), x2, y2);
	}



	f64 Math::sin(f64 radians) {
		return std::sin(radians);
	}
	f64 Math::cos(f64 radians) {
		return std::cos(radians);
	}
	f64 Math::tan(f64 radians) {
		return std::tan(radians);
	}
	f64 Math::cot(f64 radians) {
		return 1.0 / std::tan(radians);
	}
	f64 Math::asin(f64 value) {
		return std::asin(value);
	}
	f64 Math::acos(f64 value) {
		return std::acos(value);
	}
	f64 Math::atan(f64 value) {
		return std::atan(value);
	}
	f64 Math::acot(f64 value) {
		return std::atan(1.0 / value);
	}



	f32 Math::sin(f32 radians) {
		return std::sin(radians);
	}
	f32 Math::cos(f32 radians) {
		return std::cos(radians);
	}
	f32 Math::tan(f32 radians) {
		return std::tan(radians);
	}
	f32 Math::cot(f32 radians) {
		return 1.0F / std::tan(radians);
	}
	f32 Math::asin(f32 value) {
		return std::asin(value);
	}
	f32 Math::acos(f32 value) {
		return std::acos(value);
	}
	f32 Math::atan(f32 value) {
		return std::atan(value);
	}
	f32 Math::acot(f32 value) {
		return std::atan(1.0F / value);
	}
}