#ifndef Desk_h
#define Desk_h

#include <SFML/Graphics.hpp>


class Desk 
{
    public:
    Desk(const int SizeWindowHor, const int SizeWindowVert, int sizeRectHor= 100, int sizeRectVert = 30);
    const sf::RectangleShape& GetRefRect(){ return desk;}

    private:
    sf::RectangleShape desk;
};


#endif