#ifndef JEWEL_H
#define JEWEL_H

#include "Vec2D.h"

class Jewel {
public:
	Jewel() : _pos({0, 0}), _value(0) {}
	Jewel(const Vec2D& pos) : _pos(pos), _value(pow(pos.x + pos.y, 2)) {}
	Jewel(const Vec2D& pos, int value) : _pos(pos), _value(value) {}

	Jewel& operator*=(int other);

	friend Jewel operator*(const Jewel& jewel, int other);

	int getValue() const { return _value; }

	Vec2D getPos() const { return _pos; }

	void setPos(const Vec2D& pos) { _pos = pos; }

private:
	Vec2D _pos;
	int _value;
};

#endif