#include "Game.h"

Game::Game()
    : window("desk and ball"), ball(SIZE_HOR,SIZE_VERT), desk(SIZE_HOR,SIZE_VERT), state (true) 
    {
        if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf"))
            std::cout<<"Error reading font"<<std::endl;
    }

void Game::Update()
{
    window.Update();
    desk.Move();
    ball.Move();
}

void Game::LateUpdate()
{
    desk.CheckCollision(SIZE_HOR, SIZE_VERT,ttyData.get_value_sensor());
    ball.CheckCollision(SIZE_HOR, SIZE_VERT,desk.GetRefRect().getSize().x,desk.GetRefRect().getSize().y, desk.GetRefRect().getPosition().x, state);
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
    SaveResult();
    if (GameOver())
        {
            return false;
        }
    else 
        {
            return true;
        }

}

bool Game::Restart()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    window.BeginDraw();
    sf::Text queryToOut;
    SetStringOnDisplay(queryToOut,font,"Game over", SIZE_HOR/2-100, SIZE_VERT/2 ,48);

    sf::Text question;
    SetStringOnDisplay(question,font,"Press \"Y\" for new game and \"N\" or \"Q\" for out", SIZE_HOR/2-200, SIZE_VERT/2+60,20);

    window.Draw(queryToOut);
    window.Draw(question);
    window.EndDraw();
    while(true)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            //Set default position for new game
            desk.SetDefaultPosition(SIZE_HOR,SIZE_VERT);
            ball.SetDefaultSettings(SIZE_HOR,SIZE_VERT);
            state = true;
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

void Game::SaveResult()
{
    std::ifstream ifs{fileResultScore};
    if (!ifs)
    {
        std::cout<< "Error opening file "<<fileResultScore<<std::endl;
        return;
    }
    std::vector<std::pair<std::string, int>> scoreResult;
    std::pair<std::string,int> data;
    
    while(!ifs.eof())
    {
        ifs>>data.first>>data.second;
        scoreResult.push_back(data);        
    }
    ifs.close();
    
    // Input user name----------
    std::string player_name{"Player"};
    PrintInputOnScreen(window,font, "Enter your name: ", player_name, SIZE_HOR/2+50, SIZE_VERT/2);

    // Check on full or not table score-----
    int colResult = ball.GetScore();
    if (scoreResult.size() >= 10)
    {
        int min = 1000;
        int indMin = 0;
        int i =0;
        for (i=0;i<scoreResult.size();++i)
        {
            if (min > scoreResult[i].second)
            {
                min = scoreResult[i].second;
                indMin = i;
            }
        }
            scoreResult.erase(scoreResult.begin()+i);
    }

    // output modern data with new result---
    data.first = player_name;
    data.second = colResult;
    scoreResult.push_back(data);
    // 
    std::sort(scoreResult.begin(),scoreResult.end(),[](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b){return a.second> b.second;});
   
    //  write in the file
    std::ofstream ofs{fileResultScore,std::ios_base::out};
    if (!ofs)
    {
        std::cout<< "Error opening file "<<fileResultScore<<std::endl;
        return;
    }
    
    for (int i=0; i<scoreResult.size()-1;++i)
    {
        ofs<<scoreResult[i].first<<' '<<scoreResult[i].second<<std::endl;
        //std::cout<<scoreResult[i].first<<' '<<scoreResult[i].second<<std::endl;
    }
        ofs<<scoreResult[scoreResult.size()-1].first<<' '<<scoreResult[scoreResult.size()-1].second;
    ofs.close();
    
}


void SetStringOnDisplay(sf::Text& text, sf::Font& font, const std::string& str,
                         const float posX, const float posY, const unsigned int size,
                          sf::Color color)
{
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    sf::Vector2f position;
    position.x = posX;
    position.y = posY;
    text.setPosition(position);
}


void PrintInputOnScreen(Window& window, sf::Font& font,std::string stringName, std::string& str, float posX, float posY)
{
    sf::Text text;
    sf::Text strName;
    int strCoef = stringName.size();
    int strSize = 30;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    while(!((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            str +="a";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            str +="b";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            str +="c";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            str +="d";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            str +="e";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            str +="f";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            str +="g";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            str +="h";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            str +="i";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            str +="j";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            str +="k";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            str +="m";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            str +="n";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            str +="o";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            str +="p";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            str +="q";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            str +="r";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            str +="s";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            str +="t";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
            str +="u";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
            str +="v";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            str +="w";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            str +="x";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
            str +="y";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            str +="z";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            str +="1";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            str +="2";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            str +="3";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            str +="4";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            str +="5";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            str +="6";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            str +="7";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
            str +="8";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
            str +="9";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
            str +="0";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !str.empty())
            str.erase(str.end()-1);  
        window.BeginDraw();
        SetStringOnDisplay(strName,font,stringName,posX-strCoef*strSize/2, posY ,strSize); 
        SetStringOnDisplay(text,font,str,posX, posY ,strSize); 
        window.Draw(text);  
        window.Draw(strName);
        window.EndDraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }

}
