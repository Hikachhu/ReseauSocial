#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graphics.h"
#define TailleCercle 40
#define Taille 7

struct Arc{
	int SommetDeDepart;
	int SommetArrive;
	int Poid;
	int Progression;
	int XDebut;
	int YDebut;
	int YFin;
	int XFin;

};

typedef struct Arc Arc;

void liberation(Arc *ListeArc,int taille);
Arc *SimpleAllocation(int tailleArc);
int NombreDArc(int **Graphe);
void AssociationPoid(int **Graphe,Arc *ListeArc);
void AffichageArc(Arc *ListeArc,int TailleArc);
int TotalInformation(int *SommetInformation,int taille);
void Initialisation(Arc *ListeArc,int TailleArc);
void AssociationSommet(int **Graphe,Arc *ListeArc,int TailleArc);
int TrouveArc(Arc *ListeArc,int TailleArc,int Debut,int Fin);
void InitGraphic();
void StopGraphic();
void AffichageGraphic(Arc *ListeArc,int TailleArc);
void SegmentProgression(Arc Actuel,int Progression);

void CopieLigne(int DistanceEnCours[Taille][Taille],int Actuel);
void AfficheListeDistance(int DistanceEnCours[Taille][Taille],int OrdreSommet[Taille]);
int PlusPetit(int Tab[Taille],int DistanceFinal[Taille]);
int NombreDispo(int Dispo[Taille]);
int SuivantDispo(int Dispo[Taille],int OrdreSommet[Taille]);
void Dijkstra(int **Matrice);

void ListeSommet(FILE *fichier,int **tab);
int **lecture();