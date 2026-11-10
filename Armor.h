#pragma once
class Armor {
public:
	Armor(int value);
	int getValue() const;
	int reduceDamage(int damage) const;

private:
	int value_;
};
