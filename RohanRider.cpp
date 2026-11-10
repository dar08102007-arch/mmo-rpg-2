#include "RohanRider.h"

RohanRider::RohanRider(int x, int y)
	: Cavalry(Health(150), Armor(15), Attack(20), x, y) {
}

std::unique_ptr<Unit> RohanRider::clone() const {
	return std::make_unique<RohanRider>(*this);
}

std::string RohanRider::getType() const {
	return "RohanRider";
}

char RohanRider::symbol() const {
	return 'C';
}
