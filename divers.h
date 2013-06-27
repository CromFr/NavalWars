#ifndef DIVERS_H_INCLUDED
#define DIVERS_H_INCLUDED

#include <stdlib.h>
#include "cpu.h"

#define CASE_VIDE 0
#define CASE_PLOUF 1
#define CASE_TOUCHE 2
#define CASE_CROISEUR 3
#define CASE_SOUSMARIN 4
#define CASE_TORPILLEUR 5


#define GRILLE_JOU_OWN 0
#define GRILLE_JOU_ADV 1
#define GRILLE_CPU_OWN 2
#define GRILLE_CPU_ADV 3
#define GRILLE_ALL 10

//DEFINITION VARIABLES GLOBALES
extern struct vect vTouche;
extern int bPaire;

//Liées au réseau
extern struct sockaddr_in si_me, si_other;
extern int sock_send, sock_recv;


int GetIsVectorValid(struct vect vVector);
void SetVectorInvalid(struct vect *vVector);
int RandomAB(int a, int b);



#endif // DIVERS_H_INCLUDED
