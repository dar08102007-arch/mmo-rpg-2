#pragma once
#include "Cavalry.h"

class WargRider : public Cavalry {
public:
    UnitKind kind() const override { return UnitKind::WargRider; }
	WargRider(int x, int y);

	std::unique_ptr<Unit> clone() const override;
	std::string getType() const override;
	char symbol() const override;
};
