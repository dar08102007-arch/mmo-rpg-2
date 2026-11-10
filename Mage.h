#pragma once
#include "Unit.h"
class Mage : public Unit {
public:
    Mage(const Health& h, const Armor& a, const Attack& at, int x, int y)
        : Unit(h, a, at, x, y) {}
};
