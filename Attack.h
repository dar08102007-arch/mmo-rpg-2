#pragma once
#include "Armor.h"

class Attack {
public:
	Attack(int value);
	int getValue() const;
	int calculateDamage(const Armor& targetArmor) const;

private:
	int value_;
};
