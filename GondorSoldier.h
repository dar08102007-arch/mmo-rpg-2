#pragma once
#include "Infantry.h"

class GondorSoldier : public Infantry {
public:
    UnitKind kind() const override { return UnitKind::GondorSoldier; }
	GondorSoldier(int x, int y);

	std::unique_ptr<Unit> clone() const override;
	std::string getType() const override;
	char symbol() const override;
};
