#pragma once
#include "FlyingUnit.h"
class FellBeast : public FlyingUnit {
public:
    UnitKind kind() const override { return UnitKind::FellBeast; }
    FellBeast(int x, int y) : FlyingUnit(Health(105), Armor(4), Attack(28), x, y) {}
    std::unique_ptr<Unit> clone() const override { return std::make_unique<FellBeast>(*this); }
    std::string getType() const override { return "FellBeast"; }
    char symbol() const override { return 'F'; }
};
