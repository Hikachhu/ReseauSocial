#include "AllIncludes.h"

//Fonction libérant le tableau d'arc
void liberation(Arc *ListeArc,int taille){
	free(ListeArc);//Libère le tableau
	ListeArc=NULL;
}

//Alloue un tableau d'arc
Arc *SimpleAllocation(int tailleArc){
	Arc *tab=malloc(tailleArc*sizeof(Arc));
	return tab;
}

//Compte le nombre d'arc dans un graphe
int NombreDArc(int **Graphe){
	int c=0;
	for (int i=0;i<Taille;i++){
		for (int j = 0; j < Taille; j++){
			if(Graphe[i][j]!=0)c++;//Si la valeur est différente de 0 alors il s'agit d'un arc
		}
	}
	return c;
}

void AssociationPoid(int **Graphe,Arc *ListeArc){
	int Num=0;
	for (int i=0;i<Taille;i++){
		for (int j = 0; j < Taille; j++){
			if(Graphe[i][j]!=0){//Si nous trouvons un arc
				ListeArc[Num].Poid=Graphe[i][j];//Nous associons sa valeur à poid du sommet suivant
				Num++;//Change de sommet dans la liste
			}
		}
	}
}

//Permet d'afficher les caractéristiques de chaque arcs
void AffichageArc(Arc *ListeArc,int TailleArc){
	for (int i = 0; i < TailleArc; ++i){
		printf("%c | %c | %d | %d\n",ListeArc[i].SommetDeDepart+'A',ListeArc[i].SommetArrive+'A',ListeArc[i].Poid,ListeArc[i].Progression);
	}
	printf("\n");
}

//Verifie que tout les sommets possèdent bien l'informations
int TotalInformation(int *SommetInformation,int taille){
	int c=0;
	for (int i = 0; i < taille; i++){
		if(SommetInformation[i]==0)c++;
	}
	return c;
}

//Initialise le tableau des arcs avec leurs coordonnées visuels ainsi que les caracteristiques à 0
void Initialisation(Arc *ListeArc,int TailleArc){
	int ToutePosition[32]={//        Numero des arcs
	                40 , 40, 720,580, //0
                    80 ,200, 540,320, //1
                    80 ,200, 540,760, //2
                    240,240, 360,500, //3
                    280,400, 540,540, //4
                    280,440, 760,580, //5
                    440,280, 500,110, //6
                    200,40 , 110,500  //7
                					};
	for (int i = 0; i < TailleArc; i++)
	{
		ListeArc[i].SommetDeDepart=0;
		ListeArc[i].SommetArrive=0;
		ListeArc[i].Poid=0;
		ListeArc[i].Progression=0;
		ListeArc[i].YDebut=ToutePosition[i*4];
		ListeArc[i].YFin=ToutePosition[i*4+1];
		ListeArc[i].XDebut=ToutePosition[i*4+2];
		ListeArc[i].XFin=ToutePosition[i*4+3];
	}
}

//Fourni les sommets de début et de fin de chaque arc
void AssociationSommet(int **Graphe,Arc *ListeArc,int TailleArc){
	int Num=0;
	for (int i = 0; i < Taille; i++){
		for (int j = 0; j < Taille; j++){
			if(Graphe[i][j]!=0){
				ListeArc[Num].SommetDeDepart=i;
				ListeArc[Num].SommetArrive=j;
				Num++;
			}
		}
	}
}

//Trouve un arc a partir des informations sur son sommet de debut et de fin
int TrouveArc(Arc *ListeArc,int TailleArc,int Debut,int Fin){
	int i;
	for (i = 0; i < TailleArc; i++){
		if(ListeArc[i].SommetDeDepart==Debut&&ListeArc[i].SommetArrive==Fin)break;
	}
	return i;
}

//Initilise la fenetre d'affichage
void InitGraphic(){
  int gdriver,gmode;
  gdriver = VGA;gmode=VGAMAX;   
  initgraph(&gdriver,&gmode,"");
  setcolor(RED);
  setfontcolor(RED);
  printf("Liste Graphe");
}

//Ferme la fenetre
void StopGraphic(){
  sleep(4);
  closegraph();
}

//Affiche les differents cerle, leurs noms, ainsi que les arcs et leurs extremités.
void AffichageGraphic(Arc *ListeArc,int TailleArc){
  circle(760, 40, TailleCercle); //1
  outtextxy(760,40,"A");
  circle(540, 40, TailleCercle);//2
  outtextxy(540,40,"B");
  circle(320, 240, TailleCercle);//3
  outtextxy(320,240,"C");
  circle(540, 240, TailleCercle);//4
  outtextxy(540,240,"D");
  circle(760, 240, TailleCercle);//5
  outtextxy(760,240,"E");
  circle(540, 440, TailleCercle);//6
  outtextxy(540,440,"F");
  circle(110, 240, TailleCercle);//7
  outtextxy(110,240,"G");
  for (int i = 0; i < TailleArc; i++){//Affiche tout les arcs
  	line(ListeArc[i].XDebut,ListeArc[i].YDebut,ListeArc[i].XFin,ListeArc[i].YFin);
  	circle(ListeArc[i].XFin,ListeArc[i].YFin,TailleCercle/5);//Affiches leurs extremites
  }
}

//Affiche les segments en fonctions de leurs progressions
void SegmentProgression(Arc Actuel,int Progression){
	setcolor(BLUE);
	setfontcolor(BLUE);	
	int XProgress,YProgress;
	int AfficheX,AfficheY;
	XProgress=(abs(Actuel.XDebut-Actuel.XFin)/(Actuel.Poid))*Progression;//Decalage en X selon la progression
	YProgress=(abs(Actuel.YDebut-Actuel.YFin)/(Actuel.Poid))*Progression;//Decalage en Y selon la progression
	if(Progression!=Actuel.Poid){//Si le poid est different de la progression
		if(Actuel.XDebut<Actuel.XFin)//Permet de calculer le décalage nécessaire
			AfficheX=Actuel.XDebut+XProgress;
		else
			AfficheX=Actuel.XDebut-XProgress;
		if(Actuel.YDebut<Actuel.YFin)
			AfficheY=Actuel.YDebut+YProgress;
		else
			AfficheY=Actuel.YDebut-YProgress;

		line(AfficheX,AfficheY,Actuel.XDebut,Actuel.YDebut);//Affiche le segment en progression
	}
	else{//Si le segment a une progression complete
		line(Actuel.XDebut,Actuel.YDebut,Actuel.XFin,Actuel.YFin);//Reaffiche entierement la ligne
		circle(Actuel.XFin,Actuel.YFin,TailleCercle/5);//Affiche eglement le cercle
	}

}
