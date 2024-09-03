#include "Police.h"

using namespace std;

unsigned int Police::nextId = 0;

void Police::arrest(Robber<Jewel>& robber, bool group) {
	// not checking size because its guaranteed elsewhere that the number of total robers <= 20
	_robbersArrested[_numRobbersArrested] = robber;

	for (size_t i = 0; i < robber.bagSize(); i++) {
		if (group) {
			_robbersArrested[_numRobbersArrested][i] *= 2;
		} else {
			_robbersArrested[_numRobbersArrested][i] = _robbersArrested[_numRobbersArrested][i] * 2;
		}

		_confiscatedLoot += _robbersArrested[_numRobbersArrested][i].getValue();
	}

	_numRobbersArrested++;

	robber.arrest();
}

Vec2D Police::move() {
	Vec2D old = _pos;

	Vec2D newPos = _pos + randDirection();
	while (newPos.x < 1 || newPos.x > 11 || newPos.y < 1 || newPos.y > 13) {
		newPos = _pos + randDirection();
	}

	_pos = newPos;
	return old;
}

void Police::shareLoot(Police& other) {
	int half = (_confiscatedLoot + other._confiscatedLoot) / 2;
	other._confiscatedLoot = half;
	_confiscatedLoot -= half;
}

Police& Police::operator=(const Police& other) {
	_id = other._id;
	_pos = other._pos;
	_confiscatedLoot = other._confiscatedLoot;
	_numRobbersArrested = other._numRobbersArrested;

	for (size_t i = 0; i < _numRobbersArrested; i++) {
		_robbersArrested[i] = other._robbersArrested[i];
	}

	return *this;
}

ostream& operator<<(ostream& os, const Police& police) {
	return os << "Police id: " << police._id << "\n"
			  << "\tConfiscated jewels amount: $" << police._confiscatedLoot << "\n"
			  << "\tFinal number of robbers caught: " << police._numRobbersArrested;
}