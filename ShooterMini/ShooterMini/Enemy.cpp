//
//  Enemy.cpp
//  ShooterMini
//
//  Created by Floney Yang on 2/1/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#include "Enemy.hpp"
#include "ResourcePath.hpp"
#include <chrono>
#include <ctime>

Enemy::Enemy(RenderWindow *window, int radius): Actor(radius, 30, 10){
    this->window = window;
    this->radius = radius;
}

Enemy::~Enemy(){
    
}

void Enemy::Start(float dirX, float dirY){
    float clockRadius = transform.getRadius();
    this->radius = transform.getRadius();
    
    transform.setFillColor(sf::Color(64, 224, 208));
    transform.setOutlineThickness(clockRadius/7);
    transform.setOutlineColor(sf::Color(250, 128, 114));
    transform.setOrigin(clockRadius, clockRadius);
    if(random) transform.setPosition(rand()%int(window->getSize().x - 2*transform.getRadius()) + transform.getRadius(),
                                     rand()%int(window->getSize().y - 2*transform.getRadius()) + transform.getRadius());
    else transform.setPosition(dirX, dirY);
    
    //Setup Clock
    float centerX = transform.getPosition().x;
    float centerY = transform.getPosition().y;
    
    float centerRadius = clockRadius/5;

    centerCircle = sf::CircleShape(centerRadius, 360);
    centerCircle.setPosition (centerX - centerRadius, centerY - centerRadius);
    centerCircle.setFillColor (sf::Color(250, 128, 114));
    
    float hourHandLength = (10.0f/16.0f) * clockRadius;
    float minuteHandLength = (14.0f/16.0f) * clockRadius;
    float secondHandLength = (15.0f/16.0f) * clockRadius;

    float hourHandWidth = 6.0f;
    float minuteHandWidth = 6.0f;
    float secondHandWidth = 3.0f;
    
    hourHand.setPosition (centerX, centerY - hourHandWidth / 2);
    hourHand.setSize (sf::Vector2f (hourHandLength, hourHandWidth));
    hourHand.setFillColor (sf::Color(102, 152, 255));
    
    minuteHand.setPosition (centerX, centerY - minuteHandWidth / 2);
    minuteHand.setSize (sf::Vector2f (minuteHandLength, minuteHandWidth));
    minuteHand.setFillColor (sf::Color(255, 204, 102));
    
    secondHand.setPosition (centerX, centerY - secondHandWidth / 2);
    secondHand.setSize (sf::Vector2f (secondHandLength, secondHandWidth));
    secondHand.setFillColor (sf::Color(127, 82, 93));
    
    direction = sf::Vector2i(rand()%int(speed), rand()%int(speed));
}

void Enemy::Update(){
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    second = now->tm_sec;
    minute = now->tm_min + second / 60;
    hour   = now->tm_hour + minute / 60;
    
    // change the angle of the hour, minute and second hand
    hourHandAngle = (hour / 12.0f) * 360.0f - 90.0f;
    minuteHandAngle = (minute / 60.0f) * 360.0f - 90.0f;
    secondHandAngle = (second / 60.0f) * 360.0f - 90.0f;
    hourHand.setRotation (hourHandAngle);
    minuteHand.setRotation (minuteHandAngle);
    secondHand.setRotation (secondHandAngle);
    
    Collision();
    Move(direction.x, direction.y);
    
}

void Enemy::Draw(){
    window->draw(transform);
    window->draw (hourHand);
    window->draw (minuteHand);
    window->draw (secondHand);
    window->draw (centerCircle);
    //window->draw(time);
}

void Enemy::Move(float dirX, float dirY){
    transform.move(dirX, dirY);
    centerCircle.move(dirX, dirY);
    hourHand.move(dirX, dirY);
    minuteHand.move(dirX, dirY);
    secondHand.move(dirX, dirY);
}

void Enemy::ResetPosition(float dirX, float dirY){
    transform.setPosition(dirX, dirY);
    centerCircle.setPosition(dirX-radius/5, dirY-radius/5);
    hourHand.setPosition(dirX, dirY-3.f);
    minuteHand.setPosition(dirX, dirY-3.f);
    secondHand.setPosition(dirX, dirY-1.5);
}

void Enemy::Collision(){
    if(transform.getPosition().x < transform.getRadius() ||
       (transform.getPosition().x + transform.getRadius()) > window->getSize().x){
        direction.x = -(direction.x+1);
        direction.y = rand()%int(speed);
    }
    else if(transform.getPosition().y < transform.getRadius() ||
       (transform.getPosition().y + transform.getRadius()) > window->getSize().y){
        direction.y = -(direction.y+1);
        direction.x = rand()%int(speed);
    }
}

