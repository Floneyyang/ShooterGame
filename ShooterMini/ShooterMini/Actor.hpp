//
//  Actor.hpp
//  ShooterMini
//
//  Created by Floney Yang on 1/31/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Actor{
public:
    Actor(int scale, int numOfSides, int _speed);
    ~Actor();
    
public:
    CircleShape transform;
    float speed;
    
    
};


#endif /* Actor_hpp */
