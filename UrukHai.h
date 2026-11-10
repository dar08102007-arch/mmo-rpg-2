#pragma once
#include "Infantry.h"

class UrukHai : public Infantry {
public:
    UnitKind kind() const override { return UnitKind::UrukHai; }
	UrukHai(int x, int y);

	std::unique_ptr<Unit> clone() const override;
	std::string getType() const override;
	char symbol() const override;
};
