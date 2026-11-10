#include "OrcArcher.h"

OrcArcher::OrcArcher(int x, int y)
	: Archer(Health(80), Armor(5), Attack(18), x, y) {
}

std::unique_ptr<Unit> OrcArcher::clone() const {
	return std::make_unique<OrcArcher>(*this);
}

std::string OrcArcher::getType() const {
	return "OrcArcher";
}

char OrcArcher::symbol() const {
	return 'H';
}
