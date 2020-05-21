#include <stdio.h>
#include <stdlib.h>
#define Taille 7

struct Arc{
	int SommetDeDepart;
	int SommetArrive;
	int Poid;
	int Progression;
};

typedef struct Arc Arc;

void liberation(Arc **ListeArc,int taille){
	for (int i = 0; i < taille; i++){
		free(ListeArc[i]);
		ListeArc[i]=NULL;
	}
	free(ListeArc);
	ListeArc=NULL;
}

Arc **SimpleAllocation(int taille){
	int i;
	Arc **tab=(Arc**)malloc(taille*sizeof(Arc**));
	for (i=0;i<taille;i++){
		tab[i]=(Arc*)malloc(sizeof(Arc*));
		tab[i]->SommetDeDepart=0;
		tab[i]->SommetArrive=0;
		tab[i]->Poid=0;
		tab[i]->Progression=0;
	}
	return tab;
}

int NombreDArc(int Graphe[Taille][Taille]){
	int c=0;
	for (int i=0;i<Taille;i++){
		for (int j = 0; j < Taille; j++){
			if(Graphe[i][j]!=0)c++;
		}
	}
	return c;
}

void AssociationPoid(int Graphe[Taille][Taille],Arc **ListeArc){
	int Num=0;
	for (int i=0;i<Taille;i++){
		for (int j = 0; j < Taille; j++){
			if(Graphe[i][j]!=0){
				ListeArc[Num]->Poid=Graphe[i][j];
				Num++;
			}
		}
	}
}

void AffichageArc(Arc **ListeArc,int TailleArc){
	for (int i = 0; i < TailleArc; ++i){
		printf("%c | %c | %d | %d\n",ListeArc[i]->SommetDeDepart+'A',ListeArc[i]->SommetArrive+'A',ListeArc[i]->Poid,ListeArc[i]->Progression);
	}
	printf("\n");
}

int TotalInformation(int *SommetInformation,int taille){
	int c=0;
	for (int i = 0; i < taille; i++){
		if(SommetInformation[i]==0)c++;
	}
	return c;
}

void Initialisation(Arc **ListeArc,int TailleArc){
	for (int i = 0; i < TailleArc; i++)
	{
		ListeArc[i]->SommetDeDepart=0;
		ListeArc[i]->SommetArrive=0;
		ListeArc[i]->Poid=0;
		ListeArc[i]->Progression=0;
	}
}

void AssociationSommet(int Graphe[Taille][Taille],Arc **ListeArc,int TailleArc){
	int Num=0;
	for (int i = 0; i < Taille; i++)
	{
		for (int j = 0; j < Taille; j++)
		{
			if(Graphe[i][j]!=0){
				ListeArc[Num]->SommetDeDepart=i;
				ListeArc[Num]->SommetArrive=j;
				Num++;
			}
		}
	}
}

Arc *TrouveArc(Arc **ListeArc,int TailleArc,int Debut,int Fin){
	int i;
	for (i = 0; i < TailleArc; i++){
		if(ListeArc[i]->SommetDeDepart==Debut&&ListeArc[i]->SommetArrive==Fin)break;
	}
	return ListeArc[i];
}

int main(int argc, char *argv[])
{
	int Graphe[Taille][Taille]={{0,3,0,0,0,0,0},
								{0,0,2,0,1,0,0},
								{0,0,0,1,0,0,0},
								{0,0,0,0,0,2,0},
								{0,0,0,0,0,1,0},
								{0,0,0,0,0,0,4},
								{0,5,2,0,0,0,0}};
	int TailleArc=NombreDArc(Graphe),Temps=0;
	printf("%d\n",TailleArc);
	Arc **ListeArc=SimpleAllocation(TailleArc);
	int SommetInformation[Taille]={0};
	Initialisation(ListeArc,TailleArc);
	AssociationPoid(Graphe,ListeArc);
	AssociationSommet(Graphe,ListeArc,TailleArc);
	AffichageArc(ListeArc,TailleArc);
	SommetInformation[0]=1;
	while(TotalInformation(SommetInformation,Taille)!=0){
		Temps++;
		printf("||||||| Resultat fin de temps=%d |||||||\n",Temps);
		for (int i = 0; i < Taille; i++){
			if(SommetInformation[i]!=0){
				for (int j = 0; j < Taille; j++){
					if(Graphe[i][j]!=0){
						if(SommetInformation[j]==0){
							printf("Progression de %c vers %c\n",i+'A',j+'A');
							if(TrouveArc(ListeArc,TailleArc,i,j)->Progression!=TrouveArc(ListeArc,TailleArc,i,j)->Poid) (TrouveArc(ListeArc,TailleArc,i,j)->Progression)++;
							else if(SommetInformation[j]==0){
								SommetInformation[j]=1;
								printf("Le sommet %c à recu l'information\n",j+'A');
							}
						}
					}
				}
			}
		}
		AffichageArc(ListeArc,TailleArc);
	}

	liberation(ListeArc,TailleArc);
	return 0;
}
