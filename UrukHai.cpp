#include "UrukHai.h"

UrukHai::UrukHai(int x, int y)
	: Infantry(Health(90), Armor(8), Attack(12), x, y) {
}

std::unique_ptr<Unit> UrukHai::clone() const {
	return std::make_unique<UrukHai>(*this);
}

std::string UrukHai::getType() const {
	return "UrukHai";
}

char UrukHai::symbol() const {
	return 'P';
}
