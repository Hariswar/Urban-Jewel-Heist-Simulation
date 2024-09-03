#include "Vec2D.h"

using namespace std;

double Vec2D::distanceTo(const Vec2D& other) {
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

Vec2D& Vec2D::operator+=(const Vec2D& other) {
	x += other.x;
	y += other.y;

	return *this;
}

Vec2D operator+(const Vec2D& a, const Vec2D& b) {
	return Vec2D(a.x + b.x, a.y + b.y);
}

bool operator==(const Vec2D& a, const Vec2D& b) {
	return a.x == b.x && a.y == b.y;
}

Vec2D randDirection() {
	int dir = rand() % 8;

	// there might be a closed-form solution to describe this transformation, but im too dum-dum to figure it out
	switch (dir) {
		case 0:
			return Vec2D(-1, 1);
		case 1:
			return Vec2D(0, 1);
		case 2:
			return Vec2D(1, 1);
		case 3:
			return Vec2D(-1, 0);
		case 4:
			return Vec2D(1, 0);
		case 5:
			return Vec2D(-1, -1);
		case 6:
			return Vec2D(0, -1);
		case 7:
			return Vec2D(1, -1);
		default:  // impossible
			return Vec2D(0, 0);
	}
}

string to_string(const Vec2D& vec) {
	return "(" + to_string(vec.x) + ", " + to_string(vec.y) + ")";
}