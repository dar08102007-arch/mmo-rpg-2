#pragma once
#include "Archer.h"

class OrcArcher : public Archer {
public:
    UnitKind kind() const override { return UnitKind::OrcArcher; }
	OrcArcher(int x, int y);

	std::unique_ptr<Unit> clone() const override;
	std::string getType() const override;
	char symbol() const override;
};
