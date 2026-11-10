#include "GameController.h"
#include "InfantryFactory.h"
#include "ArcherFactory.h"
#include "CavalryFactory.h"
#include "MageFactory.h"
#include "FlyingFactory.h"
#include <iostream>
#include <cmath>
#include <utility>

GameController::GameController()
    : field_(12,8,20), terrain_(12,8),
      base_("Минас-Тирит",0,0,500,12,5,500) {
    terrain_.setTerrain(3,2,std::make_unique<Forest>());
    terrain_.setTerrain(4,2,std::make_unique<Forest>());
    terrain_.setTerrain(5,2,std::make_unique<Swamp>());
    terrain_.setTerrain(7,2,std::make_unique<Mountains>());
    terrain_.setTerrain(8,2,std::make_unique<Mountains>());
    terrain_.setTerrain(3,4,std::make_unique<Swamp>());
    terrain_.setNeutralObject(4,3,std::make_shared<TreasureChest>());
    terrain_.setNeutralObject(5,4,std::make_shared<Trap>());
    terrain_.setNeutralObject(2,3,std::make_shared<Altar>());
    terrain_.setNeutralObject(8,5,std::make_shared<EnergySource>());
}
GameController::~GameController() { base_.releaseObservers(field_); }
bool GameController::create(UnitKind kind, int x, int y) {
    InfantryFactory infantry;
    ArcherFactory archer;
    CavalryFactory cavalry;
    MageFactory mage;
    FlyingFactory flying;
    const UnitFactory* factory = nullptr;

    switch(kind) {
    case UnitKind::GondorSoldier: case UnitKind::UrukHai: factory=&infantry; break;
    case UnitKind::ElfArcher: case UnitKind::OrcArcher: factory=&archer; break;
    case UnitKind::RohanRider: case UnitKind::WargRider: factory=&cavalry; break;
    case UnitKind::Gandalf: case UnitKind::Saruman: factory=&mage; break;
    case UnitKind::GreatEagle: case UnitKind::FellBeast: factory=&flying; break;
    }

    if (!factory || !terrain_.inBounds(x,y)) {
        return false;
    }

    if (x==base_.x() && y==base_.y()) {
        return false;
    }

    TerrainProxy proxy(&terrain_.getTerrain(x,y));
    if (!proxy.isPassable(kind)) {
        return false;
    }

    return base_.createUnit(field_,*factory,kind,x,y);
}
bool GameController::move(int x,int y,int nx,int ny) {
    Unit* u = field_.getUnit(x, y);
    if (!u || !u->isAlive() || !terrain_.inBounds(nx,ny)) {
        return false;
    }

    if (nx==base_.x() && ny==base_.y()) {
        return false;
    }

    if (std::abs(nx-x)+std::abs(ny-y) != 1) {
        return false;
    }

    TerrainProxy proxy(&terrain_.getTerrain(nx,ny));
    if (!proxy.isPassable(u->kind())) {
        return false;
    }

    double speed = proxy.getSpeedModifier(u->kind());
    double defense = proxy.getDefenseBonus(u->kind());
    if (!field_.moveUnit(x,y,nx,ny)) {
        return false;
    }

    if (defense>0) {
        u->boostArmor(static_cast<int>(defense));
    }
    std::cout << u->getType() << " переместился в (" << nx << "," << ny << "), скорость x" << speed << "\n";
    return true;
}
bool GameController::interact(int x,int y) {
    Unit* u = field_.getUnit(x, y);
    NeutralObject* obj = terrain_.getNeutralObject(x, y);

    if (!u || !obj || !u->isAlive()) {
        return false;
    }

    std::cout << u->getType() << " взаимодействует: " << obj->name() << "\n";
    if (auto chest=dynamic_cast<TreasureChest*>(obj)) {
        *u + *chest;
        base_.addResources(30);

    } else if (auto trap=dynamic_cast<Trap*>(obj)) *u - *trap;
    else if (auto altar=dynamic_cast<Altar*>(obj)) { altar->chooseStrategy(u->kind()); *u * *altar; }
    else if (auto source=dynamic_cast<EnergySource*>(obj)) {
        *u / *source;
    }
    return true;
}
bool GameController::fight(int x,int y,int tx,int ty) {
    Unit* a = field_.getUnit(x, y);
    Unit* b = field_.getUnit(tx, ty);
    if (!a || !b || !a->isAlive() || !b->isAlive() || a==b) {
        return false;
    }
    if (std::abs(x-tx)+std::abs(y-ty)>1) {
        return false;
    }
    int damage=a->attack(*b);
    std::cout << a->getType() << " атакует " << b->getType() << ": урон " << damage << "\n";
    if (!b->isAlive()) {
        field_.removeUnit(tx,ty);
    }
    return true;
}
void GameController::print() const {
    std::cout << "\n   "; for(int x=0;x<terrain_.width();++x) std::cout << x%10 << ' '; std::cout << '\n';
    for(int y=0;y<terrain_.height();++y) {
        std::cout << y << "  ";
        for(int x=0;x<terrain_.width();++x) {
            char ch=terrain_.getTerrain(x,y).symbol();
            if (auto obj=terrain_.getNeutralObject(x,y)) {
                ch=obj->symbol();
            }
            if (auto unit=field_.getUnit(x,y)) {
                ch=unit->symbol();
            }
            if (x==base_.x() && y==base_.y()) {
                ch='B';
            }
            std::cout << ch << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Легенда: B база, . равнина, * лес, ~ болото, ^ горы, $ сундук, ! ловушка, A алтарь, + источник\n";
    std::cout << "База " << base_.name() << ": " << base_.count() << " юнитов, " << base_.resources() << " ресурсов\n";
}
void GameController::runDemos() {
    std::cout << "\n СЦЕНАРИЙ 1: БАЗА И СОЗДАНИЕ ЮНИТОВ ЧЕРЕЗ ФАБРИКИ \n";
    create(UnitKind::GondorSoldier,1,1);
    create(UnitKind::UrukHai,10,6);
    create(UnitKind::ElfArcher,2,2);
    create(UnitKind::OrcArcher,9,6);
    create(UnitKind::RohanRider,6,2);
    create(UnitKind::WargRider,9,5);
    create(UnitKind::Gandalf,1,3);
    create(UnitKind::Saruman,10,5);
    create(UnitKind::GreatEagle,7,1);
    create(UnitKind::FellBeast,10,4);
    print();

    std::cout << "\n СЦЕНАРИЙ 2: ПЕРЕМЕЩЕНИЕ И ПРОКСИ ЛАНДШАФТА \n";
    std::cout << "Всадник в горах: " << (move(6,2,7,2)?"прошёл":"проход закрыт") << '\n';
    std::cout << "Орёл в горах: " << (move(7,1,7,2)?"прошёл":"проход закрыт") << '\n';
    move(2,2,3,2);
    print();

    std::cout << "\n СЦЕНАРИЙ 3: ОБЪЕКТЫ, СТРАТЕГИЯ И ОПЕРАТОРЫ \n";
    move(1,3,2,3); interact(2,3); // Алтарь: operator*
    move(3,2,3,3); move(3,3,4,3); interact(4,3); // Сундук: operator+
    create(UnitKind::OrcArcher,5,3); move(5,3,5,4); interact(5,4); // Ловушка: operator-
    create(UnitKind::Gandalf,8,4); move(8,4,8,5); interact(8,5); // Источник: operator/
    print();

    std::cout << "\n СЦЕНАРИЙ 4: НАБЛЮДАТЕЛЬ, ГИБЕЛЬ И КОПИРОВАНИЕ \n";
    Unit* soldier=field_.getUnit(1,1);
    if (soldier) {
        soldier->takeDamage(500);
        field_.removeUnit(1, 1);
    }
    std::cout << "Юнитов на базе после гибели: " << base_.count() << '\n';
    GameField copy=field_;
    GameField moved=std::move(copy);
    std::cout << "Юнитов в перемещённой копии: " << moved.size() << '\n';
    std::cout << "Обход итератором:\n";
    for (Unit& u : moved) {
        std::cout << "  " << u.getType() << " #" << u.id() << " (" << u.getX() << ',' << u.getY() << ")\n";
    }
    print();
}
