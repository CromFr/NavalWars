
#include "battle.h"


extern int nGrille[4][10][10];

void tirer(int k, int AI_or_player)
{
    int l, c, type,i;

    while(1)
    {
        printf("\nVeuillez saisir les coordonnees de la frappe n°%d ( ligne | colonne ) : ", k);
        scanf(" %d %d", &l, &c);

        if(AI_or_player==0) // Si on joue en réseau
        {
            if(l<10 && l>=0 && c<10 && c>=0 && nGrille[GRILLE_JOU_ADV][l][c]==CASE_VIDE) // Si la case existe et qu'elle n'a pas déjà été joué
            {
                send_position(l,c);     // Envoie la position
                receive_position(&type,&i); // Reçoie le type de case touchée

                switch(type)
                {
                    case CASE_PLOUF :
                        nGrille[GRILLE_JOU_ADV][l][c]=CASE_PLOUF;  // à l'eau
                        AfficherGrille();
                        printf("\nTir manque... ");
                        printf("\n");
                        break;

                    case CASE_TOUCHE :
                        nGrille[GRILLE_JOU_ADV][l][c]=CASE_TOUCHE; // touché
                        AfficherGrille();
                        printf("\nTir reussi... ");
                        printf("\n");
                        break;

                }
                AfficherGrille();
                break;
            }
            else
                printf("\nErreur de coordonnees, veuillez recommencer... ");
        }
        else  // Si on joue contre l'ordi
        {
            if(l<10 && l>=0 && c<10 && c>=0 && nGrille[GRILLE_JOU_ADV][l][c]==CASE_VIDE)
            {
                switch(nGrille[GRILLE_CPU_OWN][l][c])
                {
                    case CASE_VIDE :
                        nGrille[GRILLE_CPU_OWN][l][c]=CASE_PLOUF;
                        nGrille[GRILLE_JOU_ADV][l][c]=CASE_PLOUF;
                        AfficherGrille();
                        printf("\nTir manque... ");
                        printf("\n");
                        break;

                    case CASE_CROISEUR : case CASE_SOUSMARIN : case CASE_TORPILLEUR :
                        nGrille[GRILLE_CPU_OWN][l][c]=CASE_TOUCHE;
                        nGrille[GRILLE_JOU_ADV][l][c]=CASE_TOUCHE;
                        AfficherGrille();
                        printf("\nTir reussi... ");
                        printf("\n");
                        break;

                }
                break;
            }
            else
                printf("\nErreur de coordonnees, veuillez recommencer... ");
        }

    }
}

void degats(int AI_or_player, int nDifficulte)
{
    int l, c;

    if(AI_or_player==0)
    {
        receive_position(&l, &c); // Reçoie la position de la frappe
        switch(nGrille[GRILLE_JOU_OWN][l][c])  // Regarde ce qu'elle a touché
        {
            case CASE_CROISEUR : case CASE_SOUSMARIN : case CASE_TORPILLEUR :
                nGrille[GRILLE_JOU_OWN][l][c]=CASE_TOUCHE;
                AfficherGrille();
                printf("\nVous avez ete touche... ");
                break;
            case CASE_VIDE :
                nGrille[GRILLE_JOU_OWN][l][c]=CASE_PLOUF;
                AfficherGrille();
                printf("\nTir ennemi manque... ");
                break;
        }
        send_position(nGrille[GRILLE_JOU_OWN][l][c],1); // Renvoie le type de case touchée
    }
    else
    {
        ActionCPU(nDifficulte);
    }
}

int dead(int AI_or_player)  // Si une de nos cases n'a pas été touché par un tir, on est en vie
{
    int i, j;

    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            if(AI_or_player==0)
            {
                if(nGrille[GRILLE_JOU_OWN][i][j]==CASE_CROISEUR || nGrille[GRILLE_JOU_OWN][i][j]==CASE_SOUSMARIN || nGrille[GRILLE_JOU_OWN][i][j]==CASE_TORPILLEUR)
                    return 0;
            }
            else
            {
                if(nGrille[GRILLE_CPU_OWN][i][j]==CASE_CROISEUR || nGrille[GRILLE_CPU_OWN][i][j]==CASE_SOUSMARIN || nGrille[GRILLE_CPU_OWN][i][j]==CASE_TORPILLEUR)
                    return 0;
            }
        }
    }
    return 1;
}

int noDetectBoat(int type, int AIorPlayer_OWNorADV)  // Si une de nos cases n'a pas été touché par un tir, on est en vie JOU_OWN 0, CPU_OWN 1, JOU_ADV 2 et CPU_ADV 3
{
    int i, j;

     for(i=0 ; i<10 ; i++)
     {
         for(j=0 ; j<10 ; j++)
         {
             if(AIorPlayer_OWNorADV==0)
             {
                switch(type)
                {
                    case CASE_CROISEUR :
                        if(nGrille[GRILLE_JOU_OWN][i][j]==CASE_CROISEUR)
                        return 0;
                        break;

                    case CASE_SOUSMARIN :
                        if(nGrille[GRILLE_JOU_OWN][i][j]==CASE_SOUSMARIN)
                        return 0;
                        break;

                    case CASE_TORPILLEUR :
                        if(nGrille[GRILLE_JOU_OWN][i][j]==CASE_TORPILLEUR)
                        return 0;
                        break;
                }
             }
             else if(AIorPlayer_OWNorADV==1)
             {
                switch(type)
                {
                    case CASE_CROISEUR :
                        if(nGrille[GRILLE_CPU_OWN][i][j]==CASE_CROISEUR)
                        return 0;
                        break;

                    case CASE_SOUSMARIN :
                        if(nGrille[GRILLE_CPU_OWN][i][j]==CASE_SOUSMARIN)
                        return 0;
                        break;

                    case CASE_TORPILLEUR :
                        if(nGrille[GRILLE_CPU_OWN][i][j]==CASE_TORPILLEUR)
                        return 0;
                        break;
                }
             }
             else if(AIorPlayer_OWNorADV==2)
             {
                switch(type)
                {
                    case CASE_CROISEUR :
                        if(nGrille[GRILLE_JOU_ADV][i][j]==CASE_CROISEUR)
                        return 0;
                        break;

                    case CASE_SOUSMARIN :
                        if(nGrille[GRILLE_JOU_ADV][i][j]==CASE_SOUSMARIN)
                        return 0;
                        break;

                    case CASE_TORPILLEUR :
                        if(nGrille[GRILLE_JOU_ADV][i][j]==CASE_TORPILLEUR)
                        return 0;
                        break;
                }
             }
             else if(AIorPlayer_OWNorADV==3)
             {
                switch(type)
                {
                    case CASE_CROISEUR :
                        if(nGrille[GRILLE_CPU_ADV][i][j]==CASE_CROISEUR)
                        return 0;
                        break;

                    case CASE_SOUSMARIN :
                        if(nGrille[GRILLE_CPU_ADV][i][j]==CASE_SOUSMARIN)
                        return 0;
                        break;

                    case CASE_TORPILLEUR :
                        if(nGrille[GRILLE_CPU_ADV][i][j]==CASE_TORPILLEUR)
                        return 0;
                        break;
                }
             }
         }
     }
     return 1;
}
