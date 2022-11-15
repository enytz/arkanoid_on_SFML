#ifndef Ball_h
#define Ball_h

#include <math.h>
#include <SFML/Graphics.hpp>
#define M_PI				3.14159265358979323846


float degtorad(int& angle);

class Ball
{
    public:
    Ball(const int SizeWindowHor, const int SizeWindowVert,const float radius= 10);
    void Move();
    void CheckCollision(const int SizeHor, const int SizeVert, const int sizeDeskX, const int sizeDeskY, const int posDesk);
    const sf::CircleShape& GetRefBall(){ return ball;}
    bool IsQuit() const{return collision;}

private:
    sf::CircleShape ball;
    bool CollisionWithField(const int sizeHor, const int sizeVert, const int sizeDeskX, const int sizeDeskY, const int posDesk);
    bool CollisionBallAndDeskOnX(int posBallX, int posDeskX, int sizeDeskX, int sizeDeskY);
    int angle;
    int speedX;
    int speedY;
    float dx;
    float dy;
    bool collision;
};




#endif