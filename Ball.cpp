#include "Ball.h"

Ball::Ball(float b_x,float b_y)
{
    //shape.setPosition(b_x/2,b_y/2);
    shape.setRadius(this->ballRadius);
    shape.setFillColor(Color::White);
    shape.setOrigin(this->ballRadius,this->ballRadius);
    this->Height=b_y;
    this->Width=b_x;
}

void Ball::update()
{
    shape.move(this->velocity);
    if(this->left()<=0)
    {
        velocity.x=-velocity.x;//velocity.x=ballVelocity;
        if(this->left()<0){
            velocity.x=ballVelocity;
        }

    }
    else if(this->right()>=this->Width)
    {
        velocity.x=-velocity.x;//velocity.x=-ballVelocity;
        if(this->right()>this->Width){
            velocity.x=-ballVelocity;
        }
    }

    if(this->top()<=0)
    {
        velocity.y=-velocity.y;//velocity.y=ballVelocity;

    }
    /*else if(this->bottom()>this->Height)
    {
        velocity.y=-ballVelocity;
    }*/
}


float Ball::left()
{
    return this->shape.getPosition().x-shape.getRadius();
}
float Ball::right()
{
    return this->shape.getPosition().x+shape.getRadius();
}
float Ball::top()
{
    return this->shape.getPosition().y-shape.getRadius();
}
float Ball::bottom()
{
    return this->shape.getPosition().y+shape.getRadius();
}

void Ball::movedown()
{
    this->velocity.y=ballVelocity;
}
void Ball::moveup()
{
    this->velocity.y=-ballVelocity;
}
void Ball::moveright()
{
    this->velocity.x=ballVelocity;
}
void Ball::moveleft()
{
    this->velocity.x=-ballVelocity;
}

void Ball::move1()
{
    this->velocity.x=-((ballVelocity*pow(6,0.5))/2);
    this->velocity.y=-((ballVelocity*pow(2,0.5))/2);
}

void Ball::move2()
{
    this->velocity.x=-ballVelocity;
    this->velocity.y=-ballVelocity;
}

void Ball::move3()
{
    this->velocity.x=-((ballVelocity*pow(2,0.5))/2);
    this->velocity.y=-((ballVelocity*pow(6,0.5))/2);
}

void Ball::move4()
{
    this->velocity.x=((ballVelocity*pow(2,0.5))/2);
    this->velocity.y=-((ballVelocity*pow(6,0.5))/2);
}

void Ball::move5()
{
    this->velocity.x=ballVelocity;
    this->velocity.y=-ballVelocity;
}

void Ball::move6()
{
    this->velocity.x=((ballVelocity*pow(6,0.5))/2);
    this->velocity.y=-((ballVelocity*pow(2,0.5))/2);
}

Vector2f Ball::getPosition()
{
    return shape.getPosition();
}
