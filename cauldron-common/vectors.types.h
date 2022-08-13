#include "primitives.h"
#include "vectors.h"
#pragma once
namespace cauldron::common {
	using float4  = vector4<f32>;
	using float3  = vector3<f32>;
	using float2  = vector2<f32>;
	using double4 = vector4<f64>;
	using double3 = vector3<f64>;
	using double2 = vector2<f64>;

	using ubyte4  = vector4<u8>;
	using ubyte3  = vector3<u8>;
	using ubyte2  = vector2<u8>;
	using byte4   = vector4<i8>;
	using byte3   = vector3<i8>;
	using byte2   = vector2<i8>;

	using ushort4 = vector4<u16>;
	using ushort3 = vector3<u16>;
	using ushort2 = vector2<u16>;
	using short4  = vector4<i16>;
	using short3  = vector3<i16>;
	using short2  = vector2<i16>;

	using uint4   = vector4<u32>;
	using uint3   = vector3<u32>;
	using uint2   = vector2<u32>;
	using int4	= vector4<i32>;
	using int3	= vector3<i32>;
	using int2	= vector2<i32>;

	using ulong4  = vector4<u64>;
	using ulong3  = vector3<u64>;
	using ulong2  = vector2<u64>;
	using long4   = vector4<i64>;
	using long3   = vector3<i64>;
	using long2   = vector2<i64>;
}
