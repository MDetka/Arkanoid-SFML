#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
class Ball
{
    public:
        /*!
        * Konstruktor pilki.
        * Ustawia promien pilki,
        * kolor wypelnienia,
        * punkt poczatkowy (origin),
        * zapisuje wysokosc oraz szerokosc okna gry w zmiennych Height i Width.
        */
        Ball(float b_x,float b_y);
        CircleShape shape;/**< Ustawia ksztalt pilki */
        void update();
        /*!
        * Zwraca wspolrzedne lewej sciany pilki
        */
        float left();
        /*!
        * Zwraca wspolrzedne prawej sciany pilki
        */
        float right();
        /*!
        * Zwraca wspolrzedne gornej sciany pilki
        */
        float top();
        /*!
        * Zwraca wspolrzedne dolnej sciany pilki
        */
        float bottom();
        /*!
        * Zwraca pozycje pilki.
        */
        Vector2f getPosition();
        /*!
        * Zmienia predkosc przemieszczania pilki wzgeledem osi y,
        * tak by pilka przemieszczala sie w gore.
        */
        void moveup();
        /*!
        * Zmienia predkosc przemieszczania pilki wzgeledem osi y,
        * tak by pilka przemieszczala sie w dol.
        */
        void movedown();
        /*!
        * Zmienia predkosc przemieszczania pilki wzgeledem osi x,
        * tak by pilka przemieszczala sie w prawo.
        */
        void moveright();
        /*!
        * Zmienia predkosc przemieszczania pilki wzgeledem osi x,
        * tak by pilka przemieszczala sie w lewo.
        */
        void moveleft();
        /*!
        * Zmienia predkosc przemieszczania pilki,
        * tak by pilka przemieszczala sie w pod katem 30 stopni wzgledem lewej czesci paletki.
        */
        void move1();
        /*!
        * Zmienia predkosc przemieszczania pilki,
        * tak by pilka przemieszczala sie w pod katem 45 stopni wzgledem lewej czesci paletki.
        */
        void move2();
        /*!
        * Zmienia predkosc przemieszczania pilki,
        * tak by pilka przemieszczala sie w pod katem 60 stopni wzgledem lewej czesci paletki.
        */
        void move3();
        /*!
        * Zmienia predkosc przemieszczania pilki,
        * tak by pilka przemieszczala sie w pod katem 60 stopni wzgledem prawej czesci paletki.
        */
        void move4();
        /*!
        * Zmienia predkosc przemieszczania pilki,
        * tak by pilka przemieszczala sie w pod katem 45 stopni wzgledem prawej czesci paletki.
        */
        void move5();
        /*!
        * Zmienia predkosc przemieszczania pilki,
        * tak by pilka przemieszczala sie w pod katem 30 stopni wzgledem prawej czesci paletki.
        */
        void move6();
    protected:

    private:
        const float ballVelocity=5.f;/**< Predkosc pilki */
        const float ballRadius=10.f;/**< Promien pilki */
        Vector2f velocity{ballVelocity,ballVelocity};/**< Wektor przesuniecia pilki */
        int Height;/**< Wysokosc okna gry */
        int Width;/**< Szerokosc okna gry */

};

#endif // BALL_H
