#pragma once
#include <string>
#include <vector>
#include "GameField.h"
#include "UnitEvent.h"
class Base : public IObserver {
public:
    Base(std::string name, int x, int y, int health, int maxUnits, int defense, int resources);
    bool createUnit(GameField& field, const UnitFactory& factory, UnitKind kind, int x, int y);
    bool removeUnit(GameField& field, int unitId);
    void onUnitEvent(const UnitEvent& event) override;
    void releaseObservers(GameField& field);
    int count() const { return static_cast<int>(unitIds_.size()); }
    int resources() const { return resources_; }
    int health() const { return health_; }
    int defense() const { return defense_; }
    int x() const { return x_; }
    int y() const { return y_; }
    const std::string& name() const { return name_; }
    void addResources(int amount) { if (amount > 0) resources_ += amount; }
    void takeDamage(int damage);
private:
    std::string name_;
    int x_, y_, health_, maxUnits_, defense_, resources_;
    std::vector<int> unitIds_;
};
