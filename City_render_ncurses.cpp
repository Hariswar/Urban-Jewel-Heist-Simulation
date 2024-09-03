#include "City.h"
#include "ncurses.h"

using namespace std;

void City::render() const {
	for (int i = 12; i >= 0; i--) {
		for (int j = 0; j < 11; j++) {
			addch(_grid[i][j]);
		}

		addch('\n');
	}
}