#include "GameField.h"

#include <iostream>
#include <stdexcept>
#include <utility>

GameField::GameField(int width, int height, int maxUnits)
    : width_(width), height_(height), maxUnits_(maxUnits), unitCount_(0) {
    if (width <= 0 || height <= 0 || maxUnits <= 0) {
        throw std::invalid_argument("GameField: size and maxUnits must be positive");
    }
    cells_.resize(width * height);   
}

bool GameField::inBounds(int x, int y) const {
    return x >= 0 && y >= 0 && x < width_ && y < height_;
}

Unit* GameField::getUnit(int x, int y) const {
    if (!inBounds(x, y)) {
        return nullptr;
    }
    return cells_[y * width_ + x].get();
}

bool GameField::addUnit(std::unique_ptr<Unit> unit, int x, int y) {
    if (!unit) {
        return false;
    }
    if (!inBounds(x, y)) {
        return false;                       // ��� ����
    }
    if (cells_[y * width_ + x]) {
        return false;                       // ������ ������
    }
    if (unitCount_ >= maxUnits_) {
        return false;                       // ��������� ����� �� ������
    }
    unit->setPosition(x, y);
    cells_[y * width_ + x] = std::move(unit);
    ++unitCount_;
    return true;
}

bool GameField::spawn(const UnitFactory& factory, UnitKind kind, int x, int y) {
    if (!inBounds(x, y) || cells_[y * width_ + x] || unitCount_ >= maxUnits_) {
        return false;                      
    }
    return addUnit(factory.createUnit(kind, x, y), x, y);
}

bool GameField::removeUnit(int x, int y) {
    if (!inBounds(x, y)) {
        return false;
    }
    return removeUnitByIndex(y * width_ + x);
}

bool GameField::removeUnitByIndex(int index) {
    if (index < 0 || index >= static_cast<int>(cells_.size())) {
        return false;
    }
    if (!cells_[index]) {
        return false;                       
    }
    cells_[index].reset();                  
    --unitCount_;
    return true;
}

bool GameField::moveUnit(int fromX, int fromY, int toX, int toY) {
    Unit* unit = getUnit(fromX, fromY);
    if (unit == nullptr) {
        return false;
    }
    if (!inBounds(toX, toY) || cells_[toY * width_ + toX]) {
        return false;                       //��� ���� ��� ������
    }
    if (!unit->move(toX, toY, width_, height_)) {
        return false;
    }
    cells_[toY * width_ + toX] = std::move(cells_[fromY * width_ + fromX]);
    return true;
}

void GameField::print() const {
    
    for (int i = 0; i < width_ + 2; ++i) {
        std::cout << 'X';
    }
    std::cout << std::endl;

    for (int y = 0; y < height_; ++y) {
        std::cout << 'X';
        for (int x = 0; x < width_; ++x) {
            const std::unique_ptr<Unit>& cell = cells_[y * width_ + x];
            if (cell) {
                std::cout << cell->symbol();
            }
            else {
                std::cout << '.';
            }
        }
        std::cout << 'X' << std::endl;
    }

    for (int i = 0; i < width_ + 2; ++i) {
        std::cout << 'X';
    }
    std::cout << std::endl;
}

GameField::GameField(const GameField& other)
    : width_(other.width_), height_(other.height_),
    maxUnits_(other.maxUnits_), unitCount_(other.unitCount_) {
    cells_.resize(other.cells_.size());
    for (std::size_t i = 0; i < other.cells_.size(); ++i) {
        if (other.cells_[i]) {
            cells_[i] = other.cells_[i]->clone();
        }
    }
}


GameField::GameField(GameField&& other) noexcept
    : width_(other.width_), height_(other.height_),
    maxUnits_(other.maxUnits_), unitCount_(other.unitCount_),
    cells_(std::move(other.cells_)) {
    other.width_ = 0;
    other.height_ = 0;
    other.maxUnits_ = 0;
    other.unitCount_ = 0;
    other.cells_.clear();
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        GameField copy(other);       
        *this = std::move(copy);      
    }
    return *this;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        maxUnits_ = other.maxUnits_;
        unitCount_ = other.unitCount_;
        cells_ = std::move(other.cells_);   //������ ����� ��������� �����

        other.width_ = 0;
        other.height_ = 0;
        other.maxUnits_ = 0;
        other.unitCount_ = 0;
        other.cells_.clear();
    }
    return *this;
}
