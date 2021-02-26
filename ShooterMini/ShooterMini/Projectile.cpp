//
//  Projectile.cpp
//  ShooterMini
//
//  Created by Floney Yang on 1/31/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#include "Projectile.hpp"

Projectile::Projectile(){
    transform = RectangleShape(Vector2f(50, 5));
}

Projectile::~Projectile(){
    
}
