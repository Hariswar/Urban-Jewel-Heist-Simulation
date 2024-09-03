#ifndef ROBBER_H
#define ROBBER_H

#include "Vec2D.h"

template <class Loot>
class Robber {
public:
	Robber() : _id((unsigned int)-1), _pos({0, 0}), _bagSize(0), _active(false), _greedy(false), _turnsSinceLoot(0), _turnsImmobilized(0), _hasClone(false) {}
	Robber(const Vec2D& pos, bool greedy)
		: _id(nextId++), _pos(pos), _bagSize(0), _active(true), _greedy(greedy), _turnsSinceLoot(0), _turnsImmobilized(0), _hasClone(false) {}
	Robber(const Robber<Loot>& other);

	bool pickUpLoot(const Loot& loot);

	Loot operator--(int);

	void move();

	int calculateTotalValue() const;

	void arrest();

	Robber<Loot> clone(const Vec2D& pos);

	// as funny as it would be to make the Police class a friend of the robber class, use reference getter to allow access to bag
	Loot& operator[](unsigned int i) { return _bag[i]; }

	unsigned int bagSize() const { return _bagSize; }

	Robber<Loot>& operator=(const Robber<Loot>& other);

	template <class L>
	friend std::ostream& operator<<(std::ostream& os, const Robber<L>& robber);

	unsigned int getID() const { return _id; }

	Vec2D getPos() const { return _pos; }

	bool isActive() const { return _active; }

	bool isGreedy() const { return _greedy; }

	bool hasClone() const { return _hasClone; }

	static unsigned int getTotalLoot() { return totalLoot; }

private:
	unsigned int _id;
	Vec2D _pos;
	Loot _bag[20];
	unsigned int _bagSize;
	bool _active;
	bool _greedy;
	int _turnsSinceLoot;
	int _turnsImmobilized;
	bool _hasClone;

	static unsigned int totalLoot, nextId;
};

#include "Robber.hpp"
#endif