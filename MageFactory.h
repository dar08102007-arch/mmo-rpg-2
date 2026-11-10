#pragma once
#include "UnitFactory.h"
class MageFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(UnitKind kind, int x, int y) const override;
};
