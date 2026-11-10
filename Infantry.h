#pragma once
#include "Unit.h"

class Infantry : public Unit {
public:
	Infantry(const Health& health, const Armor& armor, const Attack& attack, int x, int y )
		: Unit(health, armor, attack, x, y){ }
};
