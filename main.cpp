#include "Game.h"
#include "Window.h"

int main()
{
    Game game;
    std::thread thread2 ([&game](){game.ReadDataTTY();});
    while (game.IsRunning())
    {   
        //auto t1 = std::chrono::high_resolution_clock::now();
        game.Update();
        game.LateUpdate();
        game.Draw();
        //auto t2 = std::chrono::high_resolution_clock::now();
        //std::cout<<std::chrono::duration<double>(t2-t1).count()<<std::endl;
    }
    thread2.join();
    return 0;
}