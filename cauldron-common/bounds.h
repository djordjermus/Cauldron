#include "vectors.h"
#pragma once
namespace cauldron::common {
	template<class T> struct bounds2;
	template<class T> struct bounds3;

	template<class T> struct bounds2 {
	public:

		// Constructors

		bounds2() : from(), to() {}
		bounds2(T x1, T y1, T x2, T y2) :
			from(x1, y1), to(x2, y2) {}
		bounds2(const vector2<T>& from, const vector2<T>& size) :
			from(from), to(from + size) {}
		bounds2(const vector4<T> bounds) :
			from(bounds.x, bounds.y), to(bounds.z, bounds.w) {}

		// Getters

		vector2<T> size() const {
			return vector2<T>(to.x - from.x, to.y - from.y);
		}
		T width() const		{ return to.x - from.x; }
		T height() const	{ return to.y - from.y; }

		// Casts

		template<class U = T>
		inline bounds2<U> asB2() const { return bounds2<U>((U)from.x, (U)from.y, (U)to.x, (U)to.y); }
		template<class U = T>
		inline bounds3<U> asB3() const { return bounds3<U>((U)from.x, (U)from.y, U(), (U)to.x, (U)to.y, U()); }
		template<class U>
		inline bounds2<U> as() const { return asB2<U>(); }

		template<class U>
		inline operator bounds2<U>() const { return asB2<U>(); }
		template<class U>
		inline operator bounds3<U>() const { return asB3<U>(); }

		template<class U>
		inline bool operator==(const bounds2<U>& rhs) const {
			return
				this->from.x == rhs.from.x &&
				this->from.y == rhs.from.y &&
				this->to.x == rhs.to.x &&
				this->to.y == rhs.to.y;
		}
		template<class U>
		inline bool operator!=(const bounds2<U>& rhs) const {
			return
				this->from.x != rhs.from.x ||
				this->from.y != rhs.from.y ||
				this->to.x != rhs.to.x ||
				this->to.y != rhs.to.y;
		}

		// Data

		vector2<T> from;
		vector2<T> to;
	};

	template<class T> struct bounds3 {
	public:

		// Constructors

		bounds3() : from(), to() {}
		bounds3(T x1, T y1, T z1, T x2, T y2, T z2) :
			from(x1, y1, z1), to(x2, y2, z2) {}
		bounds3(const vector3<T>& from, const vector3<T>& size) :
			from(from), to(from + size) {}

		// Getters

		vector3<T> size() {
			return vector2<T>(to.x - from.x, to.y - from.y, to.z - from.z);
		}
		T width()  { return to.x - from.x; }
		T height() { return to.y - from.y; }
		T depth()  { return to.z - from.z; }

		// Casts

		template<class U = T>
		inline bounds2<U> asB2() const { return bounds2<U>((U)from.x, (U)from.y, (U)to.x, (U)to.y); }
		template<class U = T>
		inline bounds3<U> asB3() const { return bounds3<U>((U)from.x, (U)from.y, (U)from.z, (U)to.x, (U)to.y, (U)to.z); }
		template<class U>
		inline bounds2<U> as() const { return asB3<U>(); }

		template<class U>
		inline operator bounds2<T>() const { return asB2<U>(); }
		template<class U>
		inline operator bounds3<U>() const { return asB3<U>(); }

		template<class U = T>
		inline bool operator==(const bounds3<U>& rhs) const {
			return
				this->from.x == rhs.from.x &&
				this->from.y == rhs.from.y &&
				this->from.z == rhs.from.z &&
				this->to.x == rhs.to.x &&
				this->to.y == rhs.to.y &&
				this->to.z == rhs.to.z;
		}
		template<class U = T>
		inline bool operator!=(const bounds3<U>& rhs) const {
			return
				this->from.x != rhs.from.x ||
				this->from.y != rhs.from.y ||
				this->from.z != rhs.from.z ||
				this->to.x != rhs.to.x ||
				this->to.y != rhs.to.y ||
				this->to.z != rhs.to.z;
		}

		// Data

		vector3<T> from;
		vector3<T> to;
	};
}