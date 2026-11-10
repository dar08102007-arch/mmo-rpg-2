#pragma once
#include <memory>
#include <string>
#include "InteractionStrategy.h"
class NeutralObject {
public:
    explicit NeutralObject(std::shared_ptr<InteractionStrategy> strategy) : strategy_(std::move(strategy)) {}
    virtual ~NeutralObject() = default;
    virtual std::string name() const = 0;
    virtual char symbol() const = 0;
    virtual void interact(Unit& unit) const { strategy_->apply(unit); }
protected:
    std::shared_ptr<InteractionStrategy> strategy_;
};
class TreasureChest : public NeutralObject {
public:
    TreasureChest() : NeutralObject(std::make_shared<ResourceStrategy>()) {}
    std::string name() const override { return "Сундук"; }
    char symbol() const override { return '$'; }
};
class Trap : public NeutralObject {
public:
    Trap() : NeutralObject(std::make_shared<DamageStrategy>()) {}
    std::string name() const override { return "Ловушка"; }
    char symbol() const override { return '!'; }
};
class Altar : public NeutralObject {
public:
    Altar() : NeutralObject(std::make_shared<AttackBoostStrategy>()) {}
    std::string name() const override { return "Алтарь"; }
    char symbol() const override { return 'A'; }
    void chooseStrategy(UnitKind kind);
};
class EnergySource : public NeutralObject {
public:
    EnergySource() : NeutralObject(std::make_shared<HealthRestoreStrategy>()) {}
    std::string name() const override { return "Источник энергии"; }
    char symbol() const override { return '+'; }
};

Unit& operator+(Unit& unit, const TreasureChest& chest);
Unit& operator-(Unit& unit, const Trap& trap);
Unit& operator*(Unit& unit, const Altar& altar);
Unit& operator/(Unit& unit, const EnergySource& source);
