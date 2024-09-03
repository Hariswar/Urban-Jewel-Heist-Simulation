#include "Jewel.h"

Jewel& Jewel::operator*=(int factor) {
	_value *= factor;

	return *this;
}

Jewel operator*(const Jewel& jewel, int factor) {
	return Jewel(jewel._pos, jewel._value * factor);
}