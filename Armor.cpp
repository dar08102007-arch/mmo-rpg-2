#include "Armor.h"

Armor::Armor(int value) {
	if (value < 0) {
		value = 0;
	}
	value_ = value;
}

int Armor::getValue() const {
	return value_;
}

int Armor::reduceDamage(int damage) const {
	int result = damage - value_;
	if (result < 0) {
		result = 0;
	}
	return result;
}
