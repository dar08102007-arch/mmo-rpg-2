#include "ArcherFactory.h"

#include <stdexcept>
#include "ElfArcher.h"
#include "OrcArcher.h"

std::unique_ptr<Unit> ArcherFactory::createUnit(UnitKind kind, int x, int y) const {
    if (kind == UnitKind::ElfArcher) {
        return std::make_unique<ElfArcher>(x, y);
    }
    if (kind == UnitKind::OrcArcher) {
        return std::make_unique<OrcArcher>(x, y);
    }
    throw std::invalid_argument("ArcherFactory cannot create this unit");
}
