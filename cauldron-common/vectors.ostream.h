#include "vectors.h"
#include <ostream>
#pragma once
template<class T>
std::ostream& operator << (std::ostream& out, cauldron::common::vector2<T> vec) {
	out << vec.x << ", " << vec.y;
	return out;
}
template<class T>
std::ostream& operator << (std::ostream& out, cauldron::common::vector3<T> vec) {
	out << vec.x << ", " << vec.y << ", " << vec.z;
	return out;
}
template<class T>
std::ostream& operator << (std::ostream& out, cauldron::common::vector4<T> vec) {
	out << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
	return out;
}

template<class T>
std::wostream& operator << (std::wostream& out, cauldron::common::vector2<T> vec) {
	out << vec.x << L", " << vec.y;
	return out;
}
template<class T>
std::wostream& operator << (std::wostream& out, cauldron::common::vector3<T> vec) {
	out << vec.x << L", " << vec.y << L", " << vec.z;
	return out;
}
template<class T>
std::wostream& operator << (std::wostream& out, cauldron::common::vector4<T> vec) {
	out << vec.x << L", " << vec.y << L", " << vec.z << L", " << vec.w;
	return out;
}
