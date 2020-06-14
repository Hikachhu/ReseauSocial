#include "AllIncludes.h"

//Permet de lire tout les sommets et les enregistrer dans la matrice
void ListeSommet(FILE *fichier,int **tab){
	int debut,fin,poid;
	while(fscanf(fichier,"%d%d%d",&debut,&fin,&poid)==3){
		tab[debut][fin]=poid;
	}
}

//Initalise la matrice du graphe
int **lecture(){
	char Fichier[50]="ListePoid.txt";
	FILE *fichier=fopen(Fichier,"r");
	int **tab=malloc(Taille*sizeof(int*));
	for (int i = 0; i < Taille; i++){
		tab[i]=malloc(Taille*sizeof(int));
		for (int j = 0; j < Taille; j++){
			tab[i][j]=0;
		}
	}
	ListeSommet(fichier,tab);
	return tab;
}