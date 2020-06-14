#include "AllIncludes.h"

/*Copie une ligne sur la ligne d'en dessous*/
void CopieLigne(int DistanceEnCours[TailleMatrice][TailleMatrice],int Actuel){
	for (int i = 0; i < TailleMatrice; i++)
	{	
		DistanceEnCours[Actuel+1][i]=DistanceEnCours[Actuel][i];
	}
}

/*Afficage de la matrice avec l'ensemble des distances historiquement*/
void AfficheListeDistance(int DistanceEnCours[TailleMatrice][TailleMatrice],int OrdreSommet[TailleMatrice]){
	for (int i = 0; i < TailleMatrice; i++)
	{
		printf("%c :",OrdreSommet[i]+'A');/*Affiche le sommet */
		for (int j = 0; j <TailleMatrice ; j++)
		{
			printf("%2d ",DistanceEnCours[i][j]);		
		}
		printf("\n");
	}
}

int PlusPetit(int Tab[TailleMatrice],int DistanceFinal[TailleMatrice]){
/*Trouve le nombre la valeur la plus petite parmis celles disponible sur la ligne et renvoi son index*/ 
	int p=100,index=0;
	for (int i = 0; i < TailleMatrice; i++)
	{	
		if(p>Tab[i]&&Tab[i]>0&&DistanceFinal[i]==-1){p=Tab[i];index=i;}
	}
	return index;
}

/*Renvoi 1 si toute les valeur du tableau son différentes de 0*/
int NombreDispo(int Dispo[TailleMatrice]){
	for (int i = 0; i < TailleMatrice; i++)
	{
		if(Dispo[i]==0){
			return 0;
		}
	}
	return 1;
}

/*Donne le sommet suivant à traiter */
int SuivantDispo(int Dispo[TailleMatrice],int OrdreSommet[TailleMatrice]){
	for (int i =TailleMatrice-1; i !=0; i--)
	{
		if(Dispo[OrdreSommet[i]]==0)
			return OrdreSommet[i];
	}
	return -1;
}

void Dijkstra(int **Matrice){

	int DistanceEnCours[Taille][Taille];
	int DistanceFinal[Taille];
	int OrdreSommet[Taille];
	int SommetDeDepart;
	for (int i = 0; i < Taille; i++){
		DistanceFinal[i]=-1;
		for (int j = 0; j < Taille; j++){
			DistanceEnCours[i][j]=-1;
		}
	}
	int SommetActuel,a,i,j;
	SommetActuel=0;
	SommetDeDepart=SommetActuel;
	DistanceFinal[SommetActuel]=0;
	for (a = 0; a < TailleMatrice; a++){/*Pour tout les sommets*/
		for(i=0;i<TailleMatrice;i++){/*Pour toutes ses correspondances*/
			OrdreSommet[a]=SommetActuel;/*Permet de retenir l'ordre des sommets dans lequels nous les traitons*/
			if(Matrice[SommetActuel][i]!=0&&DistanceFinal[i]==-1){/*Si il y a correspondance entre le sommet actuel et un autre ET que l'autre sommet n'a pas été traité*/
				if(DistanceEnCours[a][i]==-1){/*Si Nous n'avons jamais donné de valeur pour la distance entre les 2 sommets*/
					DistanceEnCours[a][i]=Matrice[SommetActuel][i]+DistanceFinal[SommetActuel];/*La distance entre le point d'origine et le sommet selectionné= entre sommet actuel et sommet selectionné + distance pour arriver au sommet actuel*/
				}
				else{/*Sinon*/ 
					if((Matrice[SommetActuel][i]+DistanceFinal[SommetActuel])<DistanceEnCours[a][i])/*Si Il y a deja une valeur nous choissons le plus court chemin pour arriver au sommet selectionné*/
						DistanceEnCours[a][i]=Matrice[SommetActuel][i]+DistanceFinal[SommetActuel];
				}
			}	
		}
		SommetActuel=PlusPetit(DistanceEnCours[a],DistanceFinal);/*Le prochain sommet est celui dont la distance est la plus petite et non selectionne parmis la ligne en cours du tableau*/
		DistanceFinal[SommetActuel]=DistanceEnCours[a][SommetActuel];/*La distance pour le point actuel correspond à sa valeur dans le tableau quand nous la selectionnons*/
		if(a!=TailleMatrice-1)CopieLigne(DistanceEnCours,a);/*Si nous ne sommes pas a la fin nous reportons la ligne actuel sur la ligne suivante*/
	}
	printf("\nDe plus le chemin le plus court passe par ");
	int Dispo[Taille],Chemin[Taille],NombreIte=0;
	for (int i = 0; i < Taille; i++){
		Dispo[i]=0;
	}
	SommetActuel=OrdreSommet[Taille-1];//Commence par le dernier sommet
	Dispo[0]=1;
	while(NombreDispo(Dispo)==0){
		Dispo[SommetActuel]=1;
		for (int i = Taille-1; i !=-1; i--){//Nous partons du bas et remontons
			if(DistanceEnCours[i][SommetActuel]!=DistanceEnCours[i-1][SommetActuel]){//Si la distance est différentes de celle du dessus
				Chemin[NombreIte+1]=OrdreSommet[i];// Enregistre le premier sommet
				Chemin[NombreIte]=SommetActuel;// Enregistre le sommet suivant
				NombreIte++;// Change de sommet
				SommetActuel=OrdreSommet[i];// Nous chageons de sommet
				break;
			}
		}
		if(SommetActuel==SommetDeDepart){// Si nous avons trouver le sommet de depart nous arretons
			break;
		}
	}
	for (int i = NombreIte; i !=-1; i--){//Affiche tout les sommets dans l'autre dans lesquels nous les avons découverts
		fprintf(stdout,"%c ",Chemin[i]+'A');//Affiche dans la console et non dans la fenetre graphique
	}
	fprintf(stdout,"comme vous avez pu le voir\n");

}