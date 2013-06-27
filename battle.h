#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "reseau.h"
#include "divers.h"







//DEFINITION VARIABLES GLOBALES
extern struct vect vTouche;
extern int bPaire;

//Liées au réseau
extern struct sockaddr_in si_me, si_other;
extern int sock_send, sock_recv;



void tirer(int k, int AI_or_player); // Demande les coordonnées de frappe, les envois, regarde si c'est (à l'eau/touché)
void degats(int AI_or_player, int nDifficulte); // Reçoie les coordonnées de frappe, les comparent et envoie l'état de la case (à l'eau/touché)
int dead(int AI_or_player); // Vérifie si l'on n'est pas mort
int noDetectBoat(int type, int AI_or_player); // Vérifie s'il reste toujours une case (occupée par un type de bateau) non touchée



#endif // BATTLE_H_INCLUDED
