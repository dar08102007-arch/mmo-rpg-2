#pragma once
#include "FlyingUnit.h"
class GreatEagle : public FlyingUnit {
public:
    UnitKind kind() const override { return UnitKind::GreatEagle; }
    GreatEagle(int x, int y) : FlyingUnit(Health(95), Armor(3), Attack(25), x, y) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<GreatEagle>(*this); }
    std::string getType() const override { return "GreatEagle"; }
    char symbol() const override { return 'E'; }
};
