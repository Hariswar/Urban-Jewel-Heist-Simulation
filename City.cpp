#include "City.h"

City::City() : _numJewels(60) {
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 11; j++) {
			_grid[i][j] = '.';
		}
	}

	for (size_t i = 0; i < _numJewels; i++) {
		int x = rand() % 11, y = rand() % 13;

		while (_grid[y][x] == 'J') {
			x = rand() % 11;
			y = rand() % 13;
		}

		_grid[y][x] = 'J';

		_jewels[i] = Jewel(Vec2D(x + 1, y + 1));
	}
}

void City::update(Robber<Jewel> robbers[20], int numRobbers, Police police[3]) {
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 11; j++) {
			_grid[i][j] = '.';
		}
	}

	for (size_t i = 0; i < _numJewels; i++) {
		Vec2D pos = _jewels[i].getPos();

		_grid[pos.y - 1][pos.x - 1] = 'J';
	}

	for (int i = 0; i < numRobbers; i++) {
		Vec2D pos = robbers[i].getPos();
		char& symbol = _grid[pos.y - 1][pos.x - 1];

		if (robbers[i].isActive()) {
			if (symbol == '.' || symbol == 'A' || symbol == 'J') {
				symbol = 'r';
			} else if (symbol == 'r') {
				symbol = 'R';
			}
		} else if (symbol == '.' || symbol == 'J') {
			symbol = 'A';
		}
	}

	for (int i = 0; i < 3; i++) {
		Vec2D pos = police[i].getPos();
		char& symbol = _grid[pos.y - 1][pos.x - 1];

		if (symbol == '.' || symbol == 'A' || symbol == 'J') {
			symbol = 'p';
		}
	}
}

Vec2D City::getEmptyTile() const {
	int x = rand() % 11, y = rand() % 13;

	while (_grid[y][x] != '.') {
		x = rand() % 11;
		y = rand() % 13;
	}

	return Vec2D(x + 1, y + 1);
}

void City::returnJewel(const Jewel& jewel) {
	_jewels[_numJewels++] = jewel;
}

void City::returnJewel(const Jewel& jewel, const Vec2D& pos) {
	Jewel returned(jewel);
	returned.setPos(pos);
	_jewels[_numJewels++] = returned;
}

Jewel City::getJewel(const Vec2D& pos) const {
	Jewel jewel;

	for (size_t i = 0; i < _numJewels; i++) {
		if (_jewels[i].getPos() == pos) {
			jewel = _jewels[i];
			break;
		}
	}

	return jewel;
}

void City::removeJewel(const Vec2D& pos) {
	bool shift = false;

	for (size_t i = 0; i < (shift ? _numJewels - 1 : _numJewels); i++) {
		if (!shift) {
			if (_jewels[i].getPos() == pos) {
				shift = true;
			}
		} else {
			_jewels[i] = _jewels[i + 1];
		}
	}

	if (shift) {
		_numJewels--;
	}
}