#pragma once
namespace cauldron::common {

	template<class T> struct vector2;
	template<class T> struct vector3;
	template<class T> struct vector4;

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

		// Data

		T x, y;
	};

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

		// Data

		T x, y, z;
	};
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

		// Data

		T x, y, z, w;
	};



	// - - - - - - - - - - - - - - -
	// O P E R A T O R S- - - - - -
	// - - - - - - - - - - - - - -


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