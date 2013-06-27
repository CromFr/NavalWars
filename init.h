#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "battle.h"
#include "divers.h"

//DEFINITION VARIABLES GLOBALES
extern int nGrille[4][10][10];

extern int bCpuATouche;
extern struct vect vTouche;
extern int bPaire;

//Liées au réseau
extern struct sockaddr_in si_me, si_other;
extern int sock_send, sock_recv;



void initPosNavires(int bAuto, int IA_or_player); // Interface de demande des positions des navires (type, h ou v)
void placerNavire(int nb_cases, int alignement, int ligne, int colonne, int AI_or_player); // Place le navire sur la grille en fct de son nb de cases
int verifierPlacement(int nb_cases, int alignement, int ligne, int colonne, int AI_or_player); // Vérifie si le placement est correct
void InitGrille(int nType);

#endif // INIT_H_INCLUDED
