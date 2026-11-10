#include "Unit.h"
#include <algorithm>
#include <ctime>
int Unit::nextId_ = 1;
Unit::Unit(const Health& h, const Armor& a, const Attack& at, int x, int y)
    : health_(h), armor_(a), attack_(at), x_(x), y_(y), id_(nextId_++) {}
Unit::Unit(const Unit& other)
    : health_(other.health_), armor_(other.armor_), attack_(other.attack_),
      x_(other.x_), y_(other.y_), id_(nextId_++) {}
void Unit::subscribe(IObserver* observer) {
    if (observer && std::find(observers_.begin(), observers_.end(), observer) == observers_.end()) {
        observers_.push_back(observer);
    }
}
void Unit::unsubscribe(IObserver* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}
void Unit::notify(const UnitEvent& event) { for (IObserver* o : observers_) o->onUnitEvent(event); }
void Unit::heal(int amount) { if (amount > 0) health_.increase(std::min(amount, getInfo().maxHealth - health_.getValue())); }
bool Unit::move(int x, int y, int width, int height) {
    if (x < 0 || y < 0 || x >= width || y >= height || !isAlive()) {
        return false;
    }
    x_ = x; y_ = y; return true;
}
int Unit::attack(Unit& target) { return target.takeDamage(attack_.getValue()); }
int Unit::takeDamage(int damage) {
    if (!isAlive()) {
        return 0;
    }
    int real = armor_.reduceDamage(damage);
    health_.decrease(real);
    notify({isAlive() ? EventType::Damaged : EventType::Destroyed, id_, real, getType(), static_cast<int>(std::time(nullptr))});
    return real;
}
void Unit::setPosition(int x, int y) { x_ = x; y_ = y; }
