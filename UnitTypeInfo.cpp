#include "UnitTypeInfo.h"
#include <stdexcept>
const UnitTypeInfo& UnitTypeInfo::getInfo(UnitKind kind) {
    static const std::unordered_map<UnitKind, std::shared_ptr<const UnitTypeInfo>> data = {
        {UnitKind::GondorSoldier, std::make_shared<const UnitTypeInfo>("GondorSoldier",100,15,2,20,5,UnitKind::GondorSoldier,false)},
        {UnitKind::UrukHai, std::make_shared<const UnitTypeInfo>("UrukHai",120,19,2,25,5,UnitKind::UrukHai,false)},
        {UnitKind::ElfArcher, std::make_shared<const UnitTypeInfo>("ElfArcher",75,22,3,20,2,UnitKind::ElfArcher,false)},
        {UnitKind::OrcArcher, std::make_shared<const UnitTypeInfo>("OrcArcher",70,18,2,20,2,UnitKind::OrcArcher,false)},
        {UnitKind::RohanRider, std::make_shared<const UnitTypeInfo>("RohanRider",100,23,4,30,4,UnitKind::RohanRider,false)},
        {UnitKind::WargRider, std::make_shared<const UnitTypeInfo>("WargRider",105,24,4,30,3,UnitKind::WargRider,false)},
        {UnitKind::Gandalf, std::make_shared<const UnitTypeInfo>("Gandalf",110,35,2,40,5,UnitKind::Gandalf,false)},
        {UnitKind::Saruman, std::make_shared<const UnitTypeInfo>("Saruman",100,34,2,40,5,UnitKind::Saruman,false)},
        {UnitKind::GreatEagle, std::make_shared<const UnitTypeInfo>("GreatEagle",95,25,5,35,3,UnitKind::GreatEagle,true)},
        {UnitKind::FellBeast, std::make_shared<const UnitTypeInfo>("FellBeast",100,27,5,35,3,UnitKind::FellBeast,true)}
    };
    auto it = data.find(kind);
    if (it == data.end()) {
        throw std::invalid_argument("Unknown unit kind");
    }
    return *it->second;
}
