// fichier : carte_.cpp
// auteur.es : MBADU NYANGI GRACE NEFERTITI , 
// date : 2020
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
    Position pos(x , y);

    // On parcourt les cases voisines
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            pos.set_ligne(i);
            pos.set_colonne(j);

            // On vérifie que la position est valide et que ce n'est pas la case elle-même
            if (!(pos == e_pos) && estDansCarte(pos))
            {
                 if (getCase(pos).estUneMine())
                 {
                        compt++; // On incrémente le compteur si la case contient une mine
                 }
                
            }
        }
    }
    return compt;  // Retourne le nombre total de mines adjacentes après avoir parcouru toutes les cases voisines
}

// Description: Methode qui essaie d'ouvrir une case
// param[E] Position de la case
// retour : booleen - vrai si ce n'est pas une mine, faux sinon
// post : si la case a deja ete ouverte, ce n'est pas une mine -> retourne vrai, si la case n'est pas une mine, les cases voisines doivent etre ouvertes jusqu'a une prochaine mine

bool Carte::essaieCase(Position e_pos)
{
    if (getCase(e_pos).estOuverte())
    {
        return true;
    }
    
    if (getCase(e_pos).estUneMine())
    {
        return false;
    }

    ouvreCase(e_pos);
    
        int x = e_pos.ligne();
        int y = e_pos.colonne();
        Position posAdj(x, y);
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                
                posAdj.set_ligne(i);
                posAdj.set_colonne(j);
                if (!(e_pos == posAdj) && estDansCarte(posAdj))
                {
                    if (estDansCarte(posAdj)) {
						if(m_cases[x][y].estUneMine())
						{
							break;
						}
                        essaieCase(posAdj);
                    }
                }
            }

        }
    
    return true;
};

// Description: Methode qui calcule le nombre de mines adjacentes pour les cases libres de la carte
// post : pour chacune des cases qui ne contient pas une mine, on compte le nombre de mines adjacentes

void Carte::compteMinesAdjParCase()
{
    int coordLigne = nbLignes();
    int coordColonne = nbColonnes();
    Position maPosition(0 , 0);
    Compteur  compt = 0;

    for (int i = 0; i < coordLigne; i++)
    {
        for (int j = 0; j < coordColonne; j++)
        {
            maPosition.set_ligne(i);
            maPosition.set_colonne(j);

            if (estDansCarte(maPosition) && !m_cases[i][j].estUneMine())
            {
                compt = getNbMinesAdjacentes(maPosition);

                for (int k = 0; k < compt; k++)
                {
                    m_cases[i][j].operator++();
                }
            }
        }
    }
}
