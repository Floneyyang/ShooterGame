//
//  Actor.cpp
//  ShooterMini
//
//  Created by Floney Yang on 1/31/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#include "Actor.hpp"

Actor::Actor(int scale, int numOfSides, int _speed = 20){
    this->transform = CircleShape(scale, numOfSides);
    this->speed = _speed;
}

Actor::~Actor(){
    
}
