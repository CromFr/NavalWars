#include "ui.h"


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
//Affichage de la grille
//Testé & approuvé
void AfficherGrille()
{
     int i, j;

     CLRSCR;

     printf("O======================================O======================================O\n");
     printf("|             Vos Bateaux              |              Ses Bateaux             |\n");
     printf("O======================================O======================================O\n");
     printf("|       \\  0 1 2 3 4 5 6 7 8 9  /      |       \\  0 1 2 3 4 5 6 7 8 9  /      |\n");
     printf( "|         ---------------------        |         ---------------------        |\n");

     for(i=0 ; i<10 ; i++)
     {
         printf("|      %d |", i);
         for(j=0 ; j<10 ; j++)
         {
             switch(nGrille[0][i][j])
             {
                 case CASE_VIDE: printf("  ");break;
                 case CASE_PLOUF: printf(" -");break;
                 case CASE_TOUCHE: printf(" X");break;
                 case CASE_CROISEUR: case CASE_SOUSMARIN: case CASE_TORPILLEUR: printf(" O");break;
                 default: printf(" ?");break;
             }

         }
	printf(" |       |      %d |", i);
         for(j=0 ; j<10 ; j++)
         {
             switch(nGrille[1][i][j])
             {
                 case CASE_VIDE: printf("  ");break;
                 case CASE_PLOUF: printf(" -");break;
                 case CASE_TOUCHE: printf(" X");break;
                 case CASE_CROISEUR: case CASE_SOUSMARIN: case CASE_TORPILLEUR: printf(" O");break;
                 default: printf(" ?");break;
             }

         }
         printf(" |       |\n");
     }

     printf("|         ---------------------        |         ---------------------        |\n");
     printf("|       /                       \\      |       /                       \\      |\n");
     printf("O======================================O======================================O\n");
     printf("|   - : Tir dans l'eau             O : Bateau             X : Bateau touche   |\n");
     printf("O=============================================================================O\n");

}
