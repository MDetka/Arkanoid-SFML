#ifndef BRICK_H
#define BRICK_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Brick
{
    public:
        /*!
        * Konstruktor cegielki odpowiedzialny za ustawienie jej pozycji,
        * rozmiaru,
        * punktu glownego (origin),
        * wczytanie textury.
        */
        Brick(float b_x,float b_y,float brickWidth,float brickHeight);
        /*!
        * Zwraca wspolrzedne aktualnej pozycji cegielki
        */
        Vector2f getPosition();
        /*!
        * Zwraca wspolrzedne lewej sciany cegielki
        */
        float left();
        /*!
        * Zwraca wspolrzedne prawej sciany cegielki
        */
        float right();
        /*!
        * Zwraca wspolrzedne gornej sciany cegielki
        */
        float top();
        /*!
        * Zwraca wspolrzedne dolnej sciany cegielki
        */
        float bottom();
        /*!
        * Zwraca zmienna destroyed.
        */
        bool isDestroyed();
        /*!
        * Funkcja odpowiedzialna za zmiane wartosci stalej destroyed na true,
        * niszczy cegielke.
        */
        void destroy();
        /*!
        * Zwraca rozmiar cegielki.
        */
        Vector2f getSize();
        RectangleShape shape;/**< Ustawia ksztalt cegielki */
        int hp{1};/**< Zmienna odpowiedzialna za ilosc zycia cegielki */
        Texture BrickTexture;/**< Textura cegielki */
    protected:

    private:
        bool destroyed=false;/**< Informacja o tym czy cegielka powinna zostac zniszczona */
};

#endif // BRICK_H
