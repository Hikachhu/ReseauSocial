#include "AllIncludes.h"

int main(int argc, char *argv[])
{
	int **Graphe=lecture(); //Initialise la matrice du graphe en fonction du fichier texte
	int TailleArc=NombreDArc(Graphe); //Recupère la quantité d'arc dans le graphe
	int Temps=0,SommetInformation[Taille]={0};
	printf("\n\n_____________________________________________________________________\n");
	printf("\nSimulation de la transmission d'une information dans un reseau social\n");
	printf("\nIl y a %d arcs dans ce graphe. Simulons la transmission d'une information\nayant pour origine le sommet A et pour arriver le sommet G\n",TailleArc);
	printf("Appuyez sur entree pour lancer la simulation\n");
	getchar(); //Attend l'appuie de la touche entrée
	Arc *ListeArc=SimpleAllocation(TailleArc); //*Initalise dynamique la liste des arcs en fonction de la quantité d'arc
	InitGraphic(); //Initisalise le fonctionnement du graphique
	Initialisation(ListeArc,TailleArc); //Insère les valeurs de début et de fin d'arc et initalise toutes les valeurs des arcs à 0
	AssociationPoid(Graphe,ListeArc); //Associe les poids des arcs enregistré dans le graphe à ceux du tableau d'arc
	AssociationSommet(Graphe,ListeArc,TailleArc); //Associe les sommets de début et de fin de chaque arc
	AffichageGraphic(ListeArc,TailleArc); //Affiche les primites du graphe, à savoir les sommets, les arcs, les directions des arcs ainsi que les noms des sommets
	SommetInformation[0]=1; //Sommet de départ de l'information
	while(TotalInformation(SommetInformation,Taille)!=0){ //Tant que chaque sommet n'a pas reçu l'information
		Temps++;//Augmente l'étape
		for (int i = 0; i < Taille; i++){ //Pour chaque sommet i
			if(SommetInformation[i]!=0){// Si ce sommet possède l'information
				for (int j = 0; j < Taille; j++){//Pour chaque sommet j
					if(Graphe[i][j]!=0){//Si les sommets i et j sont connectés
						if(SommetInformation[j]==0){//Si le sommet j ne possède pas l'information
							if(ListeArc[TrouveArc(ListeArc,TailleArc,i,j)].Progression!=ListeArc[TrouveArc(ListeArc,TailleArc,i,j)].Poid){// Si la progression de l'arc est différentes de son poid
								ListeArc[TrouveArc(ListeArc,TailleArc,i,j)].Progression++;//Augmente sa progression
								SegmentProgression(ListeArc[TrouveArc(ListeArc,TailleArc,i,j)],ListeArc[TrouveArc(ListeArc,TailleArc,i,j)].Progression);//Affiche la progression dynamiquement
							}
							else if(SommetInformation[j]==0){//Si le sommet ne possède pas encore l'information
								SommetInformation[j]=1;//Donne l'information au sommet
							}
						}
					}
				}
			}
		}
		sleep(1);//Pause d'une seconde
	}
	Dijkstra(Graphe);//Donne les information de chemin issu du chemin de Dijkstra
	sleep(10);
  	closegraph();//Ferme la fenetre
	liberation(ListeArc,TailleArc);//Libère le tableau d'arc
	return 0;
}