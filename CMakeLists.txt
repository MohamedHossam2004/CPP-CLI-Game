project(Programming_III_M1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Programming_III_M1 main.cpp
        Object.h
        Characters/Character.h
        Characters/Heroes/Hero.h
        Weapons/Gun.h
        Weapons/Pistol.h
        Weapons/Bazooka.h
        Weapons/Rifle.h
        Characters/Heroes/MedicHero.h
        Characters/Heroes/DemolitionHero.h
        Characters/Monsters/Monster.h
        Characters/Monsters/GhostMonster.h
        Characters/Monsters/TankMonster.h
        Items/Item.h
        Items/Ammo.h
        Items/Potion.h
        GameEngine/Game.h
        Point.h)
