#pragma once
#include <vector>
#include <memory>
#include "Unit.h"
class Terrain {
public:
    virtual ~Terrain() = default;
    virtual bool isPassable(UnitKind type) const = 0;
    virtual double getSpeedModifier(UnitKind type) const = 0;
    virtual double getDefenseBonus(UnitKind type) const = 0;
    virtual char symbol() const = 0;
};
class Plains : public Terrain {
public:
    bool isPassable(UnitKind) const override { return true; }
    double getSpeedModifier(UnitKind) const override { return 1.0; }
    double getDefenseBonus(UnitKind) const override { return 0; }
    char symbol() const override { return '.'; }
};
class Forest : public Terrain {
public:
    bool isPassable(UnitKind type) const override;
    double getSpeedModifier(UnitKind type) const override;
    double getDefenseBonus(UnitKind type) const override;
    char symbol() const override { return '*'; }
};
class Swamp : public Terrain {
public:
    bool isPassable(UnitKind) const override { return true; }
    double getSpeedModifier(UnitKind type) const override;
    double getDefenseBonus(UnitKind) const override { return 0; }
    char symbol() const override { return '~'; }
};
class Mountains : public Terrain {
public:
    bool isPassable(UnitKind type) const override;
    double getSpeedModifier(UnitKind) const override { return 0.5; }
    double getDefenseBonus(UnitKind) const override { return 3; }
    char symbol() const override { return '^'; }
};
class TerrainProxy : public Terrain {
public:
    explicit TerrainProxy(const Terrain* real) : real_(real) {}
    bool isPassable(UnitKind type) const override;
    double getSpeedModifier(UnitKind type) const override;
    double getDefenseBonus(UnitKind type) const override;
    char symbol() const override { return real_->symbol(); }
private:
    const Terrain* real_;
};
class NeutralObject;
class TerrainMap {
public:
    TerrainMap(int width, int height);
    void setTerrain(int x, int y, std::unique_ptr<Terrain> terrain);
    const Terrain& getTerrain(int x, int y) const;
    void setNeutralObject(int x, int y, std::shared_ptr<NeutralObject> object);
    NeutralObject* getNeutralObject(int x, int y) const;
    bool inBounds(int x, int y) const;
    int width() const { return width_; }
    int height() const { return height_; }
private:
    int width_, height_;
    std::vector<std::vector<std::unique_ptr<Terrain>>> cells_;
    std::vector<std::vector<std::shared_ptr<NeutralObject>>> objects_;
};
