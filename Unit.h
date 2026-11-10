#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Health.h"
#include "Armor.h"
#include "Attack.h"
#include "UnitTypeInfo.h"
#include "UnitEvent.h"
class Unit : public IObservable {
public:
    Unit(const Health& health, const Armor& armor, const Attack& attack, int x, int y);
    Unit(const Unit& other);
    virtual ~Unit() = default;
    virtual std::unique_ptr<Unit> clone() const = 0;
    virtual std::string getType() const = 0;
    virtual char symbol() const = 0;
    virtual UnitKind kind() const = 0;
    virtual bool isFlying() const { return false; }
    int id() const { return id_; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    const Health& getHealth() const { return health_; }
    const Armor& getArmor() const { return armor_; }
    const Attack& getAttack() const { return attack_; }
    const UnitTypeInfo& getInfo() const { return UnitTypeInfo::getInfo(kind()); }
    bool isAlive() const { return !health_.isZero(); }
    void heal(int amount);
    void boostAttack(int amount) { attack_ = Attack(attack_.getValue() + amount); }
    void boostArmor(int amount) { armor_ = Armor(armor_.getValue() + amount); }
    void subscribe(IObserver* observer) override;
    void unsubscribe(IObserver* observer) override;
    void notify(const UnitEvent& event) override;
    bool move(int newX, int newY, int fieldWidth, int fieldHeight);
    int attack(Unit& target);
    int takeDamage(int rawDamage);
    void setPosition(int x, int y);
private:
    Health health_;
    Armor armor_;
    Attack attack_;
    int x_, y_, id_;
    static int nextId_;
    std::vector<IObserver*> observers_;
};
