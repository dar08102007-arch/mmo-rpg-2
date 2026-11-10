#include "Health.h"

Health::Health(int value) {
	if (value < 0) {
		value = 0;
	}
	value_ = value;
}

int Health::getValue() const {
	return value_;
}

void Health::decrease(int amount) {
	if (amount < 0) {
		return;
	}
	value_ -= amount;
	if (value_ < 0) {
		value_ = 0;
	}
}

void Health::increase(int amount) {
	if (amount < 0) {
		return;
	}
	value_ += amount;
}
bool Health::isZero() const {
	return value_ == 0;
}
