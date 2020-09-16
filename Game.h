#include <vector>
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"
#include "Scores.h"
using namespace std;
using namespace sf;
class Game
{
public:
    /*!
    * Konstruktor za zadanie wczytuje uzywana czcionke oraz przelacza stan gry na MENU.
    */
	Game(void);
	/*!
    * Destruktor obiektu gry aktualnie nie posiada zadnego zadania.
    */
	~Game(void);
    /*!
    * Glowna funkcja gry.
    * Wczytuje plik z oecnymi wynikami graczy,
    * decyduje na podstawie odpowiedznich wyborow jaki stan gry powinien byc wlaczony
    */
	void runGame();

protected:
    /*!
    * Typ wyliczeniowy okreslajacy wszystkie stany gry.
    */
	enum GameState {MENU,GAME,HIGHSCORE,ABOUT,GAME_OVER,END};
	GameState state;/**< Pole okreslajace obecny stan gry. */

private:
    int wynik;/**< Pole okreslajace wynik obecnego gracza. */
    vector<wyniki> highscores;/**< Tabela wynikow z ostatnimi 5 najwyzszymi wynikami.*/
    vector<Brick> bricks;/**< Tablica zawierajaca informacje o kazdej cegielce.*/
	Font font;/**< Czcionka uzywana w grze.*/
	/*!
	* Funkcja wywolywana po przelaczeniu stanu gry na MENU.
	* Wczytuje oraz ustawia tlo gry,
	* umozliwia obsluge myszka,
	* umozliwia przelaczanie miedzy stanami gry,
	* wypisuje odpowiednie informacje takie jak tytul gry oraz wybory poszczegolnych jej stanow.
	*/
	void menu();
	/*!
	* Funkcja wywolywana po przelaczeniu stanu gry na ABOUT.
	* Wczytuje oraz ustawia tlo gry,
	* wykorzystuje czcionke do wyswietlenia informacji o grze oraz autorach,
	* umozliwia powrot do poprzedniego stanu (MENU).
	*/
	void about();
	/*!
	* Funkcja wywolywana po przelaczeniu stanu gry na HIGHSCORE.
	* Wczytuje oraz ustawia tlo gry,
	* wyswietla informacje o 5 najlepszych wynikach w grze wczytanych wczesniej z pliku,
	* umozliwia powrot do poprzedniego stanu (MENU).
	*/
	void highscore();
	/*!
	* Funkcja wywolywana po przelaczeniu stanu gry na GAME.
	* Gra wlasciwa,
	* wczutuje obiekty takie jak: pilka, paletka, cegielki, czcionka,
	* wczytuje oraz ustawia textury obiektow oraz tla,
	* wyswietla je na ekranie wraz z informacja o ilosci zyc gracza oraz obecnym wynikiem,
	* po utracie wszystkich punktow zycia przelacza stan gry na GAME_OVER.
	*/
	void gra();
	/*!
	* Funkcja wywolywana po przelaczeniu stanu gry na GAME_OVER.
	* Wyswietla informacje o porazce gracza oraz jego wynik,
	* jesli osiagniêty wynik jest dostatecznie wysoki by zapisaæ siê na Highscore prosi o nick gracza,
	* umozlia rowniez na wlaczenie stanu MENU oraz HIGHSCORE.
	*/
	void game_over();
	/*!
	* Funkcja odpowiedzialna za generowanie odpowiedniej ilosci cegielek o wyliczonych wspolzêdnych
	* oraz ustawianie ilosci ich zycia.
	*/
	void generuj(vector<Brick> &bricks,int number,int hp);
	/*!
	* Funkcja odpowiedzialna za kolizje pomiedzy pilka a cegielka.
	* Po spelnieniu odpowiedniego warunku ktory mowi o zetknieciu sie pilki i cegielki,
	* okresla nowy wektor przesuniêcia pilki,
	* odejmuje zycie cegielki i jesli wynosi ono 0 to niszczy ja,
	* dodaje do wyniku 10.
	*/
	bool collision(Brick& brick, Ball& ball);
	/*!
	* Funkcja odpowiedzialna za kolizje pomiedzy pilka a paletka.
	* Po spelnieniu odpowiedniego warunku ktory mowi o zetknieciu sie pilki i paletki,
	* okresla nowy wektor przesuniecia pilki,
	*/
	bool collision(Paddle& paddle, Ball& ball);
	Texture BackgroundTexture/**< Textura tla */;
};
