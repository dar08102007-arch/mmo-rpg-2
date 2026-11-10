#include "CavalryFactory.h"

#include <stdexcept>
#include "RohanRider.h"
#include "WargRider.h"

std::unique_ptr<Unit> CavalryFactory::createUnit(UnitKind kind, int x, int y) const {

    if (kind == UnitKind::RohanRider) {
        return std::make_unique<RohanRider>(x, y);
    }

    if (kind == UnitKind::WargRider) {
        return std::make_unique<WargRider>(x, y);
    }
    throw std::invalid_argument("CavalryFactory cannot create this unit");
}
