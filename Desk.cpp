#include "Desk.h"

Desk::Desk(const int SizeWindowHor, const int SizeWindowVert, int sizeRectHor, int sizeRectVert)
{
    sf::Vector2f rectSz;
    rectSz.x = sizeRectHor;
    rectSz.y = sizeRectVert;
    desk.setSize(rectSz);
    desk.setFillColor(sf::Color::Green);
    sf::Vector2f pos;
    pos.x = SizeWindowHor/2-sizeRectHor/2;
    pos.y = SizeWindowVert-sizeRectVert;
    desk.setPosition(pos);
}