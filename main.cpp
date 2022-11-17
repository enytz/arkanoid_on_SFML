#include "Game.h"
#include "Window.h"

int main()
{
    Game game;
    std::thread thread2 ([&game](){game.ReadDataTTY();});
    while (game.IsRunning())
    {   
        game.Update();
        game.LateUpdate();
        game.Draw();
    }
    thread2.join();
    std::cout<<"END\n";
    std::cout.flush();
    return 0;
}