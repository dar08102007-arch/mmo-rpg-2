#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "UnitKind.h"
struct UnitTypeInfo {
    const std::string name;
    const int maxHealth, baseAttack, baseSpeed, cost, armor;
    const UnitKind type;
    const bool flying;
    UnitTypeInfo(std::string n, int h, int a, int s, int c, int ar, UnitKind t, bool f)
        : name(n), maxHealth(h), baseAttack(a), baseSpeed(s), cost(c), armor(ar), type(t), flying(f) {}
    static const UnitTypeInfo& getInfo(UnitKind kind);
};
