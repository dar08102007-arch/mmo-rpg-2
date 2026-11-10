#pragma once
#include "Unit.h"
class FlyingUnit : public Unit {
public:
    FlyingUnit(const Health& h, const Armor& a, const Attack& at, int x, int y)
        : Unit(h, a, at, x, y) {}
    bool isFlying() const override { return true; }
};
