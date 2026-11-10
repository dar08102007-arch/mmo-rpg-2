#include "WargRider.h"

WargRider::WargRider(int x, int y)
	: Cavalry(Health(90), Armor(4), Attack(16), x, y) {
}

std::unique_ptr<Unit> WargRider::clone() const {
	return std::make_unique<WargRider>(*this);
}

std::string WargRider::getType() const {
	return "WargRider";
}

char WargRider::symbol() const {
	return 'h';
}
