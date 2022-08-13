#include "bounds.h"
#include "vectors.ostream.h"
#include <ostream>
#pragma once
template<class T>
std::ostream& operator << (std::ostream& out, const cauldron::common::bounds2<T>& bounds) {
	out << bounds.from << " - " << bounds.to;
	return out;
}
template<class T>
std::ostream& operator << (std::ostream& out, const cauldron::common::bounds3<T>& bounds) {
	out << bounds.from << " - " << bounds.to;
	return out;
}

template<class T>
std::wostream& operator << (std::wostream& out, const cauldron::common::bounds2<T>& bounds) {
	out << bounds.from << L" - " << bounds.to;
	return out;
}
template<class T>
std::wostream& operator << (std::wostream& out, const cauldron::common::bounds3<T>& bounds) {
	out << bounds.from << L" - " << bounds.to;
	return out;
}
