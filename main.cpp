#include <random>

#include "City.h"

using namespace std;

int main() {
	srand(100);

	City city;
	Robber<Jewel> robbers[20];
	Police police[3];
	int numRobbers = 4, turn = 1;
	bool won = false, lost = false;

	for (int i = 0; i < 3; i++) {
		Vec2D pos = city.getEmptyTile();

		police[i] = Police(pos);
	}

	for (int i = 0; i < 4; i++) {
		Vec2D pos = city.getEmptyTile();

		robbers[i] = Robber<Jewel>(pos, i < 2);
	}

	cout << "Starting:" << endl;
	city.update(robbers, numRobbers, police);
	city.render();

	while (turn <= 80) {
		if (Robber<Jewel>::getTotalLoot() >= 6000) {
			won = true;
			break;
		}

		bool allArrested = true;
		for (int i = 0; i < numRobbers; i++) {
			if (robbers[i].isActive()) {
				bool moveAgain = false;
				int timesMoved = 0;

				do {
					cout << "robber " << i << " moving (" << robbers[i].getPos().x << ", " << robbers[i].getPos().y << ") to (";
					robbers[i].move();
					cout << robbers[i].getPos().x << ", " << robbers[i].getPos().y << ")" << endl;
					timesMoved++;

					city.update(robbers, numRobbers, police);

					if (rand() % 10 < 6) {
						Jewel jewel = robbers[i]--;

						if (jewel.getValue() != 0) {
							Vec2D closest;
							double distance = INFINITY;
							for (int x = 1; x <= 11; x++) {
								for (int y = 1; y <= 13; y++) {
									Vec2D pos(x, y);
									bool hasGem = city.getJewel(pos).getValue() != 0;
									bool hasRobber = false, hasPolice = false;

									for (int j = 0; j < numRobbers; j++) {
										if (robbers[j].getPos() == pos) {
											hasRobber = true;
											break;
										}
									}

									for (int j = 0; j < 3; j++) {
										if (police[j].getPos() == pos) {
											hasPolice = true;
											break;
										}
									}

									if (!hasGem && !hasRobber && !hasPolice) {
										if (robbers[i].getPos().distanceTo(pos) < distance) {
											closest = pos;
											distance = robbers[i].getPos().distanceTo(pos);
										}
									}
								}
							}

							// not possible for grid to be completely full, so no need to add mechanism for whether a space was found or not
							city.returnJewel(jewel, closest);
							city.update(robbers, numRobbers, police);
						}
					}

					if (robbers[i].isGreedy()) {
						for (int j = 0; j < numRobbers; j++) {
							if (i != j && robbers[i].getPos() == robbers[j].getPos()) {
								int halfBag = robbers[i].bagSize() / 2;

								for (int k = 0; k < halfBag; k++) {
									Jewel jewel = robbers[i]--;
									Vec2D newPos = city.getEmptyTile();

									jewel.setPos(newPos);
									city.returnJewel(jewel);
								}

								city.update(robbers, numRobbers, police);
								break;
							}
						}
					}

					Jewel jewel = city.getJewel(robbers[i].getPos());
					if (jewel.getValue() != 0) {
						moveAgain = robbers[i].pickUpLoot(jewel) && timesMoved < 3;
						city.removeJewel(robbers[i].getPos());
						city.update(robbers, numRobbers, police);
					}

					for (int j = 0; j < 3; j++) {
						if (robbers[i].getPos() == police[j].getPos()) {
							police[j].arrest(robbers[i], false);
						}
					}
				} while (moveAgain);

				if (numRobbers < 20 && !robbers[i].hasClone() && robbers[i].calculateTotalValue() >= 1600) {
					Vec2D pos = city.getEmptyTile();

					robbers[numRobbers++] = robbers[i].clone(pos);
				}

				if (robbers[i].isActive()) {
					allArrested = false;
				}

				city.update(robbers, numRobbers, police);
			}
		}

		for (int i = 0; i < 3; i++) {
			police[i].move();

			for (int j = 0; j < numRobbers; j++) {
				if (police[i].getPos() == robbers[j].getPos() && robbers[j].isActive()) {
					police[i].arrest(robbers[j], true);
				}
			}

			for (int j = 0; j < numRobbers; j++) {
				if (i != j && police[i].getPos() == police[j].getPos()) {
					police[i].shareLoot(police[j]);
				}
			}

			Jewel jewel = city.getJewel(police[i].getPos());
			if (jewel.getValue() != 0) {
				city.removeJewel(police[i].getPos());
			}
		}

		if (allArrested) {
			lost = true;
			break;
		}

		cout << "Turn " << turn << ":" << endl;
		city.update(robbers, numRobbers, police);
		city.render();

		turn++;
	}

	if (won) {
		cout << "The robbers win the chase because they accumulated $6000" << endl;
	} else if (lost) {
		cout << "The robbers lose because they all got caught!" << endl;
	} else {
		cout << "The robbers win the chase because maximum turns (80) have been reached" << endl;
	}

	for (int i = 0; i < 3; i++) {
		cout << police[i] << endl;
	}

	for (int i = 0; i < numRobbers; i++) {
		cout << robbers[i] << endl;
	}

	return 0;
}