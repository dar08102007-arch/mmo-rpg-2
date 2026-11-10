#pragma once
#include "Base.h"
#include "Terrain.h"
#include "NeutralObject.h"
class GameController {
public:
    GameController();
    ~GameController();
    bool create(UnitKind kind, int x, int y);
    bool move(int x, int y, int nx, int ny);
    bool interact(int x, int y);
    bool fight(int x, int y, int tx, int ty);
    void print() const;
    void runDemos();
    const GameField& field() const { return field_; }
    const Base& base() const { return base_; }
private:
    GameField field_;
    TerrainMap terrain_;
    Base base_;
};
