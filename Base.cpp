#include "Base.h"
#include <algorithm>
#include <iostream>
#include <ctime>

Base::Base(std::string name, int x, int y, int hp, int limit, int defense, int resources)
    : name_(name), x_(x), y_(y), health_(hp), maxUnits_(limit), defense_(defense), resources_(resources) {}

bool Base::createUnit(GameField& field, const UnitFactory& factory, UnitKind kind, int x, int y) {
    int cost = UnitTypeInfo::getInfo(kind).cost;

    if (health_ <= 0 || count() >= maxUnits_ || resources_ < cost || !field.inBounds(x,y) || field.getUnit(x,y)) {
        return false;
    }

    if (!field.spawn(factory, kind, x, y)) {
        return false;
    }

    Unit* unit = field.getUnit(x,y);
    unit->subscribe(this);
    unitIds_.push_back(unit->id());
    resources_ -= cost;

    unit->notify({EventType::Created, unit->id(), 0, unit->getType(), static_cast<int>(std::time(nullptr))});
    return true;
}

bool Base::removeUnit(GameField& field, int unitId) {
    for (Unit& unit : field) if (unit.id() == unitId) {
        unit.unsubscribe(this);
        unitIds_.erase(std::remove(unitIds_.begin(), unitIds_.end(), unitId), unitIds_.end());
        return field.removeUnit(unit.getX(), unit.getY());
    }
    return false;
}
void Base::onUnitEvent(const UnitEvent& e) {
    std::cout << "[База " << name_ << "] " << e.unitName << " #" << e.unitId << ": ";
    if (e.type == EventType::Created) {
        std::cout << "создан";
    }
    if (e.type == EventType::Damaged) {
        std::cout << "получил урон " << e.damage;
    }
    if (e.type == EventType::Destroyed) {
        std::cout << "уничтожен";
        unitIds_.erase(std::remove(unitIds_.begin(), unitIds_.end(), e.unitId), unitIds_.end());
    }
    std::cout << "\n";
}
void Base::takeDamage(int damage) {
    if (damage > defense_) {
        health_ = std::max(0, health_ - (damage - defense_));
    }
    if (health_ == 0) {
        std::cout << "База " << name_ << " разрушена!\n";
    }
}
void Base::releaseObservers(GameField& field) { for (Unit& unit : field) unit.unsubscribe(this); }
