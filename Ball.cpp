#include "Ball.h"
#include <iostream>

Ball::Ball(const int SizeWindowHor, const int SizeWindowVert,const float radius)
    //:angle(GenerateAngle()), speedX(10), speedY(10), dx(speedX* cos(degtorad(angle))), dy(speedY* sin(degtorad(angle))), collision(0), scoreCollisions(0)        // add set settings for angle
{
    ball.setRadius(radius);
    ball.setFillColor(sf::Color::Blue);
    Ball::SetDefaultSettings(SizeWindowHor,SizeWindowVert);
}

void Ball::Move()
{
    sf::Vector2f pos = ball.getPosition();
    pos.x +=dx;
    pos.y +=dy;
    ball.setPosition(pos);
}

void Ball::SetDefaultSettings(const int SizeWindowHor, const int SizeWindowVert)
{
	//std::cout<<"Old "<< speedX<<' '<<speedY<<std::endl;
	sf::Vector2f pos;
    pos.x = SizeWindowHor/2;
    pos.y = ball.getRadius();
    ball.setPosition(pos);
	angle = GenerateAngle();
	speedX = 10.0;
	speedY = 10.0;
	dx = speedX* cos(degtorad(angle));
	dy = speedX* sin(degtorad(angle));
	collision = 0;
	scoreCollisions =0;
	//std::cout<<"New "<< speedX<<' '<<speedY<<std::endl;
}

void Ball::CheckCollision(const int SizeHor, const int SizeVert, const int sizeDeskX, const int sizeDeskY, const int posDesk, std::atomic<bool>& state)
{
    if (CollisionWithFieldAndBall(SizeHor, SizeVert, sizeDeskX, sizeDeskY, posDesk, state))
	{
		float val = degtorad(angle);
		dx = speedX * cos(val);
		dy = speedY * sin(val);
	}
}

bool Ball::CollisionWithFieldAndBall(const int sizeHor,const int sizeVert, const int sizeDeskX, const int sizeDeskY, const int posDesk, std::atomic<bool>& state)
{
    bool flag =0;
	float radius = ball.getRadius();
	sf::Vector2f ballPosition = ball.getPosition();

	//  check collision with vertical field line
	if (ballPosition.x <= 0 || ballPosition.x+2*radius >= sizeHor)
	{
		angle *=-1;
		return 1;
	}

	// check collison with horizontal field line
	if (ballPosition.y <= 0)
		{
			if (angle < 0)
				angle -= 180;
			else
				angle += 180;
			speedX *= -1;
			return 1;
		}
	if (ballPosition.y+2*radius >= sizeVert)
		{
			collision =1;
			state = 0;
			return 1;
		}
	
	// check collision ball and desk on Oy

	if (ballPosition.y >= sizeVert-sizeDeskY-2*radius && (ballPosition.x >= posDesk && ballPosition.x <= posDesk+sizeDeskX))
	{
		sf::Vector2f pos;
		pos.y = sizeVert-sizeDeskY-2*radius-2;
		pos.x = ball.getPosition().x;
		ball.setPosition(pos);
		if (angle < 0)
			angle -= 180;
		else
			angle += 180;
		speedX *= -1;
		speedX *=1.05; // boost ball in case every cycle of the collision desk and ball
		speedY *=1.05; //
		++scoreCollisions;		// for save score after every game
		return 1;
	}

	// check collision ball and desk on Ox

	if (ballPosition.x >= posDesk-2*radius && ballPosition.x <= posDesk+sizeDeskX-radius && ballPosition.y >= sizeVert - sizeDeskY- radius)
	{
		angle *=-1;
		return 1;
	}
	
	// check collision on angle of the rectangle
	float distanceToAngleRectLeft = sqrt((ballPosition.x+radius-posDesk)*(ballPosition.x+radius-posDesk)+(ballPosition.y+radius-(sizeVert-sizeDeskY))*(ballPosition.y+radius-(sizeVert-sizeDeskY)));
	float distanceToAngleRectRigth = sqrt((ballPosition.x+radius-(posDesk+sizeDeskX))*(ballPosition.x+radius-(posDesk+sizeDeskX))+ (ballPosition.y+radius-(sizeVert-sizeDeskY))*(ballPosition.y+radius-(sizeVert-sizeDeskY)));
	if (distanceToAngleRectLeft - radius <=3 || distanceToAngleRectRigth - radius <= 3)
	{
		if (angle < 0)
			angle -= 180;
		else
			angle += 180;
		++scoreCollisions;		// for save score after every game
		return 1;
	}
	return 0;
}
float degtorad(int& angle)
{
	if (angle >= 360)
		angle -= 360;
	return angle > 0 ? (angle * M_PI / 180) : (180 + angle) * M_PI / 180;
}


int GenerateAngle()
{
	srand(time(NULL));
	int value = 20;
	while (true)
	{
		if ((value = -60 +rand()%120) <=-20 || value >= 20)
		{
			return value;
		}
	}
}