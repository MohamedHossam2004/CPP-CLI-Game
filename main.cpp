#include <iostream>
#include "GameEngine/Game.h"
#include "Characters/Heroes/DemolitionHero.h"
#include "Characters/Heroes/Hero.h"
#include "Characters/Heroes/MedicHero.h"
#include "Object.h"
#include "Point.h"
#include "Characters/Monsters/Monster.h"
#include "Characters/Monsters/TankMonster.h"
#include "Characters/Monsters/GhostMonster.h"
#include "Characters/Character.h"
#include "Items/Ammo.h"
#include "Items/Potion.h"
#include "Weapons/Bazooka.h"
#include "Weapons/Pistol.h"
#include "Weapons/Rifle.h"
#include <cstdlib>
using namespace std;

// Object class
Object ::Object()
{
    type = '.';
}
Object::Object(char t) : type(t) {}

char Object ::getType() const
{
    return type;
}
Object ::~Object() {}

ostream &operator<<(ostream &os, Object &obj)
{
    os << "Type: ";
    os << obj.getType() << endl;
    return os;
}

Gun::Gun(string n, int b, int d, int r) : name(n), bullets(b), damage(d), range(r) {}

string Gun ::getName()
{
    return name;
}

int Gun ::getBullets()
{
    return bullets;
}

void Gun::setBullets(int bullets)
{
    this->bullets = bullets;
}

int Gun ::getDamage()
{
    return damage;
}

int Gun ::getRange()
{
    return range;
}

Gun::~Gun() {}

ostream &operator<<(ostream &os, const Gun &gun)
{
    os << "Gun Name: " << gun.name << endl;
    os << "Number of Bullets: " << gun.bullets << endl;
    os << "Damage: " << gun.damage << endl;
    os << "Range: " << gun.range << endl;
    return os;
}

void Gun::useSpecial(Hero &h1, Object ***map)
{
    int x = h1.getPositionX();
    int y = h1.getPositionY();
    if (name == "Pistol")
    {
        if (getBullets() >= 4)
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (j != i && j != -i)
                    {
                        if (x + i < 15 && y + j < 15 && x + i >= 0 && y + j >= 0 &&
                            map[x + i][y + j]->getType() == 'G')
                        {
                            GhostMonster &g = dynamic_cast<GhostMonster &>(*map[x + i][y + j]);
                            g.setHealthPoints(g.getHealthPoints() - getDamage());
                            break;
                        }
                        else if (x + i < 15 && y + j < 15 && x + i >= 0 && y + j >= 0 &&
                                 map[x + i][y + j]->getType() == 'T')
                        {
                            TankMonster &t = dynamic_cast<TankMonster &>(*map[x + i][y + j]);
                            int dmg = getDamage() - t.getShield();
                            t.setShield(dmg >= 0 ? 0 : t.getShield() - getDamage());
                            if (dmg > 0)
                            {
                                t.setHealthPoints(t.getHealthPoints() - dmg);
                            }
                            break;
                        }
                    }
                }
            }
            setBullets(getBullets() - 4);
        }
    }
    else if (name == "Rifle")
    {
        if (getBullets() >= 3)
        {
            for (int i = 1; i < getRange() && y + i < 15; i++)
            {
                if (map[x][y + i]->getType() == 'G')
                {
                    GhostMonster &g = dynamic_cast<GhostMonster &>(*map[x][y + i]);
                    g.setHealthPoints(g.getHealthPoints() - getDamage());
                }
                else if (map[x][y + i]->getType() == 'T')
                {
                    TankMonster &t = dynamic_cast<TankMonster &>(*map[x][y + i]);
                    int dmg = getDamage() - t.getShield();
                    t.setShield(dmg >= 0 ? 0 : t.getShield() - getDamage());
                    if (dmg > 0)
                    {
                        t.setHealthPoints(t.getHealthPoints() - dmg);
                    }
                }
            }
            for (int i = 1; i < getRange() && y - i >= 0; i++)
            {
                if (map[x][y - i]->getType() == 'G')
                {
                    GhostMonster &g = dynamic_cast<GhostMonster &>(*map[x][y - i]);
                    g.setHealthPoints(g.getHealthPoints() - getDamage());
                }
                else if (map[x][y - i]->getType() == 'T')
                {
                    TankMonster &t = dynamic_cast<TankMonster &>(*map[x][y - i]);
                    int dmg = getDamage() - t.getShield();
                    t.setShield(dmg >= 0 ? 0 : t.getShield() - getDamage());
                    if (dmg > 0)
                    {
                        t.setHealthPoints(t.getHealthPoints() - dmg);
                    }
                }
            }
            for (int j = 1; j < getRange() && x + j < 15; j++)
            {
                if (map[x + j][y]->getType() == 'G')
                {
                    GhostMonster &g = dynamic_cast<GhostMonster &>(*map[x + j][y]);
                    g.setHealthPoints(g.getHealthPoints() - getDamage());
                }
                else if (map[x + j][y]->getType() == 'T')
                {
                    TankMonster &t = dynamic_cast<TankMonster &>(*map[x + j][y]);
                    int dmg = getDamage() - t.getShield();
                    t.setShield(dmg >= 0 ? 0 : t.getShield() - getDamage());
                    if (dmg > 0)
                    {
                        t.setHealthPoints(t.getHealthPoints() - dmg);
                    }
                }
            }
            setBullets(getBullets() - 3);
        }
    }
    else if (name == "Bazooka")
    {
        if (x == y)
        {
            for (int i = 0; i < 15; i++)
            {
                if (map[i][i]->getType() == 'G')
                {
                    GhostMonster &g = dynamic_cast<GhostMonster &>(*map[i][i]);
                    g.setHealthPoints(0);
                }
                else if (map[i][i]->getType() == 'T')
                {
                    TankMonster &t = dynamic_cast<TankMonster &>(*map[i][i]);
                    t.setHealthPoints(0);
                }
            }
        }
        else if (x == 14 - y)
        {
            for (int i = 0; i < 14; i++)
            {
                if (map[i][14 - i]->getType() == 'G')
                {
                    GhostMonster &g = dynamic_cast<GhostMonster &>(*map[i][14 - i]);
                    g.setHealthPoints(0);
                }
                else if (map[i][14 - i]->getType() == 'T')
                {
                    TankMonster &t = dynamic_cast<TankMonster &>(*map[i][14 - i]);
                    t.setHealthPoints(0);
                }
            }
        }
    }
}

Character ::Character(char t, int x, int y, int hp) : Object(t), positionX(x), positionY(y), healthPoints(hp) {}

int Character::getPositionX()
{
    return positionX;
}

int Character::getPositionY()
{
    return positionY;
}

int Character::getHealthPoints()
{
    return healthPoints;
}

void Character::setPosition(int x, int y)
{
    positionX = x;
    positionY = y;
}

void Character::setHealthPoints(int hp)
{
    healthPoints = hp;
}

// Hero class

Hero::Hero(char t, int x, int y, int hp) : Character(t, x, y, hp) {}

Gun *Hero::getWeapon()
{
    return weapon;
}

void Hero::setWeapon(Gun *g)
{
    weapon = g;
}

Hero::~Hero()
{
    delete weapon;
}

ostream &operator<<(ostream &os, Hero &hero)
{
    os << "Hero Type: ";
    os << ((hero.getType() == 'D') ? "Demolition" : "Medic") << endl;
    os << "Hero Health: ";
    os << hero.getHealthPoints() << endl;
    os << "X Position: ";
    os << hero.getPositionX() << endl;
    os << "Y Position: ";
    os << hero.getPositionY() << endl;
    os << "Weapon: " << endl;
    os << *hero.getWeapon() << endl;
    if (hero.getType() == 'D')
    {
        os << "Weapon 2: " << endl;
        DemolitionHero &d = dynamic_cast<DemolitionHero &>(hero);
        os << *d.getWeapon2();
    }
    return os;
}

void operator+(Hero &hero, Ammo &ammo)
{
    hero.getWeapon()->setBullets(hero.getWeapon()->getBullets() + ammo.getBullets());
    if (hero.getType() == 'D')
    {
        DemolitionHero &d = dynamic_cast<DemolitionHero &>(hero);
        d.getWeapon2()->setBullets(d.getWeapon2()->getBullets() + ammo.getBullets());
    }
}
void operator+(Hero &hero, Potion &potion)
{
    hero.setHealthPoints(hero.getHealthPoints() + potion.getHealingAmount());
}

void operator-(Hero &hero, Monster &monster)
{
    hero.setHealthPoints(hero.getHealthPoints() - 10);
    if (monster.getType() == 'T')
    {
        TankMonster &t = dynamic_cast<TankMonster &>(monster);
        int dmg = 20 - t.getShield();
        t.setShield(dmg >= 0 ? 0 : t.getShield() - 20);
        if (dmg > 0)
        {
            t.setHealthPoints(t.getHealthPoints() - dmg);
        }
    }
    else
    {
        GhostMonster &g = dynamic_cast<GhostMonster &>(monster);
        g.setHealthPoints(g.getHealthPoints() - 20);
    }
}

// Gun subclasses

Pistol::Pistol() : Gun("Pistol", 16, 30, 2) {}

Bazooka::Bazooka() : Gun("Bazooka", 4, 150, 8) {}

Rifle ::Rifle() : Gun("Rifle", 30, 20, 4) {}

// Monster class
Monster::Monster(char t, int x, int y, int hp) : Character(t, x, y, hp) {}

// Hero subclasses

MedicHero::MedicHero(char t, int x, int y, int hp, int ha) : Hero(t, x, y, hp), healingAmount(ha) {}

int MedicHero::getHealingAmount()
{
    return healingAmount;
}

void MedicHero::useSpecial()
{
    if (!usedSpecial)
    {
        usedSpecial = !usedSpecial;
        setHealthPoints(getHealthPoints() + healingAmount);
    }
    else
    {
        cout << "Used Special Ability Already" << endl;
    }
}

bool MedicHero::hasUsedSpecial()
{
    return usedSpecial;
}

DemolitionHero::DemolitionHero(char t, int x, int y, int hp) : Hero(t, x, y, hp)
{
}

void DemolitionHero::swapWeapon()
{
    if (curr == weapon)
    {
        curr = weapon2;
    }
    else
    {
        curr = weapon;
    }
}

Gun *DemolitionHero::getCurrent()
{
    return curr;
}

void DemolitionHero::setCurrent(Gun *current)
{
    curr = current;
}

void DemolitionHero::useSpecial()
{
    swapWeapon();
}

Gun *DemolitionHero::getWeapon2()
{
    return weapon2;
}

void DemolitionHero::setWeapon2(Gun *weapon2)
{
    DemolitionHero::weapon2 = weapon2;
}

// Monster subclasses
GhostMonster::GhostMonster(char t, int x, int y, int hp) : Monster(t, x, y, hp), isVisible(true) {}

bool GhostMonster::isVisibleOnMap() const
{
    return isVisible;
}

void GhostMonster::setVisible()
{
    isVisible = !isVisible;
}

TankMonster::TankMonster(char t, int x, int y, int hp, int s) : Monster(t, x, y, hp), shield(s) {}

int TankMonster::getShield() const
{
    return shield;
}

void TankMonster::setShield(int shield)
{
    TankMonster::shield = shield;
}

// Item class
Item::Item(char t) : Object(t) {}

// Item subclasses
Ammo ::Ammo(int b) : Item('A'), bullets(b) {}

int Ammo::getBullets() const
{
    return bullets;
}

Potion::Potion(int ha) : Item('P'), healingAmount(ha) {}

int Potion::getHealingAmount() const
{
    return healingAmount;
}

// Game class
Game::Game()
{
    hero = NULL;
    // Initialize grid with empty objects
    grid = new Object **[rows]; // Change the type to Object **
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new Object *[cols]; // Change the type to Object *
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = new Object('.'); // Allocate memory for each Object
        }
    }

    // round = 1;
}

Game::~Game()
{
    // Deallocate memory for grid objects
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            delete grid[i][j];
        }
    }
    // Deallocate memory for hero object
    // delete hero;
}

Hero *Game::getHero()
{
    return hero;
}

int Game::round = 1;

void Game::generateMap()
{
    srand(time(0));

    // Generate health potions
    for (int i = 0; i < 5; i++)
    {
        int healingAmount = rand() % 41 + 10; // Random number between 10 and 50
        grid[rand() % rows][rand() % cols] = new Potion(healingAmount);
    }

    // Generate ammo
    for (int i = 0; i < 10; i++)
    {
        int bullets = rand() % 16 + 5; // Random number between 5 and 20
        grid[rand() % rows][rand() % cols] = new Ammo(bullets);
    }

    // Generate monsters

    int monsterCount = 5;
    int monsterHPRange = 10;
    int monsterHPMin = 60;

    for (int j = 0; j < monsterCount; j++)
    {
        int x = rand() % rows;
        int y = rand() % cols;
        int hp = (10 * (rand() % monsterHPRange)) + monsterHPMin;
        grid[x][y] = new TankMonster('T', x, y, hp, hp);
    }

    for (int j = 0; j < monsterCount; j++)
    {
        int x = rand() % rows;
        int y = rand() % cols;
        int hp = (10 * (rand() % monsterHPRange)) + monsterHPMin;
        grid[x][y] = new GhostMonster('G', x, y, hp);
    }
}

void Game::showMap()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j]->getType() == 'G')
            {
                GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[i][j]);
                if (g.isVisibleOnMap())
                {
                    cout << grid[i][j]->getType() << " ";
                }
                else
                {
                    cout << ". ";
                }
            }
            else
            {
                cout << grid[i][j]->getType() << " ";
            }
        }
        cout << endl;
    }
}

void Game::startGame()
{
    int heroType;
    int gunType;

    cout << "Please enter 1 to choose Demolition or 2 to choose Medic: ";
    cin >> heroType;

    cout << "Please enter 1 for Pistol, 2 for Bazooka, or 3 for Rifle: ";
    cin >> gunType;

    if (heroType == 1)
    {
        if (gunType == 1)
        {
            Pistol *p = new Pistol();
            hero = new DemolitionHero('D', 0, 0, 100);
            hero->setWeapon(p);
        }
        else if (gunType == 2)
        {
            Bazooka *b = new Bazooka();
            hero = new DemolitionHero('D', 0, 0, 100);
            hero->setWeapon(b);
        }
        else if (gunType == 3)
        {
            Rifle *r = new Rifle();
            hero = new DemolitionHero('D', 0, 0, 100);
            hero->setWeapon(r);
        }
        cout << "Enter 2nd Weapon: " << endl;
        cout << "Please enter 1 for Pistol, 2 for Bazooka, or 3 for Rifle: ";
        cin >> gunType;
        if (gunType == 1)
        {
            Pistol *p = new Pistol();
            dynamic_cast<DemolitionHero *>(hero)->setWeapon2(p);
        }
        else if (gunType == 2)
        {
            Bazooka *b = new Bazooka();
            dynamic_cast<DemolitionHero *>(hero)->setWeapon2(b);
        }
        else if (gunType == 3)
        {
            Rifle *r = new Rifle();
            dynamic_cast<DemolitionHero *>(hero)->setWeapon2(r);
        }
        dynamic_cast<DemolitionHero *>(hero)->setCurrent(dynamic_cast<DemolitionHero *>(hero)->getWeapon());
    }

    else if (heroType == 2)
    {
        if (gunType == 1)
        {
            Pistol *p = new Pistol();
            hero = new MedicHero('M', 0, 0, 100, 50);
            hero->setWeapon(p);
        }
        else if (gunType == 2)
        {
            Bazooka *b = new Bazooka();
            hero = new MedicHero('M', 0, 0, 100, 50);
            hero->setWeapon(b);
        }
        else if (gunType == 3)
        {

            Rifle *r = new Rifle();
            hero = new MedicHero('M', 0, 0, 100, 50);
            hero->setWeapon(r);
        }
    }
    generateMap();
    grid[0][0] = hero;
    cout << *hero << endl;

    showMap();
}

void Game::FireGun(char Direction)
{
    int x = hero->getPositionX();
    int y = hero->getPositionY();
    Gun *gun = hero->getType() == 'D' ? dynamic_cast<DemolitionHero &>(*hero).getCurrent() : dynamic_cast<MedicHero &>(*hero).getWeapon();
    if (gun->getBullets() <= 0)
    {
        cout << "Not Enough Bullets" << endl;
        return;
    }
    if (Direction == 'w')
    {
        for (int i = 0; i < gun->getRange() && x - i >= 0; i++)
        {
            if (grid[x - i][y]->getType() == 'G')
            {
                GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x - i][y]);
                g.setHealthPoints(g.getHealthPoints() - gun->getDamage());
                break;
            }
            else if (grid[x - i][y]->getType() == 'T')
            {
                TankMonster &t = dynamic_cast<TankMonster &>(*grid[x - i][y]);
                int dmg = gun->getDamage() - t.getShield();
                t.setShield(dmg >= 0 ? 0 : t.getShield() - gun->getDamage());
                if (dmg > 0)
                {
                    t.setHealthPoints(t.getHealthPoints() - dmg);
                }
                break;
            }
        }
    }
    if (Direction == 's')
    {
        for (int i = 0; i < gun->getRange() && x + i < rows; i++)
        {
            if (grid[x + i][y]->getType() == 'G')
            {
                GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x + i][y]);
                g.setHealthPoints(g.getHealthPoints() - gun->getDamage());
                break;
            }
            else if (grid[x + i][y]->getType() == 'T')
            {
                TankMonster &t = dynamic_cast<TankMonster &>(*grid[x + i][y]);
                int dmg = gun->getDamage() - t.getShield();
                t.setShield(dmg >= 0 ? 0 : t.getShield() - gun->getDamage());
                if (dmg > 0)
                {
                    t.setHealthPoints(t.getHealthPoints() - dmg);
                }
                break;
            }
        }
    }
    if (Direction == 'a')
    {
        for (int i = 0; i < gun->getRange() && y - i >= 0; i++)
        {
            if (grid[x][y - i]->getType() == 'G')
            {
                GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x][y - i]);
                g.setHealthPoints(g.getHealthPoints() - gun->getDamage());
                break;
            }
            else if (grid[x][y - i]->getType() == 'T')
            {
                TankMonster &t = dynamic_cast<TankMonster &>(*grid[x][y - i]);
                int dmg = gun->getDamage() - t.getShield();
                t.setShield(dmg >= 0 ? 0 : t.getShield() - gun->getDamage());
                if (dmg > 0)
                {
                    t.setHealthPoints(t.getHealthPoints() - dmg);
                }
                break;
            }
        }
    }
    if (Direction == 'd')
    {
        for (int i = 0; i < gun->getRange() && y + i < cols; i++)
        {
            if (grid[x][y + i]->getType() == 'G')
            {
                GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x][y + i]);
                g.setHealthPoints(g.getHealthPoints() - gun->getDamage());
                break;
            }
            else if (grid[x][y + i]->getType() == 'T')
            {
                TankMonster &t = dynamic_cast<TankMonster &>(*grid[x][y + i]);
                int dmg = gun->getDamage() - t.getShield();
                t.setShield(dmg >= 0 ? 0 : t.getShield() - gun->getDamage());
                if (dmg > 0)
                {
                    t.setHealthPoints(t.getHealthPoints() - dmg);
                }
                break;
            }
        }
    }
    gun->setBullets(gun->getBullets() - 1);
}

void Game::useGunSpecial()
{
    if (hero->getType() == 'D')
        dynamic_cast<DemolitionHero &>(*hero).getCurrent()->useSpecial(*hero, grid);
    else
        hero->getWeapon()->useSpecial(*hero, grid);
}

void Game::move(Hero &h, char direction)
{
    int x = h.getPositionX();
    int y = h.getPositionY();
    if (direction == 'w')
    {
        if (x - 1 >= 0 && grid[x - 1][y]->getType() == '.')
        {
            grid[x][y] = new Object('.');
            grid[x - 1][y] = &h;
            h.setPosition(x - 1, y);
        }
        else if (x - 1 >= 0 && grid[x - 1][y]->getType() == 'A')
        {
            grid[x][y] = new Object('.');
            Ammo &a = dynamic_cast<Ammo &>(*grid[x - 1][y]);
            *hero + a;
            grid[x - 1][y] = &h;
            h.setPosition(x - 1, y);
        }
        else if (x - 1 >= 0 && grid[x - 1][y]->getType() == 'P')
        {
            grid[x][y] = new Object('.');
            Potion &p = dynamic_cast<Potion &>(*grid[x - 1][y]);
            *hero + p;
            grid[x - 1][y] = &h;
            h.setPosition(x - 1, y);
        }
        else if (x - 1 >= 0 && grid[x - 1][y]->getType() == 'G')
        {
            GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x - 1][y]);
            *hero - g;
        }
        else if (x - 1 >= 0 && grid[x - 1][y]->getType() == 'T')
        {
            TankMonster &t = dynamic_cast<TankMonster &>(*grid[x - 1][y]);
            *hero - t;
        }
    }
    else if (direction == 's')
    {
        if (x + 1 < rows && grid[x + 1][y]->getType() == '.')
        {
            grid[x][y] = new Object('.');
            grid[x + 1][y] = &h;
            h.setPosition(x + 1, y);
        }
        else if (x + 1 < cols && grid[x + 1][y]->getType() == 'A')
        {
            grid[x][y] = new Object('.');
            Ammo &a = dynamic_cast<Ammo &>(*grid[x + 1][y]);
            *hero + a;
            grid[x + 1][y] = &h;
            h.setPosition(x + 1, y);
        }
        else if (x + 1 < cols && grid[x + 1][y]->getType() == 'P')
        {
            grid[x][y] = new Object('.');
            Potion &p = dynamic_cast<Potion &>(*grid[x + 1][y]);
            *hero + p;
            grid[x + 1][y] = &h;
            h.setPosition(x + 1, y);
        }
        else if (x + 1 < cols && grid[x + 1][y]->getType() == 'G')
        {
            GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x + 1][y]);
            *hero - g;
        }
        else if (x + 1 < cols && grid[x + 1][y]->getType() == 'T')
        {
            TankMonster &t = dynamic_cast<TankMonster &>(*grid[x + 1][y]);
            *hero - t;
        }
    }
    else if (direction == 'a')
    {
        if (y - 1 >= 0 && grid[x][y - 1]->getType() == '.')
        {
            grid[x][y] = new Object('.');
            grid[x][y - 1] = &h;
            h.setPosition(x, y - 1);
        }
        else if (y - 1 >= 0 && grid[x][y - 1]->getType() == 'A')
        {
            grid[x][y] = new Object('.');
            Ammo &a = dynamic_cast<Ammo &>(*grid[x][y - 1]);
            *hero + a;
            grid[x][y - 1] = &h;
            h.setPosition(x, y - 1);
        }
        else if (y - 1 >= 0 && grid[x][y - 1]->getType() == 'P')
        {
            grid[x][y] = new Object('.');
            Potion &p = dynamic_cast<Potion &>(*grid[x][y - 1]);
            *hero + p;
            grid[x][y - 1] = &h;
            h.setPosition(x, y - 1);
        }
        else if (y - 1 >= 0 && grid[x][y - 1]->getType() == 'G')
        {
            GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x][y - 1]);
            *hero - g;
        }
        else if (y - 1 >= 0 && grid[x][y - 1]->getType() == 'T')
        {
            TankMonster &t = dynamic_cast<TankMonster &>(*grid[x][y - 1]);
            *hero - t;
        }
    }
    else if (direction == 'd')
    {
        if (y + 1 < rows && grid[x][y + 1]->getType() == '.')
        {
            grid[x][y] = new Object('.');
            grid[x][y + 1] = &h;
            h.setPosition(x, y + 1);
        }
        else if (y + 1 < rows && grid[x][y + 1]->getType() == 'A')
        {
            grid[x][y] = new Object('.');
            Ammo &a = dynamic_cast<Ammo &>(*grid[x][y + 1]);
            *hero + a;
            grid[x][y + 1] = &h;
            h.setPosition(x, y + 1);
        }
        else if (y + 1 < rows && grid[x][y + 1]->getType() == 'P')
        {
            grid[x][y] = new Object('.');
            Potion &p = dynamic_cast<Potion &>(*grid[x][y + 1]);
            *hero + p;
            grid[x][y + 1] = &h;
            h.setPosition(x, y + 1);
        }
        else if (y + 1 < rows && grid[x][y + 1]->getType() == 'G')
        {
            GhostMonster &g = dynamic_cast<GhostMonster &>(*grid[x][y + 1]);
            *hero - g;
        }
        else if (y + 1 < rows && grid[x][y + 1]->getType() == 'T')
        {
            TankMonster &t = dynamic_cast<TankMonster &>(*grid[x][y + 1]);
            *hero - t;
        }
    }
}

int Game::checkGameOver()
{
    if (hero->getHealthPoints() <= 0)
    {
        cout << "The hero lost!" << endl;
        return 0;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j]->getType() == 'T' || grid[i][j]->getType() == 'G')
                return -1;
        }
    }

    cout << "The hero have won!" << endl;
    return 1;
}

void Game::updateMap()
{
    srand(time(0));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j]->getType() == 'G' || grid[i][j]->getType() == 'T')
            {
                Monster &m = dynamic_cast<Monster &>(*grid[i][j]);
                if (m.getHealthPoints() <= 0)
                {
                    grid[i][j] = new Object('.');
                }
            }
            if (round % 3 == 0)
            {
                if (grid[i][j]->getType() == 'G')
                {
                    auto &g = dynamic_cast<GhostMonster &>(*grid[i][j]);
                    g.setVisible();
                }
            }
        }
    }
    int monsterHPRange = 10;
    int monsterHPMin = 60;

    if (round % 20 == 0)
    {
        int x = rand() % rows;
        int y = rand() % cols;
        while (grid[x][y]->getType() != '.')
        {
            x = rand() % rows;
            y = rand() % cols;
        }
        int hp = (rand() % monsterHPRange + 1) * monsterHPMin;
        grid[x][y] = new GhostMonster('G', x, y, hp);

        x = rand() % rows;
        y = rand() % cols;
        while (grid[x][y]->getType() != '.')
        {
            x = rand() % rows;
            y = rand() % cols;
        }
        hp = (rand() % monsterHPRange + 1) * monsterHPMin;
        grid[x][y] = new TankMonster('T', x, y, hp, hp);
    }
    // system("clear");
    showMap();
}

int Game::getRound()
{
    return round;
}

void Game::increaseRound()
{
    round++;
}

int main()
{
    Game game;
    game.startGame();
    while (game.checkGameOver() == -1)
    {
        cout << "Current Round: " << game.getRound() << endl;
        cout << endl;
        cout << "Choose your next move: " << endl;
        cout << "1. Press m to Move" << endl;
        cout << "2. Press f to Fire Gun" << endl;
        cout << "3. Press s to use Gun Special Ability" << endl;
        cout << "4. Press h to use Hero Special Ability" << endl;
        cout << "5. Press q to quit" << endl;
        char choice;
        cin >> choice;
        if (choice == 'm')
        {
            cout << "Enter direction (q to return): ";
            char direction;
            cin >> direction;
            if (direction == 'q')
            {
                system("clear");
                goto Update;
            }
            if (direction != 'w' && direction != 's' && direction != 'a' && direction != 'd')
            {
                system("clear");
                cout << "Invalid Direction" << endl;
                goto Update;
            }
            int x = game.getHero()->getPositionX();
            int y = game.getHero()->getPositionY();
            if (direction == 'w')
            {
                if (x - 1 < 0)
                {
                    system("clear");
                    cout << "Invalid Move" << endl;
                    goto Update;
                }
            }
            else if (direction == 's')
            {
                if (x + 1 >= 15)
                {
                    system("clear");
                    cout << "Invalid Move" << endl;
                    goto Update;
                }
            }
            else if (direction == 'a')
            {
                if (y - 1 < 0)
                {
                    system("clear");
                    cout << "Invalid Move" << endl;
                    goto Update;
                }
            }
            else if (direction == 'd')
            {
                if (y + 1 >= 15)
                {
                    system("clear");
                    cout << "Invalid Move" << endl;
                    goto Update;
                }
            }
            game.move(*game.getHero(), direction);
        }
        else if (choice == 'f')
        {
            cout << "Enter direction (q to return): ";
            char direction;
            cin >> direction;
            if (direction == 'q')
            {
                system("clear");
                goto Update;
            }
            if (direction != 'w' && direction != 's' && direction != 'a' && direction != 'd')
            {
                system("clear");
                cout << "Invalid Direction" << endl;
                goto Update;
            }
            game.FireGun(direction);
        }
        else if (choice == 's')
        {
            Gun *gun = game.getHero()->getType() == 'D' ? dynamic_cast<DemolitionHero &>(*game.getHero()).getCurrent() : dynamic_cast<MedicHero &>(*game.getHero()).getWeapon();
            if (gun->getName() == "Bazooka" && (game.getHero()->getPositionX() == game.getHero()->getPositionY() || game.getHero()->getPositionX() == 14 - game.getHero()->getPositionY()))
            {
                game.useGunSpecial();
            }
            else if (gun->getName() == "Bazooka" && !(game.getHero()->getPositionX() == game.getHero()->getPositionY() || game.getHero()->getPositionX() == 14 - game.getHero()->getPositionY()))
            {
                system("clear");
                cout << "Not in Diagonal" << endl;
                goto Update;
            }
            else if (gun->getName() == "Pistol" && gun->getBullets() >= 4)
            {
                game.useGunSpecial();
            }
            else if (gun->getName() == "Rifle" && gun->getBullets() >= 3)
            {
                game.useGunSpecial();
            }
            else
            {
                system("clear");
                cout << "Not Enough Bullets" << endl;
                goto Update;
            }
        }
        else if (choice == 'h')
        {
            if (game.getHero()->getType() == 'M')
            {
                bool used = dynamic_cast<MedicHero &>(*game.getHero()).hasUsedSpecial();
                if (used)
                {
                    system("clear");
                    cout << "Used Special Ability Already" << endl;
                    goto Update;
                }
            }
            game.getHero()->useSpecial();
        }
        else if (choice == 'q')
        {
            system("clear");
            cout << "Hero has given up :(" << endl;
            break;
        }
        game.increaseRound();
        system("clear");
    Update:
        cout << *game.getHero() << endl;
        game.updateMap();
    }
    return 0;
}
