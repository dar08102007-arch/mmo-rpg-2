#include "MageFactory.h"
#include <stdexcept>
#include "Gandalf.h"
#include "Saruman.h"
std::unique_ptr<Unit> MageFactory::createUnit(UnitKind kind, int x, int y) const {
    if (kind == UnitKind::Gandalf) {
        return std::make_unique<Gandalf>(x, y);
    }
    if (kind == UnitKind::Saruman) {
        return std::make_unique<Saruman>(x, y);
    }
    throw std::invalid_argument("Wrong unit kind");
}
