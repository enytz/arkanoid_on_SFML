#ifndef Desk_h
#define Desk_h

#include <SFML/Graphics.hpp>

class Desk 
{
    public:
    Desk(const int SizeWindowHor, const int SizeWindowVert, int sizeRectHor= 100, int sizeRectVert = 20);
    void Move();
    void CheckCollision(int SizeWindowHor, int SizeWindowVert, int valueSensor);
    void CheckCollisionKeyPressed(int SizeWindowHor, int SizeWindowVert);
    const sf::RectangleShape& GetRefRect(){ return desk;}
    void SetDefaultPosition(const int SizeWindowHor, const int SizeWindowVert);

    private:
    sf::RectangleShape desk;
    int dx;
};


#endif