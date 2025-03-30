// Noms: MBADU NYANGI GRACE NEFERTITI
//       RAMZI DHOUIBI
//  position.cpp
// description : fonction utilitaire qui permet de lire et valider si c'est bien un entier qui est lu
// param[ES] : flux d'entree sur lequel on lit l'entier
// param[S] : entier lu
// pre : le flux est existant et ouvert (diff. de NULL)
// post : lit une valeur dans le flux jusqu'à ce qu'elle soit un entier

#include "position.h"
#include <iostream> 
#include <limits>

using namespace std;
// constructeur par defaut dans le cas 
Position::Position() : coord_x(0), coord_y(0) {}

// constructeur surchage avec des valeurs definies 
Position::Position(int x, int y) :coord_x(x), coord_y(y) {}


int Position::ligne() const  //cette fonction retourne la coord_x 
{
    return coord_x;
}

int Position::colonne() const  //cette  fonction retourne la coord_y
{
    return coord_y;
}

// mis a jour de la coord_x
void Position::set_ligne(int ligne)
{
    coord_x = ligne;
}
// mis a jour de la coord_y
void Position::set_colonne(int colonne)
{
    coord_y = colonne;
}

// cette methode compare deux objets de type position en verifiant sil sont egaux ou pas 
bool operator==(const Position& pos1, const Position& pos2)
{
    return pos1.ligne() == pos2.ligne() && pos1.colonne() == pos2.colonne();
}

// Surcharge de loperateur >> lit une position a partir d'un flux d entree.
// Appelle une fonction utilitaire lireValiderEntier() pour valider lentree
istream& operator>>(istream& is, Position& pos)
{
    void lireValiderEntier(std::istream & es_entree, int& s_entier);

    cout << "Entrez la ligne (-1 pour quitter) : ";
    lireValiderEntier(is, pos.coord_x);

    if (pos.coord_x == -1)
    {
        return is;
    }
    cout << ("Entrez la colonne: ");
    lireValiderEntier(is, pos.coord_y);
    return is;
}
// Surcharge de loperateur << : affiche une position dans un flux de sortie.
// Le format d affichage est "ligne , colonne"
ostream& operator<<(ostream& os, const Position& pos) {
    os << pos.ligne() << " , " << pos.colonne();
    return os;
}

static void lireValiderEntier(istream& es_entree, int& s_entier)
{
    assert(es_entree);

    while (!(es_entree >> s_entier))
    {
        // Afficher un message d'erreur et redemander le numero de ligne
        cout << "Erreur! Vous devez entrer une nombre entier! " << endl << "Entrez la ligne : ";
        // Vider le tampon de lecture
        es_entree.clear();
        // Ignorer tous les caracteres deja entres
        es_entree.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    assert(es_entree);
}


