#ifndef Game_h
#define Game_h
#include "Window.h"
#include "Ball.h"
#include "Desk.h"
#include "tty.h"

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
        bool IsRunning();
        void ReadDataTTY();
        void GameOver(sf::Text& text);

    private:
        void CollisionDeskAndBall();
        Window window;
        Ball ball;
        Desk desk;
        TTY ttyData;
        std::atomic<bool> state;
        sf::Text text;

};

#endif