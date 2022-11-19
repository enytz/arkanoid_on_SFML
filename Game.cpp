#include "Game.h"

Game::Game()
    : window("EnterName"), ball(SIZE_HOR,SIZE_VERT), desk(SIZE_HOR,SIZE_VERT), state (true) {}

void Game::Update()
{
    window.Update();
    ball.Move();
    desk.Move();

}

void Game::LateUpdate()
{
    ball.CheckCollision(SIZE_HOR, SIZE_VERT,desk.GetRefRect().getSize().x,desk.GetRefRect().getSize().y, desk.GetRefRect().getPosition().x, state);
    desk.CheckCollision(SIZE_HOR, SIZE_VERT,ttyData.get_value_sensor());
    desk.CheckCollisionKeyPressed(SIZE_HOR, SIZE_VERT);
}

void Game::Draw()
{
    window.BeginDraw();
    window.Draw(ball.GetRefBall());
    window.Draw(desk.GetRefRect());
    //if (state == 0)
    //{
    //    GameOver(text);
     //   window.Draw(text);

     //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //}
    window.EndDraw();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

bool Game::IsRunning() 
{
    while (window.IsOpen() && !(ball.IsQuit()) && state)
        return true;
    state = false;      // for case if IsQuit or IsOpen generate quit
    return false;

}


void Game::ReadDataTTY()
{
    ttyData.read_data(state);
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
}
