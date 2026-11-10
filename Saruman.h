#pragma once
#include "Mage.h"
class Saruman : public Mage {
public:
    UnitKind kind() const override { return UnitKind::Saruman; }
    Saruman(int x, int y) : Mage(Health(100), Armor(4), Attack(40), x, y) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Saruman>(*this); }
    std::string getType() const override { return "Saruman"; }
    char symbol() const override { return 'M'; }
};
