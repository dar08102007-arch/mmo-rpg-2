#pragma once

#include <memory>
#include <stdexcept>
#include <vector>
#include "Unit.h"

class GameFieldIterator {
public:
    GameFieldIterator(std::vector<std::unique_ptr<Unit>>* cells, std::size_t index)
        : cells_(cells), index_(index) {
        skipEmpty();
    }


    Unit& operator*() const { return *(*cells_)[index_]; }
    Unit* operator->() const { return (*cells_)[index_].get(); }

    GameFieldIterator& operator++() {
        ++index_;
        skipEmpty();
        return *this;
    }

    bool operator==(const GameFieldIterator& other) const {
        return cells_ == other.cells_ && index_ == other.index_;
    }
    bool operator!=(const GameFieldIterator& other) const {
        return !(*this == other);
    }

    
    bool hasNext() const {
        for (std::size_t i = index_; i < cells_->size(); ++i) {
            if ((*cells_)[i]) {
                return true;
            }
        }
        return false;
    }

    Unit& next() {
        skipEmpty();
        if (index_ >= cells_->size()) {
            throw std::out_of_range("GameFieldIterator::next: no more units");
        }
        Unit& unit = *(*cells_)[index_];
        ++index_;
        skipEmpty();
        return unit;
    }

    
    std::size_t cellIndex() const { return index_; }

private:
  
    void skipEmpty() {
        while (index_ < cells_->size() && !(*cells_)[index_]) {
            ++index_;
        }
    }

    std::vector<std::unique_ptr<Unit>>* cells_;
    std::size_t index_;
};
