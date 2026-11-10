#include "Attack.h"

Attack::Attack(int value) {
	if (value < 0) {
		value = 0;
	}
	value_ = value;
}

int Attack::getValue() const {
	return value_;
}

int Attack::calculateDamage(const Armor& targetArmor) const {
	return targetArmor.reduceDamage(value_);
}
