#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "divers.h"

#define CLRSCR printf("\33[H\33[2J")//printf("\033[2J\033[1;1H")

//DEFINITION VARIABLES GLOBALES
extern int nGrille[4][10][10];

extern int bCpuATouche;
extern struct vect vTouche;
extern int bPaire;

//Liées au réseau
extern struct sockaddr_in si_me, si_other;
extern int sock_send, sock_recv;


void AfficherGrille();



#endif // UI_H_INCLUDED
