#include "GondorSoldier.h"

GondorSoldier::GondorSoldier(int x, int y)
	: Infantry(Health(100), Armor(5), Attack(15), x, y) {
}

std::unique_ptr<Unit> GondorSoldier::clone() const {
	return std::make_unique<GondorSoldier>(*this);
}

std::string GondorSoldier::getType() const {
	return "GondorSoldier";
}

char GondorSoldier::symbol() const {
	return 'S';
}
