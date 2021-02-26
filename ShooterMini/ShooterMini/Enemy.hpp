//
//  Enemy.hpp
//  ShooterMini
//
//  Created by Floney Yang on 2/1/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Actor.hpp"

class Enemy: public Actor
{
public:
    Enemy(RenderWindow *window, int radius);
    ~Enemy();
    
    void Start(float dirX, float dirY);
    void Update();
    void Draw();
    
    //Movement
    void Move(float dirX, float dirY);
    void ResetPosition(float dirX, float dirY);
    
    //Collision
    void Collision();
    
public:
    bool dead = false;
    bool random = true;
    int radius;
    sf::Vector2i direction;

private:
    RenderWindow *window;
    
    sf::CircleShape centerCircle;
    sf::RectangleShape hourHand;
    sf::RectangleShape minuteHand;
    sf::RectangleShape secondHand;
    
    float hour = 0.0f;
    float minute = 0.0f;
    float second = 0.0f;

    float hourHandAngle = 0.0f;
    float minuteHandAngle = 0.0f;
    float secondHandAngle = 0.0f;
    
    
    
};

#endif /* Enemy_hpp */
