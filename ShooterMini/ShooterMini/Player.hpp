//
//  Player.hpp
//  ShooterMini
//
//  Created by Floney Yang on 1/31/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Actor.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"
#include <vector>

class Player: public Actor
{
public:
    Player(RenderWindow *window);
    ~Player();
    
    
    //movement
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    
    //Mouse control
    void LookAtMouse();
    
    //Shoot
    void Shoot(std::vector<Enemy> &enemies);
    
    void Start(int screenWidth, int screenHeight);
    void Update();
    void Draw();
    
    
private:
    RenderWindow *window;
    
    RectangleShape head;
    
    std::vector<Projectile> projectiles;
    float playerRotation;
    sf::Vector2i mousePosition;
    
    int keyTime = 0;
    int keyResetTime = 5;

};

#endif /* Player_hpp */
