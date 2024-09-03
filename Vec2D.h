#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>
#include <random>
#include <string>

struct Vec2D {
	int x, y;

	double distanceTo(const Vec2D& other);

	Vec2D& operator+=(const Vec2D& other);
};

Vec2D operator+(const Vec2D& a, const Vec2D& b);

bool operator==(const Vec2D& a, const Vec2D& b);

Vec2D randDirection();

std::string to_string(const Vec2D& vec);

#endif