//Librairies
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "divers.h"    //Relatif aux constantes utilisées ET VARIABLES GLOBALES
#include "ui.h"     //Relatif à l'affichage dans la console
#include "reseau.h" //Relatif à la comm en réseau
#include "init.h"   //Mise en place des bateaux
#include "cpu.h"   //IA
#include "battle.h"



//Nettoyage de l'écran
#define CLRSCR printf("\33[H\33[2J")//printf("\033[2J\033[1;1H")



//DEFINITION VARIABLES GLOBALES
int nGrille[4][10][10]={{{0}}};

struct vect vTouche;
int bPaire;

//Liées au réseau
struct sockaddr_in si_me, si_other;
int sock_send, sock_recv;

struct vect vPrecedent;
int firstTime=1;              // En global
struct vectprio everTried[9]; //

void game_mode1(int* nRestart);
void game_mode2(int* nRestart);


/*===================================================================================================================================================
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
=====================================================================================================================================================*/
int main(int argc, char** argv)
{
    int nRestart=1;
    int nChoix_mode;

    srand(time(NULL));

    while(nRestart)
    {
        CLRSCR;
        printf("O=============================================================================O\n");
        printf("|                   ~      O                                                  |\n");
        printf("|         ~                O          ~            ~                     ~    |\n");
        printf("|    ~          _        _       _             ~       _   _   _              |\n");
        printf("|         |\\ | |_| |  | |_| |                  \\ |\\ | |_| |_| |_              |\n");
        printf("|    ~    | \\| | |  \\/  | | |_                  \\| \\| | | | \\  _|         ~   |\n");
        printf("|                      ~                                                      |\n");
        printf("|             ~                 ~ X X O          ~               ~         ~  |\n");
        printf("|      ~                                                 copyright 2011 (c)   |\n");
        printf("O=============================================================================O\n");
        printf("| \n");

        printf("O------> Veuillez choisir votre mode de jeu (reseau : 1 / solo : 0) : ");
        scanf(" %d", &nChoix_mode);

        if(nChoix_mode==1)
            game_mode1(&nRestart);
        else if(nChoix_mode==0)
            game_mode2(&nRestart);
    }

	return EXIT_SUCCESS;
}







/*====================================================================================================================================================
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    >>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>MODES>>>>>>>>>
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ====================================================================================================================================================*/
void game_mode1(int* nRestart)
{
char cChoix;
char cIPAdversaire[20];
int nPortSend;
int nPortRecv;
int k, who_start, who_start1, who_start2, recommencer=1, adversaire_mort=0,i, bAuto;
int croiseur, sousmarin, torpilleur;
int c1=0, c2=0, c3=0, d1=0, d2=0, d3=0;


InitGrille(GRILLE_ALL);

while(1)
    {
    GetConfig(cIPAdversaire, &nPortSend, &nPortRecv);

    CLRSCR;
    printf("O=============================================================================O\n");
    printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< JEU EN RESEAU >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
    printf("O=================================>Parametres<================================O\n");
    printf("| IP de l'adversaire : %s\n", cIPAdversaire);
    printf("| Port d'emmission : %d\n", nPortSend);
    printf("| Port de reception : %d\n", nPortRecv);
    printf("O---------------------------------------->Conserver ces parametres?(o/n): ");


    scanf(" %c", &cChoix);
    if(cChoix == 0x6F)// o
        {
        printf("| Parametres acceptes !\n|\n");
        break;
        }
    if(cChoix == 0x6E)// n
        {
        MenuChangerConfig();
        }
    }

init_socket_send(nPortSend, cIPAdversaire);
init_socket_recv(nPortRecv);


do
{
    printf("O============================>Placement des Bateaux<==========================O\n");
    printf("O-->Voulez-vous placer vos bateaux manuellement ou automatiquement ? (0/1): ");
    scanf(" %d", &bAuto);

    if(bAuto!=1 && bAuto!=0)
    {
        printf("| Erreur de saisie, veuillez recommencer... \n| (1/0): ");
    }
}while(bAuto!=1 && bAuto!=0);

initPosNavires(bAuto,0);
AfficherGrille();

if(bAuto) printf("| Bateaux places automatiquement !\n|\n");
else printf("| Placement manuel des bateaux !\n|\n");
    // Initialiser la connexion

    while(recommencer) // Définie qui va commencer
    {
        who_start1=rand()%10;   // Tirage d'un nombre entre 0 et 9
        send_position(1,who_start1);  // On l'envoie à l'autre ordi
        receive_position(&i,&who_start2);  // On reçoie le sien
        if(who_start1!=who_start2)  // Si les nombres sont différents
        {
            who_start=((who_start1>who_start2)? 1 : 0);  // Si le sien est le plus grand, on commence
            recommencer=0;
        }
    }
    if(who_start)  // On commence
    {
        for(k=1;1;k++) // Tant qu'on est en vie et que l'adversaire n'est pas mort
        {
            tirer(k,0);              // On tire et on affiche
            AfficherGrille();      //

            receive_position(&adversaire_mort,&i);            //
            receive_position(&croiseur,&i);                   // On reçoie la situation de l'autre
            receive_position(&sousmarin,&i);                  //
            receive_position(&torpilleur,&i);                 //

            if(croiseur!=c1)  // Si c'est la première foi qu'il n'y a plus de croiseur chez l'ennemi
            {
                printf("\nCroiseur ennemi detruit... ");
                printf("\n");
                c1=croiseur;
            }
            if(sousmarin!=c2)
            {
                printf("\nSous-marin ennemi detruit... ");
                printf("\n");
                c2=sousmarin;
            }
            if(torpilleur!=c3)
            {
                printf("\nTorpilleur ennemi detruit... ");
                printf("\n");
                c3=torpilleur;
            }
            if(adversaire_mort)
            {
                printf("\nFelicitations !! Vous avez gagne la partie !\n");
                break;
            }
            sleep(2);

            degats(0,0);              // On se fait tirer dessus, on affiche
            AfficherGrille();      //

            send_position(dead(0),1);
            send_position(noDetectBoat(CASE_CROISEUR,0),1);    // On envoie notre situation
            send_position(noDetectBoat(CASE_SOUSMARIN,0),1);   //
            send_position(noDetectBoat(CASE_TORPILLEUR,0),1);  //

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
                printf("\nDiantre !! Vous avez perdu la partie !\n");
                break;
            }

        }
    }
    else  // On ne commence pas
    {
        for(k=1;1;k++)
        {
            degats(0,0);
            AfficherGrille();

            send_position(dead(0),1);
            send_position(noDetectBoat(CASE_CROISEUR,0),1);
            send_position(noDetectBoat(CASE_SOUSMARIN,0),1);
            send_position(noDetectBoat(CASE_TORPILLEUR,0),1);

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
                printf("\nDiantre !! Vous avez perdu la partie !\n");
                break;
            }

            tirer(k,0);
            AfficherGrille();

            receive_position(&adversaire_mort,&i);
            receive_position(&croiseur,&i);
            receive_position(&sousmarin,&i);
            receive_position(&torpilleur,&i);

            if(croiseur!=c1)
            {
                printf("\nCroiseur ennemi detruit... ");
                printf("\n");
                c1=croiseur;
            }
            if(sousmarin!=c2)
            {
                printf("\nSous-marin ennemi detruit... ");
                printf("\n");
                c2=sousmarin;
            }
            if(torpilleur!=c3)
            {
                printf("\nTorpilleur ennemi detruit... ");
                printf("\n");
                c3=torpilleur;
            }
            if(adversaire_mort)
            {
                printf("\nFelicitations !! Vous avez gagne la partie !\n");
                break;
            }
            sleep(2);
        }
    }

    printf("\nVoullez-vous recommencer ? ( Oui : 1 | Non : 0) : ");
    scanf(" %d", nRestart);

}



/*===================================================================================================================================================
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
=====================================================================================================================================================*/
void game_mode2(int *nRestart)
{
//*********
char cChoix;
int nDifficulte;
int k, who_start, bAuto;
int c1=0, c2=0, c3=0, d1=0, d2=0, d3=0;
//*********

vPrecedent.x=-1;

CLRSCR;
printf("O=============================================================================O\n");
printf("|<<<<<<<<<<<<<<<<<<<<<<<<<< JEU CONTRE L'ORDINATEUR >>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
printf("O=============================================================================O\n");
printf("| Difficulte :       1 : Facile\n");
printf("|                    2 : Moyen\n");
printf("|                    3 : Difficile\n");
printf("|                    4 : Tres Difficile\n");
printf("O---------------------------------------->Choisissez (1/2/3/4) :");


scanf(" %c", &cChoix);

if(cChoix == 0x31)// 0x31=1
    {nDifficulte=DIFFICULTE_FACILE;}
if(cChoix == 0x32)// 0x32=2
    {nDifficulte=DIFFICULTE_MOYEN;}
if(cChoix == 0x33)// 0x33=3
    {nDifficulte=DIFFICULTE_DIFFICILE;}
if(cChoix == 0x34)// 0x34=4
    {nDifficulte=DIFFICULTE_TRES_DIFFICILE;}

bPaire = RandomAB(0, 1);

SetVectorInvalid(&vTouche);

InitGrille(GRILLE_ALL);


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
            tirer(k,1);              // On tire

            if(noDetectBoat(CASE_CROISEUR,1)!=c1)  // Si c'est la première foi qu'il n'y a plus de croiseur chez l'ennemi
            {
                printf("\nCroiseur ennemi detruit... ");
                printf("\n");
                c1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,1)!=c2)
            {
                printf("\nSous-marin ennemi detruit... ");
                printf("\n");
                c2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,1)!=c3)
            {
                printf("\nTorpilleur ennemi detruit... ");
                printf("\n");
                c3=1;
            }
            if(dead(1))
            {
                printf("\nFelicitations !! Vous avez gagne la partie !\n");
                break;
            }
            sleep(2);

            degats(1, nDifficulte);              // On se fait tirer dessus, on affiche

            if(noDetectBoat(CASE_CROISEUR,0)!=d1)  // Si c'est la première foi que vous n'avez plus de cases croiseur
            {
                printf("\nL'ennemi a detruit votre croiseur... ");
                SetVectorInvalid(&vTouche);
                //ScanAndConvertPLOUF(GRILLE_CPU_ADV, CASE_CROISEUR);
                //ChercherAncienneCaseTouchee(GRILLE_CPU_ADV);
                d1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,0)!=d2)
            {
                printf("\nL'ennemi a detruit votre sous-marin... ");
                SetVectorInvalid(&vTouche);
                //ScanAndConvertPLOUF(GRILLE_CPU_ADV, CASE_SOUSMARIN);
                //ChercherAncienneCaseTouchee(GRILLE_CPU_ADV);
                d2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,0)!=d3)
            {
                printf("\nL'ennemi a detruit votre torpilleur... ");
                SetVectorInvalid(&vTouche);
                //ScanAndConvertPLOUF(GRILLE_CPU_ADV, CASE_TORPILLEUR);
                //ChercherAncienneCaseTouchee(GRILLE_CPU_ADV);
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
            degats(1, nDifficulte);              // On se fait tirer dessus, on affiche

            if(noDetectBoat(CASE_CROISEUR,0)!=d1)  // Si c'est la première foi que vous n'avez plus de cases croiseur
            {
                printf("\nL'ennemi a detruit votre croiseur... ");
                SetVectorInvalid(&vTouche);
                //ScanAndConvertPLOUF(GRILLE_CPU_ADV, CASE_CROISEUR);
                //ChercherAncienneCaseTouchee(GRILLE_CPU_ADV);
                d1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,0)!=d2)
            {
                printf("\nL'ennemi a detruit votre sous-marin... ");
                SetVectorInvalid(&vTouche);
                //ScanAndConvertPLOUF(GRILLE_CPU_ADV, CASE_SOUSMARIN);
                //ChercherAncienneCaseTouchee(GRILLE_CPU_ADV);
                d2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,0)!=d3)
            {
                printf("\nL'ennemi a detruit votre torpilleur... ");
                SetVectorInvalid(&vTouche);
                //ScanAndConvertPLOUF(GRILLE_CPU_ADV, CASE_TORPILLEUR);
                //ChercherAncienneCaseTouchee(GRILLE_CPU_ADV);
                d3=1;
            }
            if(dead(0))
            {
                printf("\nDiantre !! Vous avez perdu la partie !");
                break;
            }

            tirer(k,1);              // On tire et on affiche

            if(noDetectBoat(CASE_CROISEUR,1)!=c1)  // Si c'est la première foi qu'il n'y a plus de croiseur chez l'ennemi
            {
                printf("\nCroiseur ennemi detruit... ");
                printf("\n");
                c1=1;
            }
            if(noDetectBoat(CASE_SOUSMARIN,1)!=c2)
            {
                printf("\nSous-marin ennemi detruit... ");
                printf("\n");
                c2=1;
            }
            if(noDetectBoat(CASE_TORPILLEUR,1)!=c3)
            {
                printf("\nTorpilleur ennemi detruit... ");
                printf("\n");
                c3=1;
            }
            if(dead(1))
            {
                printf("\nFelicitations !! Vous avez gagne la partie !\n");
                break;
            }
            sleep(2);
        }
    }

    printf("\nVoullez-vous recommencer ? ( Oui : 1 | Non : 0) : ");
    scanf(" %d", nRestart);



}
