#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Paddle
{
    public:
        /*!
        * Konstruktor paletki.
        * Ustawia poczatkowa pozycje paletki,
        * rozmiar,
        * punkt poczatkowy (origin),
        * zapisuje wysokosc oraz szerokosc okna gry w zmiennych Height i Width,
        * wczytuje textury oraz ustawia aktualna.
        */
        Paddle(float p_x,float p_y);
        /*!
        * Funkcja odpowiedzialna za ruch paletki.
        * Aktualizuje jej polozenie o okreslony wektor po wcisnieciu przycisku
        * zmienia na czas wcisniecia texture paletki.
        */
        void upadate();
        RectangleShape shape;/**< Ustawia ksztalt cegielki */
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
        * Zwraca pozycje paletki.
        */
        Vector2f getPosition();
        Texture paddleTextureFront;/**< Textura paletki przy bezczynnosci */
        Texture paddleTextureLeft;/**< Textura paletki przy przemieszczaniu w lewo */
        Texture paddleTextureRight;/**< Textura paletki przy przemieszczaniu w prawo */
    protected:

    private:
        const float paddleWidth=120.f;/**< Szerokosc paletki. */
        const float paddleHeight=20.f;/**< Wysokosc paletki. */
        const float paddleVelocity=6.f;/**< Predkosc z jaka moze sie przemieszczac*/
        Vector2f velocity{paddleVelocity,0};/**<wektor przesuniecia o okresloej predkosci*/
        int Height;/**< Wysokosc okna gry */
        int Width;/**< Szerokosc okna gry */

};

#endif // PADDLE_H
