
#include "Paddle.h"
Paddle::Paddle(float p_x,float p_y)
{
    shape.setPosition(p_x/2,10*p_y/11);
    shape.setSize(Vector2f(paddleWidth,paddleHeight));
    shape.setOrigin(this->paddleWidth/2,this->paddleHeight/2);
    this->Height=p_y;
    this->Width=p_x;
    paddleTextureFront.loadFromFile("paddlefront.png");
    paddleTextureLeft.loadFromFile("paddleleft.png");
    paddleTextureRight.loadFromFile("paddleright.png");
    shape.setTexture(&paddleTextureFront);
}

void Paddle::upadate()
{
    this->shape.move(this->velocity);
    if(Keyboard::isKeyPressed(Keyboard::Key::Left)&&this->left()>0)
    {
        velocity.x=-paddleVelocity;
        shape.setTexture(&paddleTextureLeft);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Key::Right)&&this->right()<Width)
    {
        velocity.x=paddleVelocity;
        shape.setTexture(&paddleTextureRight);
    }
    else
    {
        velocity.x=0;
        shape.setTexture(&paddleTextureFront);
    }
}
float Paddle::left()
{
    return this->shape.getPosition().x-shape.getSize().x/2;
}
float Paddle::right()
{
    return this->shape.getPosition().x+shape.getSize().x/2;
}
float Paddle::top()
{
    return this->shape.getPosition().y-shape.getSize().y/2;
}
float Paddle::bottom()
{
    return this->shape.getPosition().y+shape.getSize().y/2;
}
Vector2f Paddle::getPosition()
{
    return shape.getPosition();
}
