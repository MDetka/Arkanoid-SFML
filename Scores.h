#ifndef SCORES_H
#define SCORES_H
using namespace std;
class wyniki{
public:
    int score;/**< Wynik gracza */
    string nick;/**< Nick gracza */
    /*!
    * funkcja wczytujaca nick i wynik gracza
    */
    wyniki(string nick, int score){
    this->nick=nick;
    this->score=score;
    }

    bool operator<(const wyniki& inny) const{
    return score>inny.score;
    }
    };
#endif //SCORES_H

