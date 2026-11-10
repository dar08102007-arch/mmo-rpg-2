#include "FlyingFactory.h"
#include <stdexcept>
#include "GreatEagle.h"
#include "FellBeast.h"
std::unique_ptr<Unit> FlyingFactory::createUnit(UnitKind kind, int x, int y) const {
    if (kind == UnitKind::GreatEagle) {
        return std::make_unique<GreatEagle>(x, y);
    }

    if (kind == UnitKind::FellBeast) {
        return std::make_unique<FellBeast>(x, y);
    }

    throw std::invalid_argument("Wrong unit kind");
}
