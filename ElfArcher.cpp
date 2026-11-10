#include "ElfArcher.h"

ElfArcher::ElfArcher(int x, int y)
	: Archer(Health(60), Armor(2), Attack(14), x, y) {
}

std::unique_ptr<Unit> ElfArcher::clone() const {
	return std::make_unique<ElfArcher>(*this);
}

std::string ElfArcher::getType() const {
	return "ElfArcher";
}

char ElfArcher::symbol() const {
	return 'L';
}
