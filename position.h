
//
//  position.h
//


#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <istream>
#include <ostream>
#include <cassert>

using namespace std;


// creation de la classe position(seul) 
class Position
{
private:
    int coord_x;
    int coord_y;

public:
    Position();
    Position(int coord_x, int coord_y);
    int ligne() const;
    int colonne() const;
    void set_ligne(int ligne);  // fonction qui permet de mettre a jour la valeur de la ligne 
    void set_colonne(int colonne);

    friend bool operator==(const Position& pos1, const Position& pos2);
    friend istream& operator>>(istream& is, Position& pos); 
    friend ostream& operator<<(ostream& os, const Position& pos);

};
static void lireValiderEntier(istream& es_entree, int& s_entier);


#endif /* Position_h */
