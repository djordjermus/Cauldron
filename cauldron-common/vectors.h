#include "primitives.h"
#pragma once
namespace cauldron::common {

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // T E M P L A T E   V E C T O R S - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	template<class T> struct vector2;
	template<class T> struct vector3;
	template<class T> struct vector4;
	template<class T> struct matrix4x4;

	// 2D vector - two components - x, y of type T
	template<class T> struct vector2 final {
	public:

		// Constructors

		vector2() :
			x(), y() {}
		vector2(T x, T y = T()) :
			x(x), y(y) {}

		// Casting

		template<class U = T>
		inline vector2<U> asV2() const { return vector2<U>((U)x, (U)y); }
		template<class U = T>
		inline vector3<U> asV3() const { return vector3<U>((U)x, (U)y, U()); }
		template<class U = T>
		inline vector4<U> asV4() const { return vector4<U>((U)x, (U)y, U(), U()); }
		template<class U = T>
		inline vector2<U> as() const { return asV2<U>(); }

		template<class U>
		inline operator vector2<U>() const { return as<U>(); }
		inline operator vector3<T>() const { return asV3(); }
		inline operator vector4<T>() const { return asV4(); }

		// Operators

		template<class U>
		inline bool operator==(const vector2<U>& rhs) {
			return x == rhs.x && y == rhs.y;
		}
		template<class U>
		inline bool operator==(const vector3<U>& rhs) {
			return x == rhs.x && y == rhs.y && rhs.z == 0;
		}
		template<class U>
		inline bool operator==(const vector4<U>& rhs) {
			return x == rhs.x && y == rhs.y && rhs.z == 0 && rhs.w == 0;
		}
		template<class U>
		inline bool operator!=(const vector2<U>& rhs) {
			return !(*this == rhs);
		}
		template<class U>
		inline bool operator!=(const vector3<U>& rhs) {
			return !(*this == rhs);
		}
		template<class U>
		inline bool operator!=(const vector4<U>& rhs) {
			return !(*this == rhs);
		}

		// Data

		T x, y;
	};

	// 3D vector - three components - x, y, z of type T
	template<class T> struct vector3 final {
	public:

		// Constructors

		vector3() :
			x(), y(), z() {}
		vector3(T x, T y = T(), T z = T()) :
			x(x), y(y), z(z) {}

		// Casting

		template<class U = T>
		inline vector2<U> asV2() const { return vector2<U>((U)x, (U)y); }
		template<class U = T>
		inline vector3<U> asV3() const { return vector3<U>((U)x, (U)y, (U)z); }
		template<class U = T>
		inline vector4<U> asV4() const { return vector4<U>((U)x, (U)y, (U)z, U()); }
		template<class U = T>
		inline vector3<U> as() const { return asV3<U>(); }

		template<class U>
		inline operator vector3<U>() const { return as<U>(); }
		inline operator vector2<T>() const { return asV2(); }
		inline operator vector4<T>() const { return asV4(); }

		// Operators

		template<class U>
		inline bool operator==(const vector2<U>& rhs) {
			return x == rhs.x && y == rhs.y && z == 0;
		}
		template<class U>
		inline bool operator==(const vector3<U>& rhs) {
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}
		template<class U>
		inline bool operator==(const vector4<U>& rhs) {
			return x == rhs.x && y == rhs.y && z == rhs.z && rhs.w == 0;
		}
		template<class U>
		inline bool operator!=(const vector2<U>& rhs) {
			return !(*this == rhs);
		}
		template<class U>
		inline bool operator!=(const vector3<U>& rhs) {
			return !(*this == rhs);
		}
		template<class U>
		inline bool operator!=(const vector4<U>& rhs) {
			return !(*this == rhs);
		}

		// Data

		T x, y, z;
	};

	// 4D vector - four components - x, y, z, w of type T
	template<class T> struct vector4 final {
	public:

		// Constructors

		vector4() :
			x(), y(), z(), w() {}
		vector4(T x, T y = T(), T z = T(), T w = T()) :
			x(x), y(y), z(z), w(w){}

		// Casting

		template<class U = T>
		inline vector2<U> asV2() const { return vector2<U>((U)x, (U)y); }
		template<class U = T>
		inline vector3<U> asV3() const { return vector3<U>((U)x, (U)y, (U)z); }
		template<class U = T>
		inline vector4<U> asV4() const { return vector4<U>((U)x, (U)y, (U)z, (U)w); }
		template<class U = T>
		inline vector4<U> as() const { return asV4<U>(); }
		
		template<class U>
		inline operator vector4<U>() const { return as<U>(); }
		inline operator vector2<T>() const { return asV2(); }
		inline operator vector3<T>() const { return asV3(); }

		// Operators

		template<class U>
		inline bool operator==(const vector2<U>& rhs) {
			return x == rhs.x && y == rhs.y && z == 0 && w == 0;
		}
		template<class U>
		inline bool operator==(const vector3<U>& rhs) {
			return x == rhs.x && y == rhs.y && z == rhs.z && w == 0;
		}
		template<class U>
		inline bool operator==(const vector4<U>& rhs) {
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}
		template<class U>
		inline bool operator!=(const vector2<U>& rhs) {
			return !(*this == rhs);
		}
		template<class U>
		inline bool operator!=(const vector3<U>& rhs) {
			return !(*this == rhs);
		}
		template<class U>
		inline bool operator!=(const vector4<U>& rhs) {
			return !(*this == rhs);
		}

		// Data
		union {
			struct { T x, y, z, w; };
			T v[4];
		};
	};

	// 4X4 matrix - four components - m[4] of type vector4<T>
	template<class T> struct matrix4x4 final {
	using row_t = vector4<T>;

		// Constructors

		matrix4x4() : 
			m{} { }
		matrix4x4(const row_t m1, const row_t m2, const row_t m3, const row_t m4) :
			m{ m1, m2, m3, m4 } { }
		matrix4x4(
			const T m11, const T m12, const T m13, const T m14,
			const T m21, const T m22, const T m23, const T m24,
			const T m31, const T m32, const T m33, const T m34,
			const T m41, const T m42, const T m43, const T m44) :
			m{	{m11, m12, m13, m14}, 
				{m21, m22, m23, m24}, 
				{m31, m32, m33, m34},
				{m41, m42, m43, m44} } { }

		// Casts

		template<class U = T>
		inline matrix4x4<U> as() const { 
			return matrix4x4<U>(m[0].as<U>(), m[1].as<U>(), m[2].as<U>(), m[3].as<U>());
		}
		template<class U>
		inline operator matrix4x4<U>() const { return as<U>(); }

		// Operators

		template<class U>
		inline bool operator==(const matrix4x4<U>& other) {
			return 
				m[0] == other.m[0] && 
				m[1] == other.m[1] && 
				m[2] == other.m[2] && 
				m[3] == other.m[3];
		}
		template<class U>
		inline bool operator!=(const matrix4x4<U>& other) {
			return !(*this == other);
		}
		template<class U>
		inline auto cross(const matrix4x4<U>& rhs) {
			return matrix4x4<decltype(T()* U())>(
				m[0] * rhs.m[0],
				m[1] * rhs.m[1],
				m[2] * rhs.m[2],
				m[3] * rhs.m[3]);
		}
		template<class U>
		inline auto dot(const matrix4x4<U>& rhs) {
			matrix4x4<decltype(T()* U())> ret;

			ret.m[0].x = m[0].x * rhs.m[0].x + m[0].y * rhs.m[1].x + m[0].z * rhs.m[2].x + m[0].w * rhs.m[3].x;
			ret.m[0].y = m[0].x * rhs.m[0].y + m[0].y * rhs.m[1].y + m[0].z * rhs.m[2].y + m[0].w * rhs.m[3].y;
			ret.m[0].z = m[0].x * rhs.m[0].z + m[0].y * rhs.m[1].z + m[0].z * rhs.m[2].z + m[0].w * rhs.m[3].z;
			ret.m[0].w = m[0].x * rhs.m[0].w + m[0].y * rhs.m[1].w + m[0].z * rhs.m[2].w + m[0].w * rhs.m[3].w;

			ret.m[1].x = m[1].x * rhs.m[0].x + m[1].y * rhs.m[1].x + m[1].z * rhs.m[2].x + m[1].w * rhs.m[3].x;
			ret.m[1].y = m[1].x * rhs.m[0].y + m[1].y * rhs.m[1].y + m[1].z * rhs.m[2].y + m[1].w * rhs.m[3].y;
			ret.m[1].z = m[1].x * rhs.m[0].z + m[1].y * rhs.m[1].z + m[1].z * rhs.m[2].z + m[1].w * rhs.m[3].z;
			ret.m[1].w = m[1].x * rhs.m[0].w + m[1].y * rhs.m[1].w + m[1].z * rhs.m[2].w + m[1].w * rhs.m[3].w;

			ret.m[2].x = m[2].x * rhs.m[0].x + m[2].y * rhs.m[1].x + m[2].z * rhs.m[2].x + m[2].w * rhs.m[3].x;
			ret.m[2].y = m[2].x * rhs.m[0].y + m[2].y * rhs.m[1].y + m[2].z * rhs.m[2].y + m[2].w * rhs.m[3].y;
			ret.m[2].z = m[2].x * rhs.m[0].z + m[2].y * rhs.m[1].z + m[2].z * rhs.m[2].z + m[2].w * rhs.m[3].z;
			ret.m[2].w = m[2].x * rhs.m[0].w + m[2].y * rhs.m[1].w + m[2].z * rhs.m[2].w + m[2].w * rhs.m[3].w;

			ret.m[3].x = m[3].x * rhs.m[0].x + m[3].y * rhs.m[1].x + m[3].z * rhs.m[2].x + m[3].w * rhs.m[3].x;
			ret.m[3].y = m[3].x * rhs.m[0].y + m[3].y * rhs.m[1].y + m[3].z * rhs.m[2].y + m[3].w * rhs.m[3].y;
			ret.m[3].z = m[3].x * rhs.m[0].z + m[3].y * rhs.m[1].z + m[3].z * rhs.m[2].z + m[3].w * rhs.m[3].z;
			ret.m[3].w = m[3].x * rhs.m[0].w + m[3].y * rhs.m[1].w + m[3].z * rhs.m[2].w + m[3].w * rhs.m[3].w;

			return ret;
		}
		template<class U>
		inline vector4<decltype(T() * U())> dot(const vector4<U>& rhs) {
			vector4<decltype(T() * U())> ret;

			ret.x = m[0].x * rhs.x + m[0].y * rhs.y + m[0].z * rhs.z + m[0].w * rhs.w;
			ret.y = m[1].x * rhs.x + m[1].y * rhs.y + m[1].z * rhs.z + m[1].w * rhs.w;
			ret.z = m[2].x * rhs.x + m[2].y * rhs.y + m[2].z * rhs.z + m[2].w * rhs.w;
			ret.w = m[3].x * rhs.x + m[3].y * rhs.y + m[3].z * rhs.z + m[3].w * rhs.w;

			return ret;
		}
		// Data
	
		row_t m[4];
	};



	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // T E M P L A T E   O P E R A T O R S - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


	template<class T>
	auto operator+(const vector2<T>& lhs) { return lhs; }
	template<class T>
	auto operator-(const vector2<T>& lhs) { return vector2<decltype(-T())>(-lhs.x, -lhs.y); }
	template<class T, class U>
	auto operator*(const vector2<T>& lhs, const U& rhs) {
		return vector2<decltype(T()* U())>(
			lhs.x * rhs, lhs.y * rhs);
	}
	template<class T, class U>
	auto operator/(const vector2<T>& lhs, const U& rhs) {
		return vector2<decltype(T() / U())>(
			lhs.x / rhs, lhs.y / rhs);
	}
	template<class T, class U>
	auto operator+(const vector2<T>& lhs, const vector2<U>& rhs) {
		return vector2<decltype(T() + U())>(
			lhs.x + rhs.x, lhs.y + rhs.y);
	}
	template<class T, class U = T>
	auto operator-(const vector2<T>& lhs, const vector2<U>& rhs) {
		return vector2<decltype(T() - U())>(
			lhs.x - rhs.x, lhs.y - rhs.y);
	}
	template<class T, class U>
	auto operator*(const vector2<T>& lhs, const vector2<U>& rhs) {
		return vector2<decltype(T()* U())>(
			lhs.x * rhs.x, lhs.y * rhs.y);
	}
	template<class T, class U>
	auto operator/(const vector2<T>& lhs, const vector2<U>& rhs) {
		return vector2<decltype(T() / U())>(
			lhs.x / rhs.x, lhs.y / rhs.y);
	}



	template<class T>
	auto operator+(const vector3<T>& lhs) { return lhs; }
	template<class T>
	auto operator-(const vector3<T>& lhs) { return vector3<decltype(-T())>(-lhs.x, -lhs.y, -lhs.z); }
	template<class T, class U>
	auto operator*(const vector3<T>& lhs, const U& rhs) {
		return vector3<decltype(T()* U())>(
			lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}
	template<class T, class U>
	auto operator/(const vector3<T>& lhs, const U& rhs) {
		return vector3<decltype(T() / U())>(
			lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
	}
	template<class T, class U>
	auto operator+(const vector3<T>& lhs, const vector3<U>& rhs) {
		return vector3<decltype(T() + U())>(
			lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}
	template<class T, class U>
	auto operator-(const vector3<T>& lhs, const vector3<U>& rhs) {
		return vector3<decltype(T() - U())>(
			lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}
	template<class T, class U>
	auto operator*(const vector3<T>& lhs, const vector3<U>& rhs) {
		return vector3<decltype(T()* U())>(
			lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}
	template<class T, class U>
	auto operator/(const vector3<T>& lhs, const vector3<U>& rhs) {
		return vector3<decltype(T() / U())>(
			lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}



	template<class T>
	auto operator+(const vector4<T>& lhs) { return lhs; }
	template<class T>
	auto operator-(const vector4<T>& lhs) { return vector4<decltype(-T())>(-lhs.x, -lhs.y, -lhs.z, -lhs.w); }
	template<class T, class U>
	auto operator*(const vector4<T>& lhs, const U& rhs) {
		return vector4<decltype(T()* U())>(
			lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
	}
	template<class T, class U>
	auto operator/(const vector4<T>& lhs, const U& rhs) {
		return vector4<decltype(T() / U())>(
			lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
	}
	template<class T, class U>
	auto operator+(const vector4<T>& lhs, const vector4<U>& rhs) {
		return vector4<decltype(T()+ U())>(
			lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}
	template<class T, class U>
	auto operator-(const vector4<T>& lhs, const vector4<U>& rhs) {
		return vector4<decltype(T() - U())>(
			lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}
	template<class T, class U>
	auto operator*(const vector4<T>& lhs, const vector4<U>& rhs) {
		return vector4<decltype(T() * U())>(
			lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
	}
	template<class T, class U>
	auto operator/(const vector4<T>& lhs, const vector4<U>& rhs) {
		return vector4<decltype(T() / U())>(
			lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
	}
}