#include "Robber.h"

template <class Loot>
unsigned int Robber<Loot>::nextId = 0;

template <class Loot>
unsigned int Robber<Loot>::totalLoot = 0;

template <class Loot>
Robber<Loot>::Robber(const Robber<Loot>& other)
	: _id(other._id),
	  _pos(other._pos),
	  _bagSize(other._bagSize),
	  _active(other._active),
	  _greedy(other._greedy),
	  _turnsSinceLoot(other._turnsSinceLoot),
	  _turnsImmobilized(other._turnsImmobilized) {
	for (size_t i = 0; i < _bagSize; i++) {
		_bag[i] = other._bag[i];
	}
}

template <class Loot>
bool Robber<Loot>::pickUpLoot(const Loot& loot) {
	if (_bagSize >= 20) {
		return false;
	} else {
		_bag[_bagSize++] = loot;
		totalLoot += loot.getValue();
		_turnsSinceLoot = 0;

		return _greedy && loot.getValue() % 2 == 0;
	}
}

template <class Loot>
Loot Robber<Loot>::operator--(int) {
	if (_bagSize == 0) {
		return Jewel();
	} else {
		int idx = rand() % _bagSize;
		Loot lost = _bag[idx];

		for (size_t i = idx; i < _bagSize - 1; i++) {
			_bag[i] = _bag[i + 1];
		}

		_bagSize--;
		totalLoot -= lost.getValue();
		return lost;
	}
}

template <class Loot>
void Robber<Loot>::move() {
	if (_turnsImmobilized > 0) {
		_turnsImmobilized--;
	} else {
		if (_turnsSinceLoot >= 5) {
			// not 2 because this turn counts as one turn of immobilization
			_turnsImmobilized = 1;
			_turnsSinceLoot = 0;
		} else {
			Vec2D newPos = _pos + randDirection();
			while (newPos.x < 1 || newPos.x > 11 || newPos.y < 1 || newPos.y > 13) {
				newPos = _pos + randDirection();
			}

			_pos = newPos;
			_turnsSinceLoot++;
		}
	}
}

template <class Loot>
int Robber<Loot>::calculateTotalValue() const {
	int total = 0;

	for (size_t i = 0; i < _bagSize; i++) {
		total += _bag[i].getValue();
	}

	return total;
}

template <class Loot>
void Robber<Loot>::arrest() {
	totalLoot -= calculateTotalValue();
	_active = false;
	_bagSize = 0;
}

template <class Loot>
Robber<Loot> Robber<Loot>::clone(const Vec2D& pos) {
	Robber<Loot> copy(*this);
	copy._id = nextId++;
	copy._pos = pos;
	copy._bagSize = 0;
	copy._turnsSinceLoot = 0;
	copy._turnsImmobilized = 0;

	_hasClone = true;

	return copy;
}

template <class Loot>
Robber<Loot>& Robber<Loot>::operator=(const Robber<Loot>& other) {
	_id = other._id;
	_pos = other._pos;
	_bagSize = other._bagSize;
	_active = other._active;
	_greedy = other._greedy;

	for (size_t i = 0; i < _bagSize; i++) {
		_bag[i] = other._bag[i];
	}

	return *this;
}

template <class Loot>
std::ostream& operator<<(std::ostream& os, const Robber<Loot>& robber) {
	return os << (robber._greedy ? "Greedy" : "Ordinary") << " robber id: " << robber._id << "\n"
			  << "\tFinal number of jewels picked up: " << robber._bagSize << "\n"
			  << "\tTotal jewel worth: " << robber.calculateTotalValue();
}