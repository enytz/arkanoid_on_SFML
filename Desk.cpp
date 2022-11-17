#include "Desk.h"

Desk::Desk(const int SizeWindowHor, const int SizeWindowVert, int sizeRectHor, int sizeRectVert)
    : dx(0)
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

void Desk::Move()
{
    sf::Vector2f rectPos;
    rectPos = desk.getPosition();
    rectPos.x += dx*10;
    desk.setPosition(rectPos);
}

void Desk::CheckCollision(int SizeWindowHor, int SizeWindowVert, int valueSensor)
{
    sf::Vector2f rectPos;
    rectPos = desk.getPosition();
    if (rectPos.x <= 0)
	{
		rectPos.x = 1;
        desk.setPosition(rectPos);
	}
	else if (rectPos.x + desk.getSize().x >= SizeWindowHor )
	{
		rectPos.x = SizeWindowHor-desk.getSize().x;
        desk.setPosition(rectPos);
	}

    if (valueSensor>= 5 && valueSensor < 10)			
		{
			dx =-3;
		}
	else if (valueSensor >=10 && valueSensor <15)
		{
			dx =-2;
		}
	else if (valueSensor >= 15 && valueSensor <20)
		{
			dx =-1;
		}
	else if (valueSensor >= 20 && valueSensor <25)
		{
			dx =0;
		}
	else if (valueSensor >= 25 && valueSensor <30)
		{
			dx =1;
		}
	else if (valueSensor >= 30 && valueSensor <35)
		{
			dx =2;
		}
	else if (valueSensor >=35 && valueSensor <40)
		{
			dx =3;
		}
}