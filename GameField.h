#pragma once

#include <memory>
#include <vector>
#include "Unit.h"
#include "UnitFactory.h"
#include "UnitKind.h"
#include "GameFieldIterator.h"

class GameField {
public:
    GameField(int width, int height, int maxUnits);
    GameField(const GameField& other);             
    GameField(GameField&& other) noexcept;          
    GameField& operator=(const GameField& other);   
    GameField& operator=(GameField&& other) noexcept; 
    ~GameField() {}                                  

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getMaxUnits() const { return maxUnits_; }
    int size() const { return unitCount_; }   

    bool inBounds(int x, int y) const;
    Unit* getUnit(int x, int y) const;

    bool addUnit(std::unique_ptr<Unit> unit, int x, int y);
    bool spawn(const UnitFactory& factory, UnitKind kind, int x, int y);

    bool removeUnit(int x, int y);
    bool removeUnitByIndex(int index);

    bool moveUnit(int fromX, int fromY, int toX, int toY);

    void print() const;

    GameFieldIterator begin() { return GameFieldIterator(&cells_, 0); }
    GameFieldIterator end() { return GameFieldIterator(&cells_, cells_.size()); }

private:
    int width_;
    int height_;
    int maxUnits_;
    int unitCount_;
    std::vector<std::unique_ptr<Unit>> cells_;
};
