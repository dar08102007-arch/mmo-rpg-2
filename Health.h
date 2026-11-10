#pragma once
class Health {
public:
	Health(int value);
	int getValue() const;
	void decrease(int amount);
	void increase(int amount);
	bool isZero() const;

private:
	int value_;
};
