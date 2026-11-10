#include "NeutralObject.h"
void Altar::chooseStrategy(UnitKind kind) {
    if (kind == UnitKind::Gandalf || kind == UnitKind::Saruman)

        strategy_ = std::make_shared<ManaBoostStrategy>();

    else strategy_ = std::make_shared<AttackBoostStrategy>();
}
Unit& operator+(Unit& u,const TreasureChest& chest) { chest.interact(u); return u; }

Unit& operator-(Unit& u,const Trap& trap) { trap.interact(u); return u; }

Unit& operator*(Unit& u,const Altar& altar) { altar.interact(u); return u; }

Unit& operator/(Unit& u,const EnergySource& source) { source.interact(u); return u; }
