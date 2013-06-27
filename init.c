#include "init.h"

/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
void initPosNavires(int bAuto, int IA_or_player)
{
    AfficherGrille();
    int i=2;
    int ligne=0, colonne=0, alignement=0;
    printf("| Veuillez saisir :");
    while(i<=4) // On récolte les infos sur les positions souhaitées
    {
        if(!bAuto && IA_or_player==0)
        {
            //        O====================Coordonnees et alignement des bateaux====================O
            printf("\n|->La position du debut du %de navire mesurant %dcases (ligne colonne): ", i-1, i);
            scanf(" %d %d", &ligne, &colonne);
            printf("|-------->Puis son alignement Horizontal/Vertical (1/0): ");
            scanf(" %d", &alignement);

            if(verifierPlacement(i, alignement, ligne, colonne, GRILLE_JOU_OWN)==1) // On vérifie s'il n'y a pas d'erreur de dépacement
            {
                printf("| Veuillez saisir :");
                placerNavire(i, alignement, ligne, colonne, GRILLE_JOU_OWN);
                AfficherGrille();
                i++;
            }
        }
        else if(IA_or_player)
        {
            ligne=rand()%10;
            colonne=rand()%10;

            if(verifierPlacement(i, alignement, ligne, colonne, GRILLE_CPU_OWN)==1) // On vérifie s'il n'y a pas d'erreur de dépacement
            {
                placerNavire(i, alignement, ligne, colonne, GRILLE_CPU_OWN);
                i++;
            }
        }
        else
        {
            ligne=rand()%10;
            colonne=rand()%10;
            alignement=rand()%2;

            if(verifierPlacement(i, alignement, ligne, colonne, GRILLE_JOU_OWN)==1) // On vérifie s'il n'y a pas d'erreur de dépacement
            {
                placerNavire(i, alignement, ligne, colonne, GRILLE_JOU_OWN);
                i++;
            }
        }
    }
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
void placerNavire(int nb_cases, int alignement, int ligne, int colonne, int AI_or_player)
{
    switch(nb_cases)
    {
    case 2: // Torpilleur
        if(alignement==1)
        {
            while(nb_cases>0)
            {
                nGrille[AI_or_player][ligne][colonne+nb_cases-1]=CASE_TORPILLEUR;
                nb_cases--;
            }
        }
        else if(alignement==0)
        {
            while(nb_cases>0)
            {
                nGrille[AI_or_player][ligne+nb_cases-1][colonne]=CASE_TORPILLEUR;
                nb_cases--;
            }
        }
        break;
    case 3: // Sous-marin
        if(alignement==1)
        {
            while(nb_cases>0)
            {
                nGrille[AI_or_player][ligne][colonne+nb_cases-1]=CASE_SOUSMARIN;
                nb_cases--;
            }
        }
        else if(alignement==0)
        {
            while(nb_cases>0)
            {
                nGrille[AI_or_player][ligne+nb_cases-1][colonne]=CASE_SOUSMARIN;
                nb_cases--;
            }
        }
        break;
    case 4: // Croiseur
        if(alignement==1)
        {
            while(nb_cases>0)
            {
                nGrille[AI_or_player][ligne][colonne+nb_cases-1]=CASE_CROISEUR;
                nb_cases--;
            }
        }
        else if(alignement==0)
        {
            while(nb_cases>0)
            {
                nGrille[AI_or_player][ligne+nb_cases-1][colonne]=CASE_CROISEUR;
                nb_cases--;
            }
        }
        break;
    }
}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
int verifierPlacement(int nb_cases, int alignement, int ligne, int colonne, int AI_or_player)
{
    int correct=1;
    if(alignement==1) // Horizontal
    {
        while(nb_cases>0)
        {
            if(nGrille[AI_or_player][ligne][colonne+nb_cases-1]==0 && (((colonne+nb_cases))<=10&&(colonne>=0))) // On vérifie que la case est libre
                nb_cases--;
            else if(!(((colonne+nb_cases))<=10&&(colonne>=0)))
            {
                AfficherGrille();
                printf("| Erreur de depassement en (%d,%d), veuillez recommencer...", ligne, colonne+nb_cases-1);
                correct=0;
                break;
            }
            else if(!(nGrille[AI_or_player][ligne][colonne+nb_cases-1]==0))
            {
                AfficherGrille();
                printf("| Erreur de chevauchement en (%d,%d), veuillez recommencer...", ligne, colonne+nb_cases-1);
                correct=0;
                break;
            }
        }
    }
    else if(alignement==0)
    {
        while(nb_cases>0)
        {
            if(nGrille[AI_or_player][ligne+nb_cases-1][colonne]==0 && (((ligne+nb_cases))<=10&&(ligne>=0)))
                nb_cases--;
            else if(!(((ligne+nb_cases))<=10&&(ligne>=0)))
            {
                AfficherGrille();
                printf("| Erreur de depassement en (%d,%d), veuillez recommencer...", ligne+nb_cases-1, colonne);
                correct=0;
                break;
            }
            else if(!(nGrille[AI_or_player][ligne+nb_cases-1][colonne]==0))
            {
                AfficherGrille();
                printf("| Erreur de depassement en (%d,%d), veuillez recommencer...", ligne+nb_cases-1, colonne);
                correct=0;
                break;
            }
        }
    }
    else
    {
        AfficherGrille();
        printf("| Alignement incorrect, veuillez recommencer...");
        correct=0;
    }
    return correct;
}


void InitGrille(int nType)
{
    int z, i, j, nDep, nBorne;
    if(nType==GRILLE_ALL)
    {
        nDep = 0;
        nBorne = 4;
    }
    else
    {
        nDep = nType;
        nBorne = nType+1;
    }
    for(z=nDep ; z<nBorne ; z++)
    {
        for(i=0 ; i<10 ; i++)
        {
            for(j=0 ; j<10 ; j++)
            {
            nGrille[z][i][j]=0;
            }
        }
    }
}
