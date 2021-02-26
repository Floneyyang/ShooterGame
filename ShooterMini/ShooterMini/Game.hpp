//
//  Game.hpp
//  ShooterMini
//
//  Created by Floney Yang on 1/25/21.
//  Copyright © 2021 Floney Yang. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.hpp"
#include "Enemy.hpp"

using namespace sf;

class Game{
public:
    Game(RenderWindow *window);
    virtual ~Game();
    
    //Accessors
    inline RenderWindow& getWindow(){return *this->window;}
    
    //Setters

    
    //Functions
    void Start(int screenWidth, int screenHeight);
    void Update();
    void Draw();
    
    //EnemyManager
    void EnemyInstantiateAfterDeath();
    void EnemyRespawn();
    void EnemyCollision();
    
    //enum
    enum Direction{
        Up,
        Down,
        Left,
        Right
    };
private:
    RenderWindow *window;
    int keyTime = 1;
    
    Player player;
    std::vector<Enemy> enemies;

    //helper functions
    bool checkIfPlayerOutOfBound(Direction dir, CircleShape *player);
    sf::Text text = Text();
    
    float enemyRespawnLimit = 10;
    

};

#endif /* Game_hpp */
