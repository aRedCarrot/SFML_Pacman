// PacMan.h
#ifndef _PACMAN_H
#define _PACMAN_H

#include "sdlclg.h"

// Déclarations de constantes requises pour le jeu
const int Largeur = 19;
const int Hauteur = 21;
const int NbPixelsParCase = 16;
const int VitesseFantome = 10; // Les fantômes bougent à tous les 10 tours de Pacman
// Ajoutez vos propres constantes ici...

// Énumération pour représenter une case du labyrinthe
// V=Vide, M=Mur, P=Point, PP=Pilule
enum Objet {V, M, P,PP};

// Ajoutez vos propres enum, structures et prototypes de fonctions ici...
enum MouvementFantome{Haut,Bas,Gauche,Droite};
struct Personnage
{
	int PosX;
	int PosY;
};
// Fonction pour verification ci-dessous
int PointsRestants(Objet Tableau[][Largeur]);
bool VerifierPerdu(Objet Tableau[][Largeur],Personnage PacMan,Personnage FantomeBleu,Personnage FantomeOrange,Personnage FantomeRouge,Personnage FantomeRose);
void VerifierMange(Objet Tableau[][Largeur], Personnage PacMan, Personnage &FantomeBleu, Personnage &FantomeOrange, Personnage &FantomeRouge, Personnage &FantomeRose);
void PowerPilule(Personnage &FantomeRouge, Personnage &FantomeRose,Personnage &FantomeBleu, Personnage &FantomeOrange, Objet Tableau[][Largeur], Personnage PacMan);
// Fonction pour l'audio ci-dessous
void JouerGameOver();
void JouerVictory();
void JouerMusique();
// Fonction pour l'affichage et mouvement ci-dessous
void BougerPacMan(Evenement ToucheEnfoncer, Objet Tableau[][Largeur], Personnage &PacMan);
void AfficherLabyrinthe(Objet Tableau[][Largeur],ImageId Point, ImageId Power,ImageId Board);
void BougerStupide(Personnage &FantomeBleu, Personnage &FantomeOrange, Objet Tableau[][Largeur], int &DernierMouvementBleu, int &DernierMouvementOrange);
void BougerChasseur(Personnage &FantomeRouge,Personnage &FantomeRose,Objet Tableau[][Largeur],Personnage PacMan);
void AfficherFantome(ImageId FantomeBleuID, ImageId FantomeOrangeID, ImageId FantomeRougeID, ImageId FantomeRoseID, Personnage FantomeBleu, Personnage FantomeOrange, Personnage FantomeRouge, Personnage FantomeRose);
#endif