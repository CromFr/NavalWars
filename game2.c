void game_mode2(int* nRestart)
{

int k, who_start, bAuto;
int c1=0, c2=0, c3=0, d1=0, d2=0, d3=0;

while(1)
{
    printf("\nVoulez-vous placer vos bateaux manuellement ou automatiquement ? ( man : 0 | auto : 1) : ");
    scanf(" %d", &bAuto);

    if(bAuto==1 || bAuto==0)
    {
        initPosNavires(bAuto,0);
        AfficherGrille();
        break;
    }
    else
        printf("\nErreur de saisie, veuillez recommencer... ");

}

    initPosNavires(0,1);

    who_start=(((rand()%10)>4)? 1 : 0);

    if(who_start)  // On commence
    {
        for(k=1;1;k++) // Tant qu'on est en vie et que l'adversaire n'est pas mort
        {
            tirer(k,1);              // On tire et on affiche
            AfficherGrille();      //

            if(noDetectBoat(CASE_CROISEUR,1)!=c1)  // Si c'est la première foi qu'il n'y a plus de croiseur chez l'ennemi
            {
                printf("\nCroiseur ennemi detruit... ");
                c1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,1)!=c2)
            {
                printf("\nSous-marin ennemi detruit... ");
                c2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,1)!=c3)
            {
                printf("\nTorpilleur ennemi detruit... ");
                c3=1;
            }
            if(dead(1))
            {
                printf("\nFelicitations !! Vous avez gagne la partie !");
                break;
            }

            degats(1, nDiffuculte);              // On se fait tirer dessus, on affiche
            AfficherGrille();                    //

            if(noDetectBoat(CASE_CROISEUR,0)!=d1)  // Si c'est la première foi que vous n'avez plus de cases croiseur
            {
                printf("\nL'ennemi a detruit votre croiseur... ");
                d1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,0)!=d2)
            {
                printf("\nL'ennemi a detruit votre sous-marin... ");
                d2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,0)!=d3)
            {
                printf("\nL'ennemi a detruit votre torpilleur... ");
                d3=1;
            }
            if(dead(0))
            {
                printf("\nDiantre !! Vous avez perdu la partie !");
                break;
            }

        }
    }
    else  // On ne commence pas
    {
        for(k=1;1;k++)
        {
            degats(1, nDiffuculte);              // On se fait tirer dessus, on affiche
            AfficherGrille();                    //

            if(noDetectBoat(CASE_CROISEUR,0)!=d1)  // Si c'est la première foi que vous n'avez plus de cases croiseur
            {
                printf("\nL'ennemi a detruit votre croiseur... ");
                d1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,0)!=d2)
            {
                printf("\nL'ennemi a detruit votre sous-marin... ");
                d2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,0)!=d3)
            {
                printf("\nL'ennemi a detruit votre torpilleur... ");
                d3=1;
            }
            if(dead(0))
            {
                printf("\nDiantre !! Vous avez perdu la partie !");
                break;
            }

            tirer(k,1);              // On tire et on affiche
            AfficherGrille();        //

            if(noDetectBoat(CASE_CROISEUR,1)!=c1)  // Si c'est la première foi qu'il n'y a plus de croiseur chez l'ennemi
            {
                printf("\nCroiseur ennemi detruit... ");
                c1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,1)!=c2)
            {
                printf("\nSous-marin ennemi detruit... ");
                c2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,1)!=c3)
            {
                printf("\nTorpilleur ennemi detruit... ");
                c3=1;
            }
            if(dead(1))
            {
                printf("\nFelicitations !! Vous avez gagne la partie !");
                break;
            }
        }
    }

    printf("\nVoullez-vous recommencer ? ( Oui : 1 | Non : 0) : ");
    scanf(" %d", nRestart);

}
