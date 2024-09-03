#ifndef CITY_H
#define CITY_H

#include <iostream>

#include "City.h"
#include "Jewel.h"
#include "Police.h"

class City {
public:
	City();

	void update(Robber<Jewel> robbers[20], int numRobbers, Police police[3]);

	void render() const;

	Vec2D getEmptyTile() const;

	void returnJewel(const Jewel& jewel);

	void returnJewel(const Jewel& jewel, const Vec2D& pos);

	Jewel getJewel(const Vec2D& pos) const;

	void removeJewel(const Vec2D& pos);

private:
	char _grid[13][11];
	Jewel _jewels[60];
	unsigned int _numJewels;
};

#endif