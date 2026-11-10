#pragma once

#include <memory>
#include "Unit.h"
#include "UnitKind.h"

class UnitFactory {
public:
	virtual ~UnitFactory() {}
	virtual std::unique_ptr<Unit> createUnit(UnitKind kind, int x, int y) const = 0;
};
