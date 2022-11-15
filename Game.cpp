#include "Game.h"

Game::Game()
    : window("EnterName"), ball(SIZE_HOR,SIZE_VERT), desk(SIZE_HOR,SIZE_VERT){}


void Game::Update()
{
    window.Update();
    ball.Move();
}

void Game::LateUpdate()
{
    ball.CheckCollision(SIZE_HOR, SIZE_VERT,desk.GetRefRect().getSize().x,desk.GetRefRect().getSize().y, desk.GetRefRect().getPosition().x);
}

void Game::Draw()
{
    window.BeginDraw();
    window.Draw(ball.GetRefBall());
    window.Draw(desk.GetRefRect());
    //if ()
    {
      //  GameOver(text);
       // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    window.EndDraw();
}

bool Game::IsRunning() const
{
    while (window.IsOpen() && !(ball.IsQuit()))
        return true;
    return false;
}

void Game::GameOver(sf::Text& text)
{
    text.setString("Game over");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Red);
    sf::Vector2f pos;
    pos.x = SIZE_HOR/2-50;
    pos.y = SIZE_VERT/2;
    text.setPosition(pos);
    window.Draw(text);
}
