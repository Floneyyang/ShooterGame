//
//  Game.cpp
//  ShooterMini
//
//  Created by Floney Yang on 1/25/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#include "Game.hpp"
#include "ResourcePath.hpp"
#include <string>
#include <iostream>
#include <cmath>

unsigned int limit = 60;

Game::Game(RenderWindow *window): player(window){
    this->window = window;
    this->window->setFramerateLimit(limit);
    //this->player = Player(window);
}

Game::~Game(){
    
}

void Game::Start(int screenWidth, int screenHeight){
    //player = Player(window);
    player.Start(screenWidth, screenHeight);
    Enemy enemy = Enemy(window, 70);
    this->enemies.push_back(Enemy(enemy));
    this->enemies.push_back(Enemy(enemy));
    for(size_t i = 0; i < enemies.size(); i++){
        enemies[i].Start(0,0);
    }
}

void Game::Update(){
    if(keyTime < 1) keyTime++;
    else{
        
        if(checkIfPlayerOutOfBound(Up, &player.transform)){
            player.MoveUp();
            keyTime = 0;
        }
        if(checkIfPlayerOutOfBound(Left, &player.transform)){
            player.MoveLeft();
            keyTime = 0;
        }
        if(checkIfPlayerOutOfBound(Down, &player.transform)){
            player.MoveDown();
            keyTime = 0;
        }
        if(checkIfPlayerOutOfBound(Right, &player.transform)){
            player.MoveRight();
            keyTime = 0;
        }
        player.LookAtMouse();
        player.Shoot(enemies);
        /*
        if(Mouse::isButtonPressed(Mouse::Left)){
            keyTime = 0;
        }*/
        //cannon.setRotation(Mouse::getPosition().y);
        /*
        sf::Font font;
        if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
            return EXIT_FAILURE;
        }
        text.setFont(font);
        text.setCharacterSize(50);
        std::string rstr = std::to_string(rotation);
        text.setString(rstr);
        text.setFillColor(sf::Color::Black);*/
        
    }
    EnemyInstantiateAfterDeath();
    if(enemies.size() == 0) EnemyRespawn();
    EnemyCollision();
}

void Game::Draw(){
    player.Draw();
    for(size_t i = 0; i < enemies.size(); i++){
        enemies[i].Draw();
    }
    
}

bool Game::checkIfPlayerOutOfBound(Game::Direction dir, CircleShape *player){
    if(dir == Game::Up){
        return player->getPosition().y > player->getRadius();
    }
    else if(dir == Game::Down){
        return (player->getPosition().y + player->getRadius()) < window->getSize().y;
    }
    else if(dir == Game::Right){
        return (player->getPosition().x + player->getRadius()) < window->getSize().x;
    }
    else if(dir == Game::Left){
        return player->getPosition().x > player->getRadius();
    }
}

void Game::EnemyInstantiateAfterDeath(){
    for(size_t i = 0; i < enemies.size(); i++){
        enemies[i].Update();
        if(enemies[i].dead){
            if(enemies[i].radius/2 > enemyRespawnLimit){
                Enemy newEnemy = Enemy(window, enemies[i].radius/2);
                this->enemies.push_back(Enemy(newEnemy));
                enemies[enemies.size()-1].random = false;
                enemies[enemies.size()-1].Start(enemies[i].transform.getPosition().x+enemies[i].radius, enemies[i].transform.getPosition().y+enemies[i].radius);
                this->enemies.push_back(Enemy(newEnemy));
                enemies[enemies.size()-1].random = false;
                enemies[enemies.size()-1].Start(enemies[i].transform.getPosition().x-enemies[i].radius, enemies[i].transform.getPosition().y-enemies[i].radius);
            }
            enemies[i].dead = false;
            enemies.erase(enemies.begin()+i);
        }
    }
}

void Game::EnemyRespawn(){
    Enemy newEnemy = Enemy(window, 70);
    this->enemies.push_back(Enemy(newEnemy));
    enemies[enemies.size()-1].Start(0,0);
    this->enemies.push_back(Enemy(newEnemy));
    enemies[enemies.size()-1].Start(0,0);
}

void Game::EnemyCollision(){
    for(size_t i = 0; i < enemies.size(); i++){
        for(size_t j = i+1; j < enemies.size(); j++){
            if(enemies[i].transform.getGlobalBounds().intersects(enemies[j].transform.getGlobalBounds())){
                enemies[i].direction.x = -enemies[i].direction.x;
                enemies[i].direction.y = -enemies[i].direction.y;
                enemies[j].direction.x = -enemies[j].direction.x;
                enemies[j].direction.y = -enemies[j].direction.y;
                /*
                if(std::abs(enemies[i].transform.getPosition().x - enemies[j].transform.getPosition().x) < enemies[j].transform.getRadius()
                   || std::abs(enemies[i].transform.getPosition().y - enemies[j].transform.getPosition().y) < enemies[j].transform.getRadius()){
                    enemies[i].ResetPosition(enemies[i].transform.getPosition().x+enemies[i].transform.getRadius(), enemies[i].transform.getPosition().y+enemies[i].transform.getRadius());
                    enemies[j].ResetPosition(enemies[j].transform.getPosition().x-enemies[j].transform.getRadius(), enemies[j].transform.getPosition().y-enemies[j].transform.getRadius());
                }*/
            }
            if(enemies[j].transform.getPosition().y < 0 || enemies[j].transform.getPosition().x < 0
               || enemies[j].transform.getPosition().x > window->getSize().x
               || enemies[j].transform.getPosition().y > window->getSize().y){
                enemies.erase(enemies.begin()+j);
            }
        }
    }
}

