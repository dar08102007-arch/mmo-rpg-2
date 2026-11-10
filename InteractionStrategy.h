#pragma once
#include "Unit.h"
class InteractionStrategy {
public:
    virtual ~InteractionStrategy() = default;
    virtual void apply(Unit& unit) const = 0;
};
class AttackBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& u) const override { u.boostAttack(u.kind() == UnitKind::Gandalf || u.kind() == UnitKind::Saruman ? 15 : 5); }
};
class HealthRestoreStrategy : public InteractionStrategy {
public:
    void apply(Unit& u) const override { u.heal(30); }
};
class ManaBoostStrategy : public InteractionStrategy {
public:
    void apply(Unit& u) const override {
        if (u.kind() == UnitKind::Gandalf || u.kind() == UnitKind::Saruman) {
            u.boostAttack(20);
        }
        else u.heal(10);
    }
};
class DamageStrategy : public InteractionStrategy {
public:
    void apply(Unit& u) const override { u.takeDamage(u.isFlying() ? 5 : 25); }
};
class ResourceStrategy : public InteractionStrategy {
public:
    void apply(Unit& u) const override { u.heal(5); }
};
