#include "Game.h"

Game::Game()
    : window("EnterName"), ball(SIZE_HOR,SIZE_VERT), desk(SIZE_HOR,SIZE_VERT), state (true) 
    {
        if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf"))
            std::cout<<"Error reading font"<<std::endl;
    }

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
    window.EndDraw();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

bool Game::IsRunning() 
{
    while (window.IsOpen() && !(ball.IsQuit()) && state)
        return true;

    if (GameOver())
        return false;
    else 
        return true;

}

bool Game::Restart()
{
    sf::Text queryToOut;
    queryToOut.setFont(font);
    queryToOut.setString("Game over");
    queryToOut.setCharacterSize(48);
    queryToOut.setFillColor(sf::Color::Black);
    sf::Vector2f positionTextGameOver;
    positionTextGameOver.x = SIZE_HOR/2-100;
    positionTextGameOver.y = SIZE_VERT/2;
    queryToOut.setPosition(positionTextGameOver);

    sf::Text question;
    question.setFont(font);
    question.setString("Press \"Y\" for new game and \"N\" or \"Q\" for out");
    question.setCharacterSize(20);
    question.setFillColor(sf::Color::Black);
    sf::Vector2f positionTextRestart;
    positionTextRestart.x = SIZE_HOR/2-200;
    positionTextRestart.y = SIZE_VERT/2+60;
    question.setPosition(positionTextRestart);

    window.Draw(queryToOut);
    window.Draw(question);
    window.EndDraw();
    while(true)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            state = true;
            //Set default position for new game
            desk.SetDefaultPosition(SIZE_HOR,SIZE_VERT);
            ball.SetDefaultPosition(SIZE_HOR,SIZE_VERT);
            return true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            state = false; // for case if IsQuit or IsOpen generate quit
            return false;
        }
    }
}

void Game::ReadDataTTY()
{
    ttyData.read_data(state);
}

bool Game::GameOver()
{
    if (Restart())
        return false;
    else
        return true;
}

