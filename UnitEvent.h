#pragma once
#include <string>
enum class EventType { Created, Damaged, Destroyed };
struct UnitEvent {
    EventType type;
    int unitId;
    int damage;
    std::string unitName;
    int timestamp;
};
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onUnitEvent(const UnitEvent& event) = 0;
};
class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void subscribe(IObserver* observer) = 0;
    virtual void unsubscribe(IObserver* observer) = 0;
    virtual void notify(const UnitEvent& event) = 0;
};
