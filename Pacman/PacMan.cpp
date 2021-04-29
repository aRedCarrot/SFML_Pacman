#include "PacMan.h"
#include "sdlclg.h"
#include <SFML/Audio.hpp>
#include <iostream>
void BougerPacMan(Evenement ToucheEnfoncer, Objet Tableau[][Largeur], Personnage &PacMan)
{
   if (ToucheEnfoncer == EVDroite)
   {
      PacMan.PosX++;
	  // Teleporteur de Droite
	  if (PacMan.PosX == Largeur)
	  {
		  PacMan.PosX = 0;
	  }
	  // Empeche de entrer dans un mur
      if (Tableau[PacMan.PosY][PacMan.PosX] == M)
      {
         PacMan.PosX--;
      }
   }
   if (ToucheEnfoncer == EVGauche)
   {
      PacMan.PosX--;
	  // Teleporteur de Gauche
	  if (PacMan.PosX < 0)
	  {
		  PacMan.PosX = Largeur-1;
	  }
	  // Empeche de entrer dans un mur
      if (Tableau[PacMan.PosY][PacMan.PosX] == M)
      {
         PacMan.PosX++;
      }
   }
   if (ToucheEnfoncer == EVBas)
   {
      PacMan.PosY++;
	  // Empeche de entrer dans un mur
      if (Tableau[PacMan.PosY][PacMan.PosX] == M)
      {
         PacMan.PosY--;
      }
   }
   if (ToucheEnfoncer == EVHaut)
   {
      PacMan.PosY--;
	  // Empeche de entrer dans un mur
      if (Tableau[PacMan.PosY][PacMan.PosX] == M)
      {
         PacMan.PosY++;
      }
   }
}

void AfficherLabyrinthe(Objet Tableau[][Largeur], ImageId Point,ImageId Power, ImageId Board)
{
   int CompteurX;
   int CompteurY;
   AfficherImage(Board, 8, 5);
   for (CompteurX = 0; CompteurX <= Largeur; CompteurX++)
   {
      for (CompteurY = 0; CompteurY <= Hauteur; CompteurY++)
      {
         if (Tableau[CompteurY][CompteurX] == P)
         {
            AfficherImage(Point, CompteurX*NbPixelsParCase, CompteurY*NbPixelsParCase);
         }
		 if (Tableau[CompteurY][CompteurX] == PP)
		 {
			 AfficherImage(Power, CompteurX*NbPixelsParCase, CompteurY*NbPixelsParCase);
		 }
      }
   }
}

int PointsRestants(Objet Tableau[][Largeur])
{
   int PointRestant = 0;
   int CompteurX;
   int CompteurY;
   for (CompteurX = 0; CompteurX <= Largeur; CompteurX++)
   {
      for (CompteurY = 0; CompteurY <= Hauteur; CompteurY++)
      {
         if (Tableau[CompteurY][CompteurX] == P)
         {
            PointRestant++;
         }
      }
   }
   return PointRestant;
}

void JouerMusique()
{
	// Jouer la music principale avant le debut du jeux
	sf::SoundBuffer Music;
	if (!Music.loadFromFile("Intro.ogg"))
	{
		std::cout << "Erreur lors du chargement de la music" << std::endl;
	}
	sf::Sound Musique;

	Musique.setBuffer(Music);
	Musique.setVolume(50);
	Musique.play();

	Attendre(4500);
	Musique.stop();
}

void BougerStupide(Personnage &FantomeBleu, Personnage &FantomeOrange,Objet Tableau[][Largeur],int &DernierMouvementBleu,int &DernierMouvementOrange)
{
	// 0 = Haut ; 1 = Bas ; 2 = Gauche ; 3 = Droite

	int Chiffre;
	bool MouvementBleu = false;
	bool MouvementOrange = false;
	bool BloqueHaut = false;
	bool BloqueGauche = false;
	bool BloqueDroite = false;
	bool BloqueBas = false;
	int CompteurGauche = 0;
	int CompteurDroite = 0;
	do
	{
		do
		{
			Chiffre = (rand() % 4);
		} while (Chiffre == DernierMouvementBleu);
		if (Chiffre == Haut)
		{
			FantomeBleu.PosY--;
			if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
			{
				FantomeBleu.PosY++;
				BloqueHaut = true;
			}
			else
			{
				MouvementBleu = true;
				DernierMouvementBleu = Bas;
			}
		}
		if (Chiffre == Bas)
		{
			FantomeBleu.PosY++;
			if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
			{
				FantomeBleu.PosY--;
				BloqueBas = true;
			}
			else
			{
				MouvementBleu = true;
				DernierMouvementBleu = Haut;
			}
		}
		if (Chiffre == Gauche)
		{
			FantomeBleu.PosX--;
			// Teleporteur de Gauche
			if (FantomeBleu.PosX < 0)
			{
				FantomeBleu.PosX = Largeur - 1;
			}
				if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
				{
					FantomeBleu.PosX++;
					BloqueGauche = true;
				}
				else
				{
					MouvementBleu = true;
					DernierMouvementBleu = Droite;
				}
		}
		if (Chiffre == Droite)
		{
			FantomeBleu.PosX++;
			// Teleporteur de droite
			if (FantomeBleu.PosX == Largeur)
			{
				FantomeBleu.PosX = 0;
			}
				if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
				{
					FantomeBleu.PosX--;
					BloqueDroite = true;
				}
				else
				{
					MouvementBleu = true;
					DernierMouvementBleu = Gauche;
				}
		}

		// Si bloque dans le tableau a gauche

		if ((BloqueGauche == true) && (BloqueBas == true) && (BloqueHaut == true) && (FantomeBleu.PosX < 9))
		{
			DernierMouvementBleu = Gauche;
			BloqueGauche = false; BloqueBas = false; BloqueHaut = false; BloqueDroite = false;
		}

		// Si bloque dans le tableau a droite

		if ((BloqueDroite == true) && (BloqueBas == true) && (BloqueHaut == true) && (FantomeBleu.PosX > 9))
		{
			DernierMouvementBleu = Droite;
			BloqueDroite = false; BloqueBas = false; BloqueHaut = false; BloqueGauche = false;
		}

	} while (MouvementBleu == false);
	////////// Fantome Orange
	do
	{
		do
		{
			Chiffre = (rand() % 4);
		} while (Chiffre == DernierMouvementOrange);
		if (Chiffre == Haut)
		{
			FantomeOrange.PosY--;
			if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
			{
				FantomeOrange.PosY++;
				BloqueHaut = true;
			}
			else
			{
				MouvementOrange = true;
				DernierMouvementOrange = Bas;
			}
		}
		if (Chiffre == Bas)
		{
			FantomeOrange.PosY++;
			if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
			{
				FantomeOrange.PosY--;
				BloqueBas = true;
			}
			else
			{
				MouvementOrange = true;
				DernierMouvementOrange = Haut;
			}
		}
		if (Chiffre == Gauche)
		{
			FantomeOrange.PosX--;
			// Teleporteur de Gauche
			if (FantomeOrange.PosX < 0)
			{
				FantomeOrange.PosX = Largeur - 1;
			}
				if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
				{
					FantomeOrange.PosX++;
					BloqueGauche = true;
				}
				else
				{
					MouvementOrange = true;
					DernierMouvementOrange = Droite;
				}
		}
		if (Chiffre == Droite)
		{
			FantomeOrange.PosX++;
			// Teleporteur de droite
			if (FantomeOrange.PosX == Largeur)
			{
				FantomeOrange.PosX = 0;
			}
				if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
				{
					FantomeOrange.PosX--;
					BloqueDroite = true;
				}
				else
				{
					MouvementOrange = true;
					DernierMouvementOrange = Gauche;
				}
		}

		// Si bloque dans le tableau a gauche

		if ((BloqueGauche == true) && (BloqueBas == true) && (BloqueHaut == true) && (FantomeOrange.PosX < 9))
		{
			DernierMouvementOrange = Gauche;
			BloqueGauche = false; BloqueBas = false; BloqueHaut = false; BloqueDroite = false;
		}

		// Si bloque dans le tableau a droite

		if ((BloqueDroite == true) && (BloqueBas == true) && (BloqueHaut == true) && (FantomeOrange.PosX > 9))
		{
			DernierMouvementOrange = Droite;
			BloqueDroite = false; BloqueBas = false; BloqueHaut = false; BloqueGauche = false;
		}

	} while (MouvementOrange == false);
}

void BougerChasseur(Personnage &FantomeRouge, Personnage &FantomeRose, Objet Tableau[][Largeur], Personnage PacMan)
{
	bool MouvementCompleterRouge = false;
	int MouvementRouge;
	bool RandOKRouge = false; // sert a s assurer que un mouvement a ete effectuer apres le rand si le fantome est pris
	bool MouvementCompleterRose = false;
	int MouvementRose;
	bool RandOKRose = false;


	/////////////////////////////////// FANTOME ROUGE //////////////////////////////////////////////////////////////////////////////////////////

	if (FantomeRouge.PosX >= 15 && FantomeRouge.PosY == 9 && PacMan.PosX <= 3 && PacMan.PosY == 9) // Teleporteur si PacMan est a gauche
	{
		FantomeRouge.PosX++;
		if (FantomeRouge.PosX >= Largeur)
		{
			FantomeRouge.PosX = 0;
		}
		MouvementCompleterRouge = true;
	}
	else if (FantomeRouge.PosX >= 15 && FantomeRouge.PosY == 9 && PacMan.PosX <= 3 && PacMan.PosY == 9) // Teleporteur si PacMan est a droite
	{
		FantomeRouge.PosX--;
		if (FantomeRouge.PosX < 0)
		{
			FantomeRouge.PosX = Largeur - 1;
		}
		MouvementCompleterRouge = true;
	}
	else if ( MouvementCompleterRouge == false)
	{
		if (PacMan.PosX < FantomeRouge.PosX) // PacMan est a gauche
		{
			FantomeRouge.PosX--;
			MouvementCompleterRouge = true;
			if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
			{
				FantomeRouge.PosX++;
				MouvementCompleterRouge = false;
			}
		}
		if (PacMan.PosX > FantomeRouge.PosX && MouvementCompleterRouge == false) // PacMan est a droite
		{
			FantomeRouge.PosX++;
			MouvementCompleterRouge = true;
			if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
			{
				FantomeRouge.PosX--;
				MouvementCompleterRouge = false;
			}
		}
		if (PacMan.PosY < FantomeRouge.PosY && MouvementCompleterRouge == false) // PacMan est plus haut
		{
			FantomeRouge.PosY--;
			MouvementCompleterRouge = true;
			if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
			{
				FantomeRouge.PosY++;
				MouvementCompleterRouge = false;
			}
		}
		if (PacMan.PosY > FantomeRouge.PosY && MouvementCompleterRouge == false) // PacMan est plus bas
		{
			FantomeRouge.PosY++;
			MouvementCompleterRouge = true;
			if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
			{
				FantomeRouge.PosY--;
				MouvementCompleterRouge = false;
			}
		}

		if (MouvementCompleterRouge == false)
		{
			do
			{
				MouvementRouge = rand() % 4;
				if (MouvementRouge == Haut)
				{
					FantomeRouge.PosY--;
					RandOKRouge = true;
					if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
					{
						FantomeRouge.PosY++;
						RandOKRouge = false;
					}
				}
				if (MouvementRouge == Bas)
				{
					FantomeRouge.PosY++;
					RandOKRouge = true;
					if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
					{
						FantomeRouge.PosY--;
						RandOKRouge = false;
					}
				}
				if (MouvementRouge == Gauche)
				{
					FantomeRouge.PosX--;
					RandOKRouge = true;
					if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
					{
						FantomeRouge.PosX++;
						RandOKRouge = false;
					}
				}
				if (MouvementRouge == Droite)
				{
					FantomeRouge.PosX++;
					RandOKRouge = true;
					if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
					{
						FantomeRouge.PosX--;
						RandOKRouge = false;
					}
				}
			} while (RandOKRouge != true);
		}
	}
	////////////////////////////// FANTOME ROSE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (FantomeRose.PosX >= 15 && FantomeRose.PosY == 9 && PacMan.PosX <= 3 && PacMan.PosY == 9) // Teleporteur si PacMan est a gauche
	{
		FantomeRose.PosX++;
		if (FantomeRose.PosX >= Largeur)
		{
			FantomeRose.PosX = 0;
		}
		MouvementCompleterRose = true;
	}
	else if (FantomeRose.PosX >= 15 && FantomeRose.PosY == 9 && PacMan.PosX <= 3 && PacMan.PosY == 9) // Teleporteur si PacMan est a droite
	{
		FantomeRose.PosX--;
		if (FantomeRose.PosX < 0)
		{
			FantomeRose.PosX = Largeur - 1;
		}
		MouvementCompleterRose = true;
	}
	else if (MouvementCompleterRose == false)
	{
		if (PacMan.PosX < FantomeRose.PosX) // PacMan est a gauche
		{
			FantomeRose.PosX--;
			MouvementCompleterRose = true;
			if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
			{
				FantomeRose.PosX++;
				MouvementCompleterRose = false;
			}
		}
		if (PacMan.PosX > FantomeRose.PosX && MouvementCompleterRose == false) // PacMan est a droite
		{
			FantomeRose.PosX++;
			MouvementCompleterRose = true;
			if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
			{
				FantomeRose.PosX--;
				MouvementCompleterRose = false;
			}
		}
		if (PacMan.PosY < FantomeRose.PosY && MouvementCompleterRose == false) // PacMan est plus haut
		{
			FantomeRose.PosY--;
			MouvementCompleterRose = true;
			if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
			{
				FantomeRose.PosY++;
				MouvementCompleterRose = false;
			}
		}
		if (PacMan.PosY > FantomeRose.PosY && MouvementCompleterRose == false) // PacMan est plus bas
		{
			FantomeRose.PosY++;
			MouvementCompleterRose = true;
			if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
			{
				FantomeRose.PosY--;
				MouvementCompleterRose = false;
			}
		}

		if (MouvementCompleterRose == false)
		{
			do
			{
				MouvementRose = rand() % 4;
				if (MouvementRose == Haut)
				{
					FantomeRose.PosY--;
					RandOKRose = true;
					if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
					{
						FantomeRose.PosY++;
						RandOKRose = false;
					}
				}
				if (MouvementRose == Bas)
				{
					FantomeRose.PosY++;
					RandOKRose = true;
					if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
					{
						FantomeRose.PosY--;
						RandOKRose = false;
					}
				}
				if (MouvementRose == Gauche)
				{
					FantomeRose.PosX--;
					RandOKRose = true;
					if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
					{
						FantomeRose.PosX++;
						RandOKRose = false;
					}
				}
				if (MouvementRose == Droite)
				{
					FantomeRose.PosX++;
					RandOKRose = true;
					if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
					{
						FantomeRose.PosX--;
						RandOKRose = false;
					}
				}
			} while (RandOKRose != true);
		}
	}
}

void AfficherFantome(ImageId FantomeBleuID, ImageId FantomeOrangeID, ImageId FantomeRougeID, ImageId FantomeRoseID, Personnage FantomeBleu, Personnage FantomeOrange, Personnage FantomeRouge, Personnage FantomeRose)
{
	AfficherImage(FantomeBleuID, FantomeBleu.PosX*NbPixelsParCase, FantomeBleu.PosY*NbPixelsParCase);
	AfficherImage(FantomeOrangeID, FantomeOrange.PosX*NbPixelsParCase, FantomeOrange.PosY*NbPixelsParCase);
	AfficherImage(FantomeRougeID, FantomeRouge.PosX*NbPixelsParCase, FantomeRouge.PosY*NbPixelsParCase);
	AfficherImage(FantomeRoseID, FantomeRose.PosX*NbPixelsParCase, FantomeRose.PosY*NbPixelsParCase);
}

bool VerifierPerdu(Objet Tableau[][Largeur], Personnage PacMan, Personnage FantomeBleu, Personnage FantomeOrange, Personnage FantomeRouge, Personnage FantomeRose)
{
	bool Perdu = false;
	if ((Tableau[PacMan.PosX] == Tableau[FantomeBleu.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeBleu.PosY]))
	{
		Perdu = true;
	}
	else if ((Tableau[PacMan.PosX] == Tableau[FantomeOrange.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeOrange.PosY]))
	{
		Perdu = true;
	}
	else if ((Tableau[PacMan.PosX] == Tableau[FantomeRouge.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeRouge.PosY]))
	{
		Perdu = true;
	}
	else if ((Tableau[PacMan.PosX] == Tableau[FantomeRose.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeRose.PosY]))
	{
		Perdu = true;
	}
	return Perdu;
}

void JouerGameOver()
{
		// Jouer la musique quand le joueur perd
		sf::SoundBuffer Music;
		if (!Music.loadFromFile("GameOver.ogg"))
		{
			std::cout << "Erreur lors du chargement de la music" << std::endl;
		}
		sf::Sound Musique;

		Musique.setBuffer(Music);
		Musique.setVolume(50);
		Musique.play();

		Attendre(2000);
}

void JouerVictory()
{
	// Jouer la musique quand le joueur gagne
	sf::SoundBuffer Music;
	if (!Music.loadFromFile("Victory.ogg"))
	{
		std::cout << "Erreur lors du chargement de la music" << std::endl;
	}
	sf::Sound Musique;

	Musique.setBuffer(Music);
	Musique.setVolume(50);
	Musique.play();

	Attendre(4000);
	Musique.stop();
}

void PowerPilule(Personnage &FantomeRouge, Personnage &FantomeRose, Personnage &FantomeBleu, Personnage &FantomeOrange, Objet Tableau[][Largeur], Personnage PacMan)
{
	bool MouvementCompleterBleu = false;
	int MouvementBleu;
	bool RandOKBleu = false;
	bool MouvementCompleterOrange = false;
	int MouvementOrange;
	bool RandOKOrange = false;
	bool MouvementCompleterRouge = false;
	int MouvementRouge;
	bool RandOKRouge = false; // sert a s assurer que un mouvement a ete effectuer apres le rand si le fantome est pris
	bool MouvementCompleterRose = false;
	int MouvementRose;
	bool RandOKRose = false;


	/////////////////////////////////// FANTOME ROUGE //////////////////////////////////////////////////////////////////////////////////////////

	if (PacMan.PosX < FantomeRouge.PosX) // PacMan est a gauche
	{
		FantomeRouge.PosX++;
		MouvementCompleterRouge = true;
		if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
		{
			FantomeRouge.PosX--;
			MouvementCompleterRouge = false;
		}
	}
	if (PacMan.PosX > FantomeRouge.PosX && MouvementCompleterRouge == false) // PacMan est a droite
	{
		FantomeRouge.PosX--;
		MouvementCompleterRouge = true;
		if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
		{
			FantomeRouge.PosX++;
			MouvementCompleterRouge = false;
		}
	}
	if (PacMan.PosY < FantomeRouge.PosY && MouvementCompleterRouge == false) // PacMan est plus haut
	{
		FantomeRouge.PosY++;
		MouvementCompleterRouge = true;
		if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
		{
			FantomeRouge.PosY--;
			MouvementCompleterRouge = false;
		}
	}
	if (PacMan.PosY > FantomeRouge.PosY && MouvementCompleterRouge == false) // PacMan est plus bas
	{
		FantomeRouge.PosY--;
		MouvementCompleterRouge = true;
		if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
		{
			FantomeRouge.PosY++;
			MouvementCompleterRouge = false;
		}
	}

	if (MouvementCompleterRouge == false)
	{
		do
		{
			MouvementRouge = rand() % 4;
			if (MouvementRouge == Haut)
			{
				FantomeRouge.PosY--;
				RandOKRouge = true;
				if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
				{
					FantomeRouge.PosY++;
					RandOKRouge = false;
				}
			}
			if (MouvementRouge == Bas)
			{
				FantomeRouge.PosY++;
				RandOKRouge = true;
				if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
				{
					FantomeRouge.PosY--;
					RandOKRouge = false;
				}
			}
			if (MouvementRouge == Gauche)
			{
				FantomeRouge.PosX--;
				RandOKRouge = true;
				if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
				{
					FantomeRouge.PosX++;
					RandOKRouge = false;
				}
			}
			if (MouvementRouge == Droite)
			{
				FantomeRouge.PosX++;
				RandOKRouge = true;
				if (Tableau[FantomeRouge.PosY][FantomeRouge.PosX] == M)
				{
					FantomeRouge.PosX--;
					RandOKRouge = false;
				}
			}
		} while (RandOKRouge != true);
	}
	////////////////////////////// FANTOME ROSE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (PacMan.PosX < FantomeRose.PosX) // PacMan est a gauche
	{
		FantomeRose.PosX++;
		MouvementCompleterRose = true;
		if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
		{
			FantomeRose.PosX--;
			MouvementCompleterRose = false;
		}
	}
	if (PacMan.PosX > FantomeRose.PosX && MouvementCompleterRose == false) // PacMan est a droite
	{
		FantomeRose.PosX--;
		MouvementCompleterRose = true;
		if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
		{
			FantomeRose.PosX++;
			MouvementCompleterRose = false;
		}
	}
	if (PacMan.PosY < FantomeRose.PosY && MouvementCompleterRose == false) // PacMan est plus haut
	{
		FantomeRose.PosY++;
		MouvementCompleterRose = true;
		if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
		{
			FantomeRose.PosY--;
			MouvementCompleterRose = false;
		}
	}
	if (PacMan.PosY > FantomeRose.PosY && MouvementCompleterRose == false) // PacMan est plus bas
	{
		FantomeRose.PosY--;
		MouvementCompleterRose = true;
		if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
		{
			FantomeRose.PosY++;
			MouvementCompleterRose = false;
		}
	}

	if (MouvementCompleterRose == false)
	{
		do
		{
			MouvementRose = rand() % 4;
			if (MouvementRose == Haut)
			{
				FantomeRose.PosY--;
				RandOKRose = true;
				if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
				{
					FantomeRose.PosY++;
					RandOKRose = false;
				}
			}
			if (MouvementRose == Bas)
			{
				FantomeRose.PosY++;
				RandOKRose = true;
				if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
				{
					FantomeRose.PosY--;
					RandOKRose = false;
				}
			}
			if (MouvementRose == Gauche)
			{
				FantomeRose.PosX--;
				RandOKRose = true;
				if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
				{
					FantomeRose.PosX++;
					RandOKRose = false;
				}
			}
			if (MouvementRose == Droite)
			{
				FantomeRose.PosX++;
				RandOKRose = true;
				if (Tableau[FantomeRose.PosY][FantomeRose.PosX] == M)
				{
					FantomeRose.PosX--;
					RandOKRose = false;
				}
			}
		} while (RandOKRose != true);
	}
	////////////////////////////// FANTOME BLEU ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (PacMan.PosX < FantomeBleu.PosX) // PacMan est a gauche
	{
		FantomeBleu.PosX++;
		MouvementCompleterBleu = true;
		if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
		{
			FantomeBleu.PosX--;
			MouvementCompleterBleu = false;
		}
	}
	if (PacMan.PosX > FantomeBleu.PosX && MouvementCompleterBleu == false) // PacMan est a droite
	{
		FantomeBleu.PosX--;
		MouvementCompleterBleu = true;
		if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
		{
			FantomeBleu.PosX++;
			MouvementCompleterBleu = false;
		}
	}
	if (PacMan.PosY < FantomeBleu.PosY && MouvementCompleterBleu == false) // PacMan est plus haut
	{
		FantomeBleu.PosY++;
		MouvementCompleterBleu = true;
		if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
		{
			FantomeBleu.PosY--;
			MouvementCompleterBleu = false;
		}
	}
	if (PacMan.PosY > FantomeBleu.PosY && MouvementCompleterBleu == false) // PacMan est plus bas
	{
		FantomeBleu.PosY--;
		MouvementCompleterBleu = true;
		if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
		{
			FantomeBleu.PosY++;
			MouvementCompleterBleu = false;
		}
	}

	if (MouvementCompleterBleu == false)
	{
		do
		{
			MouvementBleu = rand() % 4;
			if (MouvementBleu == Haut)
			{
				FantomeBleu.PosY--;
				RandOKBleu = true;
				if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
				{
					FantomeBleu.PosY++;
					RandOKBleu = false;
				}
			}
			if (MouvementBleu == Bas)
			{
				FantomeBleu.PosY++;
				RandOKBleu = true;
				if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
				{
					FantomeBleu.PosY--;
					RandOKBleu = false;
				}
			}
			if (MouvementBleu == Gauche)
			{
				FantomeBleu.PosX--;
				RandOKBleu = true;
				if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
				{
					FantomeBleu.PosX++;
					RandOKBleu = false;
				}
			}
			if (MouvementBleu == Droite)
			{
				FantomeBleu.PosX++;
				RandOKBleu = true;
				if (Tableau[FantomeBleu.PosY][FantomeBleu.PosX] == M)
				{
					FantomeBleu.PosX--;
					RandOKBleu = false;
				}
			}
		} while (RandOKBleu != true);
	}
	////////////////////////////// FANTOME ORANGE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (PacMan.PosX < FantomeOrange.PosX) // PacMan est a gauche
	{
		FantomeOrange.PosX++;
		MouvementCompleterOrange = true;
		if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
		{
			FantomeOrange.PosX--;
			MouvementCompleterOrange = false;
		}
	}
	if (PacMan.PosX > FantomeOrange.PosX && MouvementCompleterOrange == false) // PacMan est a droite
	{
		FantomeOrange.PosX--;
		MouvementCompleterOrange = true;
		if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
		{
			FantomeOrange.PosX++;
			MouvementCompleterOrange = false;
		}
	}
	if (PacMan.PosY < FantomeOrange.PosY && MouvementCompleterOrange == false) // PacMan est plus haut
	{
		FantomeOrange.PosY++;
		MouvementCompleterOrange = true;
		if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
		{
			FantomeOrange.PosY--;
			MouvementCompleterOrange = false;
		}
	}
	if (PacMan.PosY > FantomeOrange.PosY && MouvementCompleterOrange == false) // PacMan est plus bas
	{
		FantomeOrange.PosY--;
		MouvementCompleterOrange = true;
		if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
		{
			FantomeOrange.PosY++;
			MouvementCompleterOrange = false;
		}
	}

	if (MouvementCompleterOrange == false)
	{
		do
		{
			MouvementOrange = rand() % 4;
			if (MouvementOrange == Haut)
			{
				FantomeOrange.PosY--;
				RandOKOrange = true;
				if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
				{
					FantomeOrange.PosY++;
					RandOKOrange = false;
				}
			}
			if (MouvementOrange == Bas)
			{
				FantomeOrange.PosY++;
				RandOKOrange = true;
				if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
				{
					FantomeOrange.PosY--;
					RandOKOrange = false;
				}
			}
			if (MouvementOrange == Gauche)
			{
				FantomeOrange.PosX--;
				RandOKOrange = true;
				if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
				{
					FantomeOrange.PosX++;
					RandOKOrange = false;
				}
			}
			if (MouvementOrange == Droite)
			{
				FantomeOrange.PosX++;
				RandOKOrange = true;
				if (Tableau[FantomeOrange.PosY][FantomeOrange.PosX] == M)
				{
					FantomeOrange.PosX--;
					RandOKOrange = false;
				}
			}
		} while (RandOKOrange != true);
	}
}

void VerifierMange(Objet Tableau[][Largeur], Personnage PacMan, Personnage &FantomeBleu, Personnage &FantomeOrange, Personnage &FantomeRouge, Personnage &FantomeRose)
{
	if ((Tableau[PacMan.PosX] == Tableau[FantomeBleu.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeBleu.PosY]))
	{
		FantomeBleu.PosX = 9; FantomeBleu.PosY = 9;
	}
	if ((Tableau[PacMan.PosX] == Tableau[FantomeOrange.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeOrange.PosY]))
	{
		FantomeOrange.PosX = 9; FantomeOrange.PosY = 9;
	}
	if ((Tableau[PacMan.PosX] == Tableau[FantomeRouge.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeRouge.PosY]))
	{
		FantomeRouge.PosX = 9; FantomeRouge.PosY = 9;
	}
	if ((Tableau[PacMan.PosX] == Tableau[FantomeRose.PosX]) && (Tableau[PacMan.PosY] == Tableau[FantomeRose.PosY]))
	{
		FantomeRose.PosX = 9; FantomeRose.PosY = 9;
	}
}