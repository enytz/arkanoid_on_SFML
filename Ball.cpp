# include "Ball.h"
#include <iostream>

Ball::Ball(const int SizeWindowHor, const int SizeWindowVert,const float radius)
    :angle(20), speedX(10), speedY(10), dx(speedX* cos(degtorad(angle))), dy(speedY* sin(degtorad(angle))), collision(0)        // add set settings for angle
{
    ball.setRadius(radius);
    ball.setFillColor(sf::Color::Blue);
    sf::Vector2f pos;
    pos.x = SizeWindowHor/2;
    pos.y = radius;
    ball.setPosition(pos);
}

void Ball::Move()
{
    sf::Vector2f pos = ball.getPosition();
    pos.x +=dx;
    pos.y +=dy;
    ball.setPosition(pos);
}

void Ball::CheckCollision(const int SizeHor, const int SizeVert, const int sizeDeskX, const int sizeDeskY, const int posDesk)
{
    if (CollisionWithField(SizeHor, SizeVert, sizeDeskX, sizeDeskY, posDesk))
	{
		float val = degtorad(angle);
		dx = speedX * cos(val);
		dy = speedY * sin(val);
	}
}

bool Ball::CollisionWithField(const int sizeHor,const int sizeVert, const int sizeDeskX, const int sizeDeskY, const int posDesk)
{
    bool flag =0;

    // check X coordinate-----------------------
    if (round(ball.getPosition().x+2*ball.getRadius()) >= sizeHor || round(ball.getPosition().x) < 1 )
        {
            angle *=-1;
            flag = 1; 
        }
	// check Y coordinate
    if (round(ball.getPosition().y) <= 1 ||
		(round(ball.getPosition().y + 2*ball.getRadius()) >= sizeVert-sizeDeskY) && CollisionBallAndDeskOnX(round(ball.getPosition().x),round(posDesk), sizeDeskX, sizeDeskY))
	{
		if (angle < 0)
			angle -= 180;
		else
			angle += 180;
		speedX *= -1;
		flag = 1;
	}
	else if (round(ball.getPosition().y + 2*ball.getRadius()) >= (sizeVert-sizeDeskY/2))
	{
		collision =1;
	}

 	return flag ? 1 : 0;
}

bool Ball::CollisionBallAndDeskOnX(int posBallX, int posDeskX, int sizeDeskX, int sizeDeskY)
{
	if (posBallX >= posDeskX && posBallX < posDeskX+sizeDeskX)
		return true;
	return false;
}

float degtorad(int& angle)
{
	if (angle >= 360)
		angle -= 360;
	return angle > 0 ? (angle * M_PI / 180) : (180 + angle) * M_PI / 180;
}
