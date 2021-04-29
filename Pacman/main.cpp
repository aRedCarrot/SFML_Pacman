#include "sdlclg.h"
#include "PacMan.h"
#include <ctime>
#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;

int main(int argc, char *argv[])
{
	// Déclaration et initialisation du tableau 2D de jeu.
	// Ceci représente le tableau classique de Pacman
	Objet Tableau[Hauteur][Largeur]  =  
	{	
	{ M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
	{ M, PP, P, P, P, P, P, P, P, M, P, P, P, P, P, P, P, PP, M},
	{ M, P, M, M, P, M, M, M, P, M, P, M, M, M, P, M, M, P, M},
	{ M, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, M},
	{ M, P, M, M, P, M, P, M, M, M, M, M, P, M, P, M, M, P, M},
	{ M, P, P, P, P, M, P, P, P, M, P, P, P, M, P, P, P, P, M},
	{ M, M, M, M, P, M, M, M, V, M, V, M, M, M, P, M, M, M, M},
	{ V, V, V, M, P, M, V, V, V, V, V, V, V, M, P, M, V, V, V},
    { M, M, M, M, P, M, V, M, M, V, M, M, V, M, P, M, M, M, M}, 
	{ V, V, V, V, P, V, V, M, V, V, V, M, V, V, P, V, V, V, V},
	{ M, M, M, M, P, M, V, M, M, V, M, M, V, M, P, M, M, M, M},
	{ V, V, V, M, P, M, V, V, V, V, V, V, V, M, P, M, V, V, V},
	{ M, M, M, M, P, M, V, M, M, M, M, M, V, M, P, M, M, M, M},
	{ M, P, P, P, P, P, P, P, P, M, P, P, P, P, P, P, P, P, M},
	{ M, P, M, M, P, M, M, M, P, M, P, M, M, M, P, M, M, P, M}, 
	{ M, P, P, M, P, P, P, P, P, P, P, P, P, P, P, M, P, P, M}, 
	{ M, M, P, M, P, M, P, M, M, M, M, M, P, M, P, M, P, M, M},
	{ M, P, P, P, P, M, P, P, P, M, P, P, P, M, P, P, P, P, M},
	{ M, P, M, M, M, M, M, M, P, M, P, M, M, M, M, M, M, P, M},
	{ M, PP, P, P, P, P, P, P, P, P, P, P, P, P, P, P, P, PP, M},
	{ M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M}
	};
   // Creation de variable
   bool PPActif = false; // PowerPillule Actif
   int DernierMouvementBleu = 0; // Garde le dernier mouvement effectuer pour les fantomes bleu et orange
   int DernierMouvementOrange = 0;
   int CompteurFantome = 0; // Compteur pour effectuer un mouvement seulement a chaque 10 tour
   int CompteurMouvementPeur = 0;
   int Points;
   int CompteurPilule; // tour restant a la pillule ( dure 150 tour )
   bool DejaJouer = false; // Sert a jouer la musique principe si elle ne la pas deja ete
   bool VictoireParPoint = false;
   bool Perdu = false;
   Personnage PacMan; PacMan.PosX = 9; PacMan.PosY = 15;
   Personnage FantomeBleu; FantomeBleu.PosX = 9; FantomeBleu.PosY = 8; // bashful
   Personnage FantomeOrange; FantomeOrange.PosX = 9; FantomeOrange.PosY = 9; // Pokey
   Personnage FantomeRouge; FantomeRouge.PosX = 9; FantomeRouge.PosY = 10;// Shadow
   Personnage FantomeRose; FantomeRose.PosX = 9; FantomeRose.PosY = 11;// Speedy
   Evenement ToucheEnfoncer = EVDroite;
	// Initialisation du générateur de nombres aléatoires
	srand(static_cast<unsigned int>(time(0)));
	// Créer une fenêtre graphique de la bonne taille
	InitialiserAffichage("PacMan", Largeur*NbPixelsParCase, Hauteur*NbPixelsParCase); // 304 Largeur X 336 Hauteur
	// Charger les images 
	ImageId PacManID = ChargerImage("pacman.bmp");
	ImageId Point = ChargerImage("point.bmp");
	ImageId FantomeBleuID = ChargerImage("bashful.bmp");
	ImageId FantomeOrangeID = ChargerImage("Pokey.bmp");
	ImageId FantomeRougeID = ChargerImage("shadow.bmp");
	ImageId FantomeRoseID = ChargerImage("speedy.bmp");
	ImageId PeurID = ChargerImage("peur.bmp");
	ImageId Power = ChargerImage("power.bmp");
	ImageId Victoire = ChargerImage("gagne.bmp");
	ImageId GameOver = ChargerImage("perdu.bmp");
	ImageId TableauDeJeu = ChargerImage("board.bmp");
	// Boucle principale: jouer tant qu'il reste des points, que Pac Man est en vie et que l'usager n'a pas demandé de quitter
	while (VictoireParPoint != true && Perdu != true && ToucheEnfoncer != EVQuitter)
	{
       // Vérifier les points restants
       Points = PointsRestants(Tableau);
	   // Vérifier si Pac Man a été mangé ou PacMan mange
	   if (PPActif)
	   {
		   VerifierMange(Tableau, PacMan, FantomeBleu, FantomeOrange, FantomeRouge, FantomeRose);
	   }
	   else
	   {
		   Perdu = VerifierPerdu(Tableau, PacMan, FantomeBleu, FantomeOrange, FantomeRouge, FantomeRose);
	   }
		// Remplir la fenêtre de noir
		RemplirFenetre(0, 0, 0);
		// Afficher le labyrinthe (murs et points)
		AfficherLabyrinthe(Tableau, Point,Power,TableauDeJeu);
		// Afficher Pac Man
		AfficherImage(PacManID, PacMan.PosX*NbPixelsParCase, PacMan.PosY*NbPixelsParCase);
		// Afficher les fantomes
		if (PPActif)
		{
			AfficherFantome(PeurID, PeurID, PeurID, PeurID, FantomeBleu, FantomeOrange, FantomeRouge, FantomeRose);
		}
		else
		{
			AfficherFantome(FantomeBleuID, FantomeOrangeID, FantomeRougeID, FantomeRoseID, FantomeBleu, FantomeOrange, FantomeRouge, FantomeRose);
		}
		// Rafraichir la fenêtre
		RafraichirFenetre();
		// Attendre 30 ms pour ralentir le jeu  (délai à ajuster si nécessaire) et jouer la music principale si elle ne la pas deja ete
		Attendre(30);
		if (DejaJouer == false) // Jouer la music d'intro
		{
			JouerMusique();
			DejaJouer = true;
		}
		// Bouger Pac Man selon la touche appuyée
		ToucheEnfoncer = LireEvenement();
        BougerPacMan(ToucheEnfoncer,Tableau,PacMan);
		// Verifier si Pac Man a manger un point
		if (Tableau[PacMan.PosY][PacMan.PosX] == P)
		{
			Tableau[PacMan.PosY][PacMan.PosX] = V;
		}
		// Teste si une pilule est manger
		if (Tableau[PacMan.PosY][PacMan.PosX] == PP)
		{
			Tableau[PacMan.PosY][PacMan.PosX] = V;
			CompteurPilule = 150; // 150 tour de boucle
			PPActif = true;
		}
		if (PPActif == true) // Si mode PowerPillule est actif
		{
			CompteurMouvementPeur++;
			CompteurPilule--;
			if (CompteurMouvementPeur >= VitesseFantome) // Bouger les fantômes un tour sur 10 (à l'aide d'un compteur qui est remis à 0 une fois que les fantômes ont bougé)
			{
				PowerPilule(FantomeRouge, FantomeRose, FantomeBleu, FantomeOrange, Tableau, PacMan);
				if (CompteurPilule <= 0)
				{
					PPActif = false;
				}
				CompteurMouvementPeur = 0;
			}
		}
		// Bouger les fantômes un tour sur 10 (à l'aide d'un compteur qui est remis à 0 une fois que les fantômes ont bougé)
		else if (CompteurFantome > VitesseFantome)
		{
			BougerStupide(FantomeBleu, FantomeOrange,Tableau,DernierMouvementBleu,DernierMouvementOrange);
            BougerChasseur(FantomeRouge, FantomeRose, Tableau,PacMan);
			CompteurFantome = 0;
		}
		CompteurFantome++;
		// Afficher le bon message de fin de partie  
      if (Points == 0)
      {
         AfficherImage(Victoire, 7 * NbPixelsParCase, 8 * NbPixelsParCase);
         VictoireParPoint = true;
      }
	  if (Perdu)
	  {
		  AfficherImage(GameOver,7*NbPixelsParCase,8*NbPixelsParCase);
	  }
	}
// Commencer le processus de termination du jeux
	RafraichirFenetre();
	if (Perdu)
	{
		JouerGameOver();
	}
	if (VictoireParPoint)
	{
		JouerVictory();
	}
	Attendre(3000);
	QuitterAffichage();
	return 0;
}