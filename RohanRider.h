#pragma once
#include "Cavalry.h"

class RohanRider : public Cavalry {
public:
    UnitKind kind() const override { return UnitKind::RohanRider; }
	RohanRider(int x, int y);

	std::unique_ptr<Unit> clone() const override;
	std::string getType() const override;
	char symbol() const override;
};
