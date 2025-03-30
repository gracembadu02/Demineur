// fichier : carte_.cpp
// auteur.es : MBADU NYANGI GRACE NEFERTITI , 
//             RAMZI DHOUIBI
// date : 2024
// modifications :
// description : Ce fichier contient la definition des methodes A IMPLEMENTER de la classe Carte d'un jeu de demineur

#include "carte.h"
#include "utilitaires.h"

#include <iomanip>
#include <cassert>
#include <stdio.h>

// Description: Methode qui calcule le nombre de mines adjacentes a une case
// param[E] Position de la case
// retour : nombre de mines adjacentes a la case
// post : on compte le nombre de mines adjacentes a la case (entre 0 et 8)

Compteur Carte::getNbMinesAdjacentes(Position e_pos)
{
    Compteur compt = 0; // Initialisation du compteur de mines adjacentes
    int x = e_pos.ligne();
    int y = e_pos.colonne();
    Position pos(x, y);

    // parcourt des cases voisines(tableau 3x3) autour  de la case actuelle
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            pos.set_ligne(i);
            pos.set_colonne(j);

            // On verifie si la position est valide et que ce n'est pas la case elle-meme
            if (!(pos == e_pos) && estDansCarte(pos))
            {
                if (getCase(pos).estUneMine())
                {
                    compt++; // incremente le compteur si la case contient une mine
                }

            }
        }
    }
    return compt;  // Retourne le nombre total de mines adjacentes apres avoir parcouru toutes les cases voisines
}

// Description: Methode qui essaie d'ouvrir une case
// param[E] Position de la case
// retour : booleen - vrai si ce n'est pas une mine, faux sinon
// post : si la case a deja ete ouverte, ce n'est pas une mine -> retourne vrai, si la case n'est pas une mine, les cases voisines doivent etre ouvertes jusqu'a une prochaine mine

bool Carte::essaieCase(Position e_pos)
{
    // verifie si la case a la position e_pos est deja ouverte 
    if (getCase(e_pos).estOuverte())
    {
        return true;
    }
    // Vérifie si la case  a la position e_pos est une mine. 
    if (getCase(e_pos).estUneMine())
    {
        return false;
    }

    // ouvre la case a la position e_pos  si elle nest pas ouverte ni une mine
    ouvreCase(e_pos);

    //varaibles pour parcourir les cases djacentes
    int x = e_pos.ligne();
    int y = e_pos.colonne();
    Position posAdj(x, y); // position temporaire pour les cases voisines

    // Parcourt toutes les cases adjacentes (dans une grille 3x3 autour de la case actuelle).
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            posAdj.set_ligne(i);
            posAdj.set_colonne(j);

            // Verifie si la position adjacente est differente de la position actuelle 
        // et que lle se trouve dans la carte.
            if (!(e_pos == posAdj) && estDansCarte(posAdj))
            {
                if (estDansCarte(posAdj)) {
                    if (m_cases[x][y].estUneMine())
                    {
                        break;
                    }
                    essaieCase(posAdj);// appel recursive de la fonction essaieCase 
                }
            }
        }

    }
    return true;
};

// Description: Methode qui calcule le nombre de mines adjacentes pour les cases libres de la carte
// post : pour chacune des cases qui ne contient pas une mine, on compte le nombre de mines adjacentes
void Carte::compteMinesAdjParCase() {

    int coordLigne = nbLignes();
    int coordColonne = nbColonnes();

    // Initialise maposition par défaut
    Position maPosition(0, 0);
    Compteur  compt = 0; // variable pour stocker le nombre de mines adjacentes

    // Parcourt toutes les cases de la carte
    for (int i = 0; i < coordLigne; i++)
    {
        for (int j = 0; j < coordColonne; j++)
        {
            maPosition.set_ligne(i);
            maPosition.set_colonne(j);

            // Verifie si maposition est valide dans la carte et que la case ne contient  pas une mine
            if (estDansCarte(maPosition) && !m_cases[i][j].estUneMine())
            {
                compt = getNbMinesAdjacentes(maPosition); // Recupere le nombre de mines adjacentes a cette position

                // Incremente le compteur de la case autant de fois qu il y a de mines adjacentes
                for (int k = 0; k < compt; k++)
                {
                    m_cases[i][j].operator++(); // mettre a jour le compteur de la case 
                }
            }
        }
    }
}
