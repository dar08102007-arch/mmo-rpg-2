#include "Terrain.h"
#include "NeutralObject.h"
#include <stdexcept>
#include <iostream>
static bool flying(UnitKind t) { return UnitTypeInfo::getInfo(t).flying; }
static bool cavalry(UnitKind t) { return t == UnitKind::RohanRider || t == UnitKind::WargRider; }
static bool heavy(UnitKind t) { return t == UnitKind::UrukHai || cavalry(t); }
bool Forest::isPassable(UnitKind t) const { return flying(t) || !heavy(t); }
double Forest::getSpeedModifier(UnitKind t) const { return flying(t) ? 1.0 : 0.5; }
double Forest::getDefenseBonus(UnitKind t) const { return flying(t) ? 0 : 3; }
double Swamp::getSpeedModifier(UnitKind t) const { return flying(t) ? 1.0 : 0.5; }
bool Mountains::isPassable(UnitKind t) const { return flying(t); }
bool TerrainProxy::isPassable(UnitKind t) const {
    if (flying(t)) { std::cout << "[Proxy] Летающий юнит проходит препятствие\n"; return true; }
    bool allowed = real_->isPassable(t);
    std::cout << "[Proxy] Проверка прохода: " << (allowed ? "разрешено" : "запрещено") << "\n";
    return allowed;
}
double TerrainProxy::getSpeedModifier(UnitKind t) const {
    double speed = flying(t) ? 1.0 : real_->getSpeedModifier(t);
    std::cout << "[Proxy] Скорость x" << speed << "\n";
    return speed;
}
double TerrainProxy::getDefenseBonus(UnitKind t) const {
    double bonus = flying(t) ? 0 : real_->getDefenseBonus(t);
    std::cout << "[Proxy] Бонус защиты " << bonus << "\n";
    return bonus;
}
TerrainMap::TerrainMap(int w, int h) : width_(w), height_(h) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Invalid map size");
    }
    cells_.resize(h); objects_.resize(h);
    for (int y=0; y<h; ++y) {
        cells_[y].resize(w); objects_[y].resize(w);
        for (int x=0; x<w; ++x) {
            cells_[y][x] = std::make_unique<Plains>();
        }
    }
}
bool TerrainMap::inBounds(int x,int y) const { return x>=0 && y>=0 && x<width_ && y<height_; }
void TerrainMap::setTerrain(int x,int y,std::unique_ptr<Terrain> t) {
    if (!inBounds(x,y) || !t) {
        throw std::out_of_range("Invalid terrain");
    }
    cells_[y][x] = std::move(t);
}
const Terrain& TerrainMap::getTerrain(int x,int y) const {
    if (!inBounds(x,y)) {
        throw std::out_of_range("Terrain out of bounds");
    }
    return *cells_[y][x];
}
void TerrainMap::setNeutralObject(int x,int y,std::shared_ptr<NeutralObject> o) {
    if (!inBounds(x,y)) {
        throw std::out_of_range("Object out of bounds");
    }
    objects_[y][x] = std::move(o);
}
NeutralObject* TerrainMap::getNeutralObject(int x,int y) const {
    if (!inBounds(x,y)) {
        return nullptr;
    }
    return objects_[y][x].get();
}
