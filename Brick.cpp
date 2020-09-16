#include "Brick.h"

Brick::Brick(float b_x,float b_y,float brickWidth,float brickHeight)
{
    shape.setPosition(b_x,b_y);
    shape.setSize(Vector2f(brickWidth,brickHeight));
    shape.setOrigin(brickWidth/2,brickHeight/2);
    BrickTexture.loadFromFile("Brick.png");
}

float Brick::left()
{
    return this->shape.getPosition().x-shape.getSize().x/2;
}
float Brick::right()
{
    return this->shape.getPosition().x+shape.getSize().x/2;
}
float Brick::top()
{
    return this->shape.getPosition().y-shape.getSize().y/2;
}
float Brick::bottom()
{
    return this->shape.getPosition().y+shape.getSize().y/2;
}
Vector2f Brick::getPosition()
{
    return shape.getPosition();
}

bool Brick::isDestroyed()
{
    return this->destroyed;
}
void Brick::destroy()
{
    this->destroyed=true;
}
Vector2f Brick::getSize()
{
    return shape.getSize();
}

