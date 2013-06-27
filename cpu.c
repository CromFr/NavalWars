#include "cpu.h"


extern int RandomAB(int a, int b);


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
void ActionCPU(int nDifficulte)
{
    struct vect vTirer;
    int nRandom, nPrioMax=-2000;
    struct vectprio vpPossibilites[16];


    int n;

    switch(nDifficulte)
    {
    case DIFFICULTE_FACILE://Random

        vTirer = CoordAleatoire(nDifficulte, bPaire);

        //tir + Mettre a jour les grilles
        switch(nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x])
        {
        case CASE_VIDE:
            nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x] = CASE_PLOUF;
            nGrille[GRILLE_CPU_ADV][vTirer.y][vTirer.x] = CASE_PLOUF;
            break;
        case CASE_CROISEUR:
        case CASE_SOUSMARIN:
        case CASE_TORPILLEUR:
            nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x] = CASE_TOUCHE;
            nGrille[GRILLE_CPU_ADV][vTirer.y][vTirer.x] = CASE_TOUCHE;
            break;
        }
        break;


    case DIFFICULTE_MOYEN://Random avec IA Touché

        niveauMoyen2();
        break;


    case DIFFICULTE_DIFFICILE:
        //Cases rand + IA Touché

        //Recherche d'une case intelligement
        if(!GetIsVectorValid(vTouche))//Si le cpu n'e vient pas de toucher un bateau
        {
            //Recherche d'une case vide (ou l'ordi n'a pas déja tiré) via random
            vTirer = CoordAleatoire(nDifficulte, bPaire);
        }
        else
        {
            //Set des prioriés & coordonnées de chaque case qui sont placés dans le tableau vpPossibilites
            GetPriorities(vpPossibilites);

            //On cherche le vecteur dont la priorité est maximale
            for(n=0 ; n<16 ; n++)
            {
                if(vpPossibilites[n].prio > nPrioMax)
                {
                    nPrioMax = vpPossibilites[n].prio;
                }
            }
            while(1)
            {
                nRandom = RandomAB(0, 15);
                if(vpPossibilites[nRandom].prio == nPrioMax)break;
            }

            vTirer.x = vpPossibilites[nRandom].x;
            vTirer.y = vpPossibilites[nRandom].y;

        }//Fin de la recherche

        //Finalement on tire
        TirerCPU(vTirer);
        break;


    case DIFFICULTE_TRES_DIFFICILE:
        //Cases impaires + IA Touché
        //Recherche d'une case intelligement
        if(!GetIsVectorValid(vTouche))//Si le cpu n'e vient pas de toucher un bateau
        {
            //Recherche d'une case vide (ou l'ordi n'a pas déja tiré) via random
            vTirer = CoordAleatoire(nDifficulte, bPaire);
        }
        else
        {
            //Set des prioriés & coordonnées de chaque case qui sont placés dans le tableau vpPossibilites
            GetPriorities(vpPossibilites);

            //On cherche le vecteur dont la priorité est maximale
            for(n=0 ; n<16 ; n++)
            {
                if(vpPossibilites[n].prio > nPrioMax)
                {
                    nPrioMax = vpPossibilites[n].prio;
                }
            }
            while(1)
            {
                nRandom = RandomAB(0, 15);
                if(vpPossibilites[nRandom].prio == nPrioMax)break;
            }

            vTirer.x = vpPossibilites[nRandom].x;
            vTirer.y = vpPossibilites[nRandom].y;

        }//Fin de la recherche

        //Finalement on tire
        TirerCPU(vTirer);
        break;
    }




}


/*====================================================================================================================================================
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ====================================================================================================================================================*/
struct vect CoordAleatoire(int nDifficulte, int bPaire)
{
    struct vect vPosRandom;

    switch(nDifficulte)
    {
    case 1:
    case 2:
    case 3://Aléatoire pour modes <= difficile
        do
        {
            vPosRandom.x = RandomAB(0, 9);
            vPosRandom.y = RandomAB(0, 9);
        }
        while(nGrille[GRILLE_CPU_ADV][vPosRandom.y][vPosRandom.x] != 0);
        break;

    default://Aléatoire sur cases impaires pour modes >2
        do
        {
            if(bPaire)
            {
                do
                {
                    vPosRandom.x = RandomAB(0, 9);
                    vPosRandom.y = RandomAB(0, 9);
                }
                while( (vPosRandom.x+vPosRandom.y)%2 !=0 );
            }
            else
            {
                do
                {
                    vPosRandom.x = RandomAB(0, 9);
                    vPosRandom.y = RandomAB(0, 9);
                }
                while( (vPosRandom.x+vPosRandom.y)%2 !=1 );
            }
        }
        while(nGrille[GRILLE_CPU_ADV][vPosRandom.y][vPosRandom.x] != 0);

        break;
    }

    return vPosRandom;
}


void TirerCPU(struct vect vTirer)
{
if(!GetIsVectorValid(vTirer))
{
    printf("\nERREUR TirerCPU : VECTEUR INVALIDE\n");
    return;
}


    switch(nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x])
    {
    case CASE_VIDE:
        nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x] = CASE_PLOUF;
        nGrille[GRILLE_CPU_ADV][vTirer.y][vTirer.x] = nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x];
        break;
    case CASE_CROISEUR:
    case CASE_SOUSMARIN:
    case CASE_TORPILLEUR:
        nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x] = CASE_TOUCHE;
        nGrille[GRILLE_CPU_ADV][vTirer.y][vTirer.x] = nGrille[GRILLE_JOU_OWN][vTirer.y][vTirer.x];//Remplacement par le type de bateau
        vTouche = vTirer;
        break;
    }
}



int DistToPriority(int nDist, int nPrio)
{
    int nReturn = nPrio * (4-abs(nDist))/3;
    return nReturn;
}


void GetPriorities(struct vectprio *vpPossibilites)
{
    int n, i;

    //Initialisation de vectprio vpPossibilites
    for(n=0 ; n<16 ; n++)
    {
        vpPossibilites[n].x=-1;
        vpPossibilites[n].y=-1;
        vpPossibilites[n].prio=0;
    }

    //===============Suivant Y
    //Set des positions====================================================
    for(n=0 ; n<8; n++)
    {
        vpPossibilites[n].prio = 0;

        //Si en dehors de la grille
        if(n-3+vTouche.y < 0 || n-3+vTouche.y > 9)
        {
            //On ne la joue pas
            vpPossibilites[n].prio = -1000;
            continue;
        }
        //Si case déja occupée (injouable);
        if(nGrille[GRILLE_CPU_ADV][n-3+vTouche.y][vTouche.x] != CASE_VIDE)
        {
            //On ne la joue pas, et on ne calcule pas sa prio
            vpPossibilites[n].prio = -1000;
            continue;
        }

        //Si dans la grille && case jouable, on calcule sa priorité

        //Set de la position====================================================
        vpPossibilites[n].x = vTouche.x;
        vpPossibilites[n].y = n-3+vTouche.y;

        //Set de la priorité====================================================
        for(i=0 ; i<7 ; i++)
        {
            //Si en dehors de la grille
            if(i-3+(n-3+vTouche.y) < 0 || i-3+(n-3+vTouche.y) > 9)
            {
                //On ne modifie pas la priorite
                continue;
            }
            //si case plouf
            if(nGrille[GRILLE_CPU_ADV][i-3+n-3+vTouche.y][vTouche.x] == CASE_PLOUF)
            {
                if(i<3)//Si avant le milieu, on continue
                {
                    continue;
                }
                else//Si après, on arrête la recherche
                {
                    break;
                }
            }

            if((nGrille[GRILLE_CPU_ADV][i-3+n-3+vTouche.y][vTouche.x] == CASE_TOUCHE) ||
               (nGrille[GRILLE_CPU_ADV][i-3+n-3+vTouche.y][vTouche.x] == CASE_CROISEUR) ||
               (nGrille[GRILLE_CPU_ADV][i-3+n-3+vTouche.y][vTouche.x] == CASE_TORPILLEUR) ||
               (nGrille[GRILLE_CPU_ADV][i-3+n-3+vTouche.y][vTouche.x] == CASE_SOUSMARIN))
            {
                vpPossibilites[n].prio += DistToPriority(i-3, 9);
            }
        }
    }
    //===============Suivant X
    //Set des positions====================================================
    for(n=0 ; n<8; n++)
    {
        vpPossibilites[n+8].prio = 0;

        //Si en dehors de la grille
        if(n-3+vTouche.x < 0 || n-3+vTouche.x > 9)
        {
            //On ne la joue pas
            vpPossibilites[n+8].prio = -1000;
            continue;
        }
        //Si case déja occupée (injouable);
        if(nGrille[GRILLE_CPU_ADV][vTouche.y][n-3+vTouche.x] != CASE_VIDE)
        {
            //On ne la joue pas, et on ne calcule pas sa prio
            vpPossibilites[n+8].prio = -1000;
            continue;
        }

        //Si dans la grille && case jouable, on calcule sa priorité

        //Set de la position====================================================
        vpPossibilites[n+8].x = n-3+vTouche.x;
        vpPossibilites[n+8].y = vTouche.y;

        //Set de la priorité====================================================
        for(i=0 ; i<7 ; i++)
        {
            //Si en dehors de la grille
            if(i-3+(n-3+vTouche.x) < 0 || i-3+(n-3+vTouche.x) > 9 || i==3)
            {
                //On ne modifie pas la priorite
                continue;
            }
            //si case plouf
            if(nGrille[GRILLE_CPU_ADV][vTouche.y][i-3+n-3+vTouche.x] == CASE_PLOUF)
            {
                if(i<3)//Si avant le milieu, on continue
                {
                    continue;
                }
                else//Si après, on arrête la recherche
                {
                    break;
                }
            }

            if((nGrille[GRILLE_CPU_ADV][vTouche.y][i-3+n-3+vTouche.x] == CASE_TOUCHE) ||
               (nGrille[GRILLE_CPU_ADV][vTouche.y][i-3+n-3+vTouche.x] == CASE_CROISEUR) ||
               (nGrille[GRILLE_CPU_ADV][vTouche.y][i-3+n-3+vTouche.x] == CASE_TORPILLEUR) ||
               (nGrille[GRILLE_CPU_ADV][vTouche.y][i-3+n-3+vTouche.x] == CASE_SOUSMARIN))
            {
                vpPossibilites[n+8].prio += DistToPriority(i-3, 9);
            }
        }
    }
}


void ScanAndConvertPLOUF(int nGrilleType, int nTypeToConvert)
{
    int i, j;

    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            if(nGrille[nGrilleType][i][j] == nTypeToConvert)
            {
                nGrille[nGrilleType][i][j] = CASE_PLOUF;
            }
        }
    }
}


void ChercherAncienneCaseTouchee(int nGrilleType)
{
    int i, j, n=0;
    int nRand;
    struct vect vVectPossibles[9];

    //Initialisation des vecteurs
    for(i=0 ; i<9 ; i++)
    {
        vVectPossibles[i].x=-1;
        vVectPossibles[i].y=-1;
    }

    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            if(nGrille[nGrilleType][i][j] != CASE_PLOUF && nGrille[nGrilleType][i][j] != CASE_VIDE)//Si il y a touche ou bateau
            {
                vVectPossibles[n].y = i;
                vVectPossibles[n].x = j;
                n++;
            }
        }
    }

    //Choix d'un d'entre eux au hazard
    do
    {
        nRand = RandomAB(0, n);
    }while(!GetIsVectorValid(vVectPossibles[nRand])
           && n!=0);//quitte immediatement si il n'y a pas de cases touchees

    vTouche = vVectPossibles[nRand];

}












int caseVide(int ligne, int colonne, int IA_or_player) // Returne 1 si la case considÃ©rÃ©e est vide
{
    if(ligne>9 || ligne<0 || colonne>9 || colonne<0)
        return 0;

    if(IA_or_player==1)
    {
        if(nGrille[GRILLE_CPU_ADV][ligne][colonne]==0)            ////// NE PAS OUBLIER LES BORDURES
            return 1;
    }
    else
    {
        if(nGrille[GRILLE_JOU_ADV][ligne][colonne]==0)
            return 1;
    }
    return 0;
}

void niveauMoyen2(void) // IA niveau moyen
{
    int ligne, colonne;

    while(1)
    {
        if(vPrecedent.x!=-1
        && (nGrille[GRILLE_CPU_ADV][vPrecedent.y][vPrecedent.x]==CASE_CROISEUR     // et que la case précédente est une case touché
        || nGrille[GRILLE_CPU_ADV][vPrecedent.y][vPrecedent.x]==CASE_SOUSMARIN     //
        || nGrille[GRILLE_CPU_ADV][vPrecedent.y][vPrecedent.x]==CASE_TORPILLEUR))  //
        {
            if(VerifCaseAdj2(vPrecedent.y, vPrecedent.x) && !noDetectBoat(nGrille[GRILLE_CPU_ADV][vPrecedent.y][vPrecedent.x], 0))    // Si la case est saturée (on tire sur une case vide sinon)
            {
                PutCaseAdj2(vPrecedent.y, vPrecedent.x);
                break;
            }
            else
            {
                do
                {
                    randomCase(&ligne, &colonne);
                }while(!caseVide(ligne, colonne, 1)); // Tant que la case au hasard a déjà été joué

                switchGrille(ligne, colonne); // On tire sur la case
                break;
            }
        }
        else
            {
                do
                {
                    randomCase(&ligne, &colonne);
                }while(!caseVide(ligne, colonne, 1)); // Tant que la case au hasard a déjà été joué

                switchGrille(ligne, colonne); // On tire sur la case
                break;
            }

          /*  else
                switchGrille(vPrecedent.y, vPrecedent.x);*/

            break;
        }
}

void switchGrille(int ligne, int colonne) // Tire sur la case
{
    switch(nGrille[GRILLE_JOU_OWN][ligne][colonne])
    {
        case CASE_VIDE :
            nGrille[GRILLE_JOU_OWN][ligne][colonne]=CASE_PLOUF;
            nGrille[GRILLE_CPU_ADV][ligne][colonne]=CASE_PLOUF;
            AfficherGrille();
            printf("\nTir ennemi manque... ");
            break;

        case CASE_CROISEUR :
            nGrille[GRILLE_JOU_OWN][ligne][colonne]=CASE_TOUCHE;
            nGrille[GRILLE_CPU_ADV][ligne][colonne]=CASE_CROISEUR;
            vPrecedent.y=ligne;
            vPrecedent.x=colonne;
            AfficherGrille();
            printf("\nVous avez ete touche... ");
            break;

        case CASE_SOUSMARIN :
            nGrille[GRILLE_JOU_OWN][ligne][colonne]=CASE_TOUCHE;
            nGrille[GRILLE_CPU_ADV][ligne][colonne]=CASE_SOUSMARIN;
            vPrecedent.y=ligne;
            vPrecedent.x=colonne;
            AfficherGrille();
            printf("\nVous avez ete touche... ");
            break;

        case CASE_TORPILLEUR :
            nGrille[GRILLE_JOU_OWN][ligne][colonne]=CASE_TOUCHE;
            nGrille[GRILLE_CPU_ADV][ligne][colonne]=CASE_TORPILLEUR;
            vPrecedent.y=ligne;
            vPrecedent.x=colonne;
            AfficherGrille();
            printf("\nVous avez ete touche... ");
            break;
    }
}

void randomCase(int* ligne, int* colonne)
{
    *ligne=rand()%10;
    *colonne=rand()%10;
}


int VerifCaseAdj2(int ligne, int colonne)
{
    if(caseVide(ligne+1, colonne,1))
    {
        return 1;
    }
    else if(caseVide(ligne-1, colonne,1))
    {
        return 1;
    }
    else if(caseVide(ligne, colonne+1,1))
    {
        return 1;
    }
    else if(caseVide(ligne, colonne-1,1))
    {
        return 1;
    }
    else
        return 0;
}

void PutCaseAdj2(int ligne, int colonne)
{
    if(rand()%2)
    {
        if(caseVide(ligne+1, colonne,1))
        {
            switchGrille(ligne+1, colonne);
        }
        else if(caseVide(ligne, colonne-1,1))
        {
            switchGrille(ligne, colonne-1);
        }
        else if(caseVide(ligne-1, colonne,1))
        {
            switchGrille(ligne-1, colonne);
        }
        else if(caseVide(ligne, colonne+1,1))
        {
            switchGrille(ligne, colonne+1);
        }

    }
    else
    {
        if(caseVide(ligne, colonne-1,1))
        {
            switchGrille(ligne, colonne-1);
        }
        else if(caseVide(ligne+1, colonne,1))
        {
            switchGrille(ligne+1, colonne);
        }
        else if(caseVide(ligne, colonne+1,1))
        {
            switchGrille(ligne, colonne+1);
        }
        else if(caseVide(ligne-1, colonne,1))
        {
            switchGrille(ligne-1, colonne);
        }

    }
}
