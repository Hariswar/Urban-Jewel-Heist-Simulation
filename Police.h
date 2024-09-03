#ifndef POLICE_H
#define POLICE_H

#include <iostream>

#include "Jewel.h"
#include "Robber.h"
#include "Vec2D.h"

class Police {
public:
	Police() : _id((unsigned int)-1), _pos({0, 0}), _confiscatedLoot(0), _numRobbersArrested(0) {}
	Police(const Vec2D& pos) : _id(nextId++), _pos(pos), _confiscatedLoot(0), _numRobbersArrested(0) {}

	void arrest(Robber<Jewel>& robber, bool group);

	Vec2D move();

	void shareLoot(Police& other);

	Police& operator=(const Police& other);

	unsigned int getID() const { return _id; }

	Vec2D getPos() const { return _pos; }

	friend std::ostream& operator<<(std::ostream& os, const Police& police);

private:
	unsigned int _id;
	Vec2D _pos;
	int _confiscatedLoot;
	Robber<Jewel> _robbersArrested[20];
	unsigned int _numRobbersArrested;

	static unsigned int nextId;
};

#endif