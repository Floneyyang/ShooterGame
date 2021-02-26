//
//  Projectile.hpp
//  ShooterMini
//
//  Created by Floney Yang on 1/31/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Projectile{
public:
    Projectile();
    ~Projectile();
    
public:
    sf::Vector2i direction;
    RectangleShape transform;
    
};

#endif /* Projectile_hpp */
