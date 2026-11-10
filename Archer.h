#pragma once
#include "Unit.h"

class Archer : public Unit {
public:
	Archer(const Health& health, const Armor& armor, const Attack& attack, int x, int y)
		: Unit(health, armor, attack, x, y) {
	}
};
