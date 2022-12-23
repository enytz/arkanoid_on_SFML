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
#include <fstream>


class Game
{
    public:
        Game();
        void Update();
        void LateUpdate();
        void Draw();
        bool IsRunning();
        bool Restart();
        void ReadDataTTY();

    private:
        bool GameOver();
        void CollisionDeskAndBall();
        void SaveResult();
        void ShowResult();
        Window window;
        Ball ball;
        Desk desk;
        TTY ttyData;
        std::atomic<bool> state;
        std::atomic<bool> quitTheGame;
        sf::Font font;
        std::string fileResultScore{"DataResult.txt"};

};


void SetStringOnDisplay(sf::Text& text, sf::Font& font, const std::string& str, const float posX, const float posY, const unsigned int size = 30, sf::Color color = sf::Color::Black);

void PrintInputOnScreen(Window& window, sf::Font& font, std::string stringName, std::string& str, float posX, float posY);
#endif