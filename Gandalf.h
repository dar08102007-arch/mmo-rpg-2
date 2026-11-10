#pragma once
#include "Mage.h"
class Gandalf : public Mage {
public:
    UnitKind kind() const override { return UnitKind::Gandalf; }
    Gandalf(int x, int y) : Mage(Health(110), Armor(5), Attack(35), x, y) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Gandalf>(*this); }
    std::string getType() const override { return "Gandalf"; }
    char symbol() const override { return 'G'; }
};
