//
//  Player.cpp
//  ShooterMini
//
//  Created by Floney Yang on 1/31/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#include "Player.hpp"
#include <math.h>


using namespace std;

const float PI = 3.14159265;

Player::Player(RenderWindow *window): Actor(70, 3, 20){
    this->window = window;
}

Player::~Player(){
    
}

void Player::Start(int screenWidth, int screenHeight){
    transform.setFillColor(sf::Color(150, 50, 250));
    transform.setOutlineThickness(10);
    transform.setOutlineColor(sf::Color(250, 150, 100));
    transform.setOrigin(transform.getRadius(), transform.getRadius());
    transform.setPosition(screenWidth/2, screenHeight*2/3);
    head = RectangleShape(Vector2f(70, 10));
    head.setFillColor(sf::Color(250, 150, 100));
    head.setPosition(transform.getPosition());
}

void Player::Update(){
    
}

void Player::Draw(){
    for(size_t i = 0; i < projectiles.size(); i++){
        window->draw(projectiles[i].transform);
    }
    window->draw(transform);
    window->draw(head);
}

void Player::MoveUp(){
    if(Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)){
        transform.move(0.f, -speed);
        head.move(0.f, -speed);
    }
}
void Player::MoveDown(){
    if(Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)){
        transform.move(0.f, speed);
        head.move(0.f, speed);
    }
}
void Player::MoveRight(){
    if(Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)){
        transform.move(speed, 0.f);
        head.move(speed, 0.f);
    }
}
void Player::MoveLeft(){
    if(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)){
        transform.move(-speed, 0.f);
        head.move(-speed, 0.f);
    }
}

void Player::LookAtMouse(){
    sf::Vector2f curPos = transform.getPosition();
    sf::Vector2i position = sf::Mouse::getPosition(*window);

    float dx = curPos.x - position.x;
    float dy = curPos.y - position.y;
    
    mousePosition = sf::Vector2i(dx,dy);

    playerRotation = (atan2(dy, dx)) * 180 / PI + 30;
    transform.setRotation(playerRotation);
    head.setRotation(playerRotation+146);
}

void Player::Shoot(std::vector<Enemy> &enemies){
    if(keyTime < keyResetTime) keyTime++;
    if(keyTime == keyResetTime && Keyboard::isKeyPressed(Keyboard::Space)){
        Projectile projectile = Projectile();
        projectile.transform.setRotation(90);
        projectile.transform.setPosition(transform.getPosition().x, transform.getPosition().y-transform.getRadius()/2);
        projectile.direction = sf::Vector2i(-mousePosition.x/20, -mousePosition.y/20);
        projectile.transform.setRotation(playerRotation-30);
        projectiles.push_back(Projectile(projectile));
        keyTime = 0;
    }
    
    for(size_t i = 0; i < projectiles.size(); i++){
        projectiles[i].transform.move(projectiles[i].direction.x, projectiles[i].direction.y);
        if(projectiles[i].transform.getPosition().y < 0 || projectiles[i].transform.getPosition().x < 0
           || projectiles[i].transform.getPosition().x > window->getSize().x
           || projectiles[i].transform.getPosition().y > window->getSize().y){
            projectiles.erase(projectiles.begin()+i);
        }else{
            for(size_t j = 0; j < enemies.size(); j++){
                if(projectiles[i].transform.getGlobalBounds().intersects(enemies[j].transform.getGlobalBounds())){
                    projectiles.erase(projectiles.begin()+i);
                    enemies[j].dead = true;
                    break;
                }
            }
        }
    }
}
