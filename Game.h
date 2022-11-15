#ifndef Game_h
#define Game_h
#include "Window.h"
#include "Ball.h"
#include "Desk.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>

class Game
{
    public:
        Game();
        void Update();
        void LateUpdate();
        void Draw();
        bool IsRunning() const;
        void GameOver(sf::Text& text);

    private:
        void CollisionDeskAndBall();
        Window window;
        Ball ball;
        Desk desk;
        sf::Text text;

};

#endif