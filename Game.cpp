#include "Game.h"
#include <sstream>
#include <fstream>
#include <algorithm>
const int WindowWidth = 800;/**<Szerokosc okna gry*/
const int WindowHeight = 600;/**<Wysokosc okna gry*/
const int bricksX=8,bricksY=4,brickWidth=80,brickHeight=20;/**< zmienne okreslające odpowiednio ilosc cegielek w wierszu, maksymalną ilosc cegielek w kolumnie, szerokosc oraz wysokosc cegielki */
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(WindowWidth,WindowHeight),"Arkanoid",Style::Default);/*!<Glowne okno gry*/
/*!
* Szablon odpowiedzialny za poinformowanie o zetknięciu się dwoch obiektow.
*/
template <class T1,class T2> bool isIntersecting(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right() &&
           A.bottom() >= B.top() && A.top() <= B.bottom();
}
/*!
* Przeksztalca zmienna typu int w string
*/
string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

bool Game::collision(Paddle& paddle, Ball& ball)
{
    if(!isIntersecting(paddle,ball)) {
    return false;
    }
    else {
    if(ball.getPosition().x<paddle.getPosition().x-40)
    {
        ball.move1();
    }
    else if(paddle.getPosition().x-40<=ball.getPosition().x&&ball.getPosition().x<paddle.getPosition().x-20)
    {
        ball.move2();
    }
    else if(paddle.getPosition().x-20<=ball.getPosition().x&&ball.getPosition().x<paddle.getPosition().x)
    {
        ball.move3();
    }
    else if(paddle.getPosition().x<=ball.getPosition().x&&ball.getPosition().x<paddle.getPosition().x+20)
    {
        ball.move4();
    }
    else if(paddle.getPosition().x+20<=ball.getPosition().x&&ball.getPosition().x<paddle.getPosition().x+40)
    {
        ball.move5();
    }
    else if(paddle.getPosition().x+40<=ball.getPosition().x)
    {
        ball.move6();
    }
    return true;
    }
}


bool Game::collision(Brick& brick, Ball& ball)
{
    if(!isIntersecting(brick,ball)){
        return false;
    }
    else{
    brick.hp=brick.hp-1;
    if(brick.hp==0){
    brick.destroy();
    wynik=wynik+10;
    }
    float overlapLeft=ball.right() - brick.left();
    float overlapRight=brick.right() - ball.left();
    float overlapTop=ball.bottom() - brick.top();
    float overlapBottom=brick.bottom() - ball.top();

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};
    if(abs(minOverlapX) < abs(minOverlapY))
        ballFromLeft ? ball.moveleft(): ball.moveright();
    else
        ballFromTop ? ball.moveup() : ball.movedown();

        return true;
    }
}

Game::Game(void)
{
    font.loadFromFile("Mecha.ttf");
    state = MENU;
}


Game::~Game(void)
{
}
void Game::runGame()
{
    fstream plik;
    string tmp;
    int tmps;
    plik.open("plik.txt",ios::in);
    for(int i=0;i<5;i++){
    plik>>tmp>>tmps;
    highscores.push_back(wyniki(tmp,tmps));
    }
    plik.close();
    while(state!=END)
    {
        switch (state)
        {
        case GameState::MENU:
            menu();
            break;
        case GameState::GAME:
            gra();
            break;
        case GameState::ABOUT:
            about();
            break;
        case GameState::HIGHSCORE:
            highscore();
            break;
        case GameState::GAME_OVER:
            game_over();
            break;
        case GameState::END:
            window.close();
            break;
        }
    }
}


void Game::menu()
{
    BackgroundTexture.loadFromFile("Background.png");
    Sprite sBackground(BackgroundTexture);
    Text title("Arkanoid",font,80);
    title.setStyle(Text::Bold);

    title.setPosition(WindowWidth/2-title.getGlobalBounds().width/2,20);

    const int ile = 4;

    Text tekst[ile];

    string str[] = {"Play","Highscore","About","Exit"};
    for(int i=0; i<ile; i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);

        tekst[i].setString(str[i]);
        tekst[i].setPosition(WindowWidth/2-tekst[i].getGlobalBounds().width/2,150+i*100);
    }

    while(state == MENU)
    {
        Vector2f mouse(Mouse::getPosition(window));
        Event event;

        while(window.pollEvent(event))
        {
            if((event.type == Event::Closed) || ((event.type == Event::KeyPressed) &&
                    (event.key.code == Keyboard::Escape)))
            {
                state = END;
            }
            else if((tekst[0].getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                state = GAME;

            }
            else if((tekst[1].getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                state = HIGHSCORE;
            }
            else if((tekst[2].getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                state=ABOUT;
            }
            else if((tekst[3].getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                state = END;
            }
        }
        for(int i=0; i<ile; i++)
            if(tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setFillColor(Color::Red);
            else tekst[i].setFillColor(Color::White);

        window.clear();
        window.draw(sBackground);
        window.draw(title);
        for(int i=0; i<ile; i++)
            window.draw(tekst[i]);

        window.display();
    }
}
void Game::about()
{
    BackgroundTexture.loadFromFile("Background.png");
    Sprite sBackground(BackgroundTexture);
    Text title("Arkanoid",font,80);
    title.setStyle(Text::Bold);
    title.setPosition(WindowWidth/2-title.getGlobalBounds().width/2,20);
    Text description("Projekt Programowanie w Jezyku C2\nMateusz Detka,Beniamin Golda 2ID12A",font,40);
    description.setPosition(WindowWidth/2-description.getGlobalBounds().width/2,120);

    Text tutorial("Poruszasz paletka za pomoca strzalek.\nTwoim zadaniem jest odbijanie pileczki tak,\nby zniszczyc wszystkie bloczki.\nJak dlugo wytrzymasz?",font,40);
    tutorial.setPosition(WindowWidth/2-tutorial.getGlobalBounds().width/2,220);
    Text back("Powrot ESC",font,40);
    back.setPosition(0.1*WindowWidth,0.8*WindowHeight);
    while(state == ABOUT)
    {
        Vector2f mouse(Mouse::getPosition(window));
        Event event;

        while(window.pollEvent(event))
        {

            if((event.type == Event::KeyPressed) &&
                    (event.key.code == Keyboard::Escape))
            {
                state = MENU;
            }
            else if(event.type==Event::Closed)
            {
                window.close();
            }
            else if((back.getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                state = MENU;
            }

            window.clear();
            window.draw(sBackground);
            window.draw(title);
            window.draw(description);
            window.draw(back);
            window.draw(tutorial);
            window.display();
        }
        if(back.getGlobalBounds().contains(mouse))
            back.setFillColor(Color::Red);
        else back.setFillColor(Color::White);
    }

}
void Game::highscore(){

    BackgroundTexture.loadFromFile("Background.png");
    Sprite sBackground(BackgroundTexture);
    Text title("Arkanoid",font,80);
    title.setStyle(Text::Bold);
    title.setPosition(WindowWidth/2-title.getGlobalBounds().width/2,20);
    Text ranking("Highscore",font,40);
    ranking.setPosition(WindowWidth/2-ranking.getGlobalBounds().width/2,120);
    Text back("Powrot ESC",font,40);
    back.setPosition(0.1*WindowWidth,0.8*WindowHeight);
    Text txtScores[5];
    while(state == HIGHSCORE)
    {
        Vector2f mouse(Mouse::getPosition(window));
        Event event;
    window.clear();
        while(window.pollEvent(event))
        {

            if((event.type == Event::KeyPressed) &&
                    (event.key.code == Keyboard::Escape))
            {
                state = MENU;
            }
            else if(event.type==Event::Closed)
            {
                window.close();
            }
            else if((back.getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                state = MENU;
            }
        }
        window.draw(sBackground);
        for(int i=0;i<5;i++){
            txtScores[i].setCharacterSize(40);
            txtScores[i].setFont(font);
            txtScores[i].setString(highscores[i].nick + " " + IntToString(highscores[i].score));
            txtScores[i].setPosition(WindowWidth/2-txtScores[i].getGlobalBounds().width/2, 200+i*40);
            window.draw(txtScores[i]);

        }

            window.draw(title);
            window.draw(ranking);
            window.draw(back);
            window.display();
        if(back.getGlobalBounds().contains(mouse))
            back.setFillColor(Color::Red);
        else back.setFillColor(Color::White);
    }


}
void Game::generuj(vector<Brick> &bricks,int number,int hp){
for(int i=0;i<number;i++)
    {
        for(int j=0;j<bricksX;j++)
        {
            bricks.emplace_back((j+1)*(brickWidth+10),(i+2)*(brickHeight+5),brickWidth,brickHeight);
        }
    }
for(auto& brick : bricks)
    {
        brick.hp=hp;
    }
}


void Game::gra(){

    window.setFramerateLimit(60);
    Ball ball(WindowWidth,WindowHeight);
    Paddle paddle(WindowWidth,WindowHeight);
    ball.shape.setPosition(paddle.shape.getPosition().x,paddle.shape.getPosition().y-10);
    Event ev;
    int playerhp=2;
    bool pauza = false;
    bool generated=false;
    int number=1;
    int hp=1;
    BackgroundTexture.loadFromFile("Background.png");
    Sprite sBackground(BackgroundTexture);
    Text score;
    score.setFont(font);
    score.setCharacterSize(20);
    score.setStyle(Text::Bold);
    score.setPosition(10,10);
    score.setFillColor(Color::Red);
    score.setString("0");
    Text Life;
    Life.setFont(font);
    Life.setCharacterSize(20);
    Life.setStyle(Text::Bold);
    Life.setPosition(WindowWidth-70,10);
    Life.setFillColor(Color::Red);
    wynik=0;
    while(state==GAME)
    {

        window.clear();
        while(window.pollEvent(ev))
        {

            if((ev.type == Event::KeyPressed) &&
                    (ev.key.code == Keyboard::Escape)){
                state = MENU;
            }
            else if(ev.type==Event::Closed){
                window.close();
            }
            else if((ev.type == Event::MouseButtonReleased)
                     && (ev.mouseButton.button == Mouse::Left));
            else if(ev.type==Event::KeyPressed&&ev.key.code==Keyboard::Space){
                if(pauza==true)
                    pauza=false;
                else if(pauza==false)
                    pauza=true;
            }
        }
        if(!pauza){
                if(!generated)
                {
                    generuj(bricks,number,hp);
                    generated=true;
                }
        ball.update();
        paddle.upadate();
        collision(paddle,ball);
        for(auto& brick : bricks)
            if(collision(brick,ball))
                break;

        auto iterator=remove_if(begin(bricks),end(bricks),[](Brick& brick){return brick.isDestroyed();});
        bricks.erase(iterator,end(bricks));
        if(bricks.empty())
        {
            number++;
            if(number>bricksY)
            {
                number=1;
                hp++;

            }
            ball.shape.setPosition(paddle.shape.getPosition().x,paddle.shape.getPosition().y-10);
            generated=false;
        }
        if(ball.bottom()>WindowHeight)
        {
            playerhp--;
            ball.shape.setPosition(paddle.shape.getPosition().x,paddle.shape.getPosition().y-10);
            if(playerhp==0){
                bricks.clear();
                state=GAME_OVER;
                break;
            }
        }
        }
        score.setString("SCORE: "+IntToString(wynik));
        Life.setString("LIFE: "+IntToString(playerhp));
        window.draw(sBackground);
        window.draw(paddle.shape);
        for(auto& brick : bricks){
            brick.shape.setTexture(&brick.BrickTexture);
            window.draw(brick.shape);
            }
        window.draw(score);
        window.draw(Life);
        window.draw(ball.shape);
        window.display();
    }
}


void Game::game_over()
{
    BackgroundTexture.loadFromFile("Background.png");
    Sprite sBackground(BackgroundTexture);
    Text title("Arkanoid",font,80);
    title.setStyle(Text::Bold);
    title.setPosition(WindowWidth/2-title.getGlobalBounds().width/2,20);
    Text youlost("YOU LOST",font,80);
    youlost.setPosition(WindowWidth/2-youlost.getGlobalBounds().width/2,0.2*WindowHeight);
    Text back("Powrot ESC",font,40);
    back.setPosition(0.1*WindowWidth,0.8*WindowHeight);
    Text highs("HIGHSCORES",font,40);
    highs.setPosition(0.7*WindowWidth,0.8*WindowHeight);
    Text points;
    points.setFont(font);
    points.setCharacterSize(40);
    points.setString("Twoj wynik: "+IntToString(wynik));
    points.setPosition(WindowWidth/2-points.getGlobalBounds().width/2,0.4*WindowHeight);

    Text nick("Podaj nick: ",font,40);
    nick.setPosition(0.3*WindowWidth,0.5*WindowHeight);
    string player;
    Text wprowadzony;
    wprowadzony.setFont(font);
	wprowadzony.setCharacterSize(40);
	wprowadzony.setPosition(0.5*WindowWidth, 0.5*WindowHeight);
    bool test=false;
    bool zapis=false;

        if(wynik>highscores[4].score){
                test=true;
        }


    while(state==GAME_OVER)
    {
        Vector2f mouse(Mouse::getPosition(window));
        Event event;
         while(window.pollEvent(event))
        {

            if((event.type == Event::KeyPressed) &&
                    (event.key.code == Keyboard::Escape))
            {
                zapis=true;
                state = MENU;
            }
            else if(event.type==Event::Closed)
            {
                zapis=true;
                state=END;
            }
            else if((back.getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                zapis=true;
                state = MENU;
            }
            else if((highs.getGlobalBounds().contains(mouse)) &&
                    (event.type == Event::MouseButtonReleased) && (event.mouseButton.button == Mouse::Left))
            {
                zapis=true;
                state = HIGHSCORE;
            }
            else if ((event.type == Event::TextEntered)&&test)
			{
				Uint32 unicode = event.text.unicode;

				if (unicode == 8 && player.size() > 0)
				{
					player.erase(player.size() - 1, 1);
					wprowadzony.setString(player);
				}
				else if (unicode==13){
                zapis=true;
                test=false;
                state=HIGHSCORE;
                    break;
				}

				else if (((unicode >= 48 && unicode <= 57) || (unicode >= 65 && unicode <= 90) ||
					(unicode >= 97 && unicode <= 122)) && player.size() < 6)
				{
					player += static_cast<char>(unicode);
					wprowadzony.setString(player);
				}
			}
            else if((event.type == Event::MouseButtonReleased)
                     && (event.mouseButton.button == Mouse::Left));


        }
        window.clear();
        window.draw(sBackground);
        window.draw(back);
        window.draw(title);
        window.draw(points);
        window.draw(youlost);
        window.draw(highs);
        if(test){
            window.draw(nick);
            window.draw(wprowadzony);

        }

        window.display();
        if(back.getGlobalBounds().contains(mouse))
            back.setFillColor(Color::Red);
        else back.setFillColor(Color::White);
        if(highs.getGlobalBounds().contains(mouse))
            highs.setFillColor(Color::Red);
        else highs.setFillColor(Color::White);
        if(zapis){
            if(player.length()<1)
                player = "NONAME";
            fstream plik;
            plik.open("plik.txt",ios::trunc|ios::out);
            highscores.push_back(wyniki(player,wynik));
            sort(highscores.begin(),highscores.end());
            for (int i=0;i<5;i++){
                plik<<highscores[i].nick<<" "<<highscores[i].score<<endl;
            }
            plik.close();
            }

    }

}

