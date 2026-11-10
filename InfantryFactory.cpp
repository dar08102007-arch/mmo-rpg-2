#include "InfantryFactory.h"

#include <stdexcept>
#include "GondorSoldier.h"
#include "UrukHai.h"

std::unique_ptr<Unit> InfantryFactory::createUnit(UnitKind kind, int x, int y) const {

    if (kind == UnitKind::GondorSoldier) {
        return std::make_unique<GondorSoldier>(x, y);
    }

    if (kind == UnitKind::UrukHai) {
        return std::make_unique<UrukHai>(x, y);
    }

    throw std::invalid_argument("InfantryFactory cannot create this unit");
}
