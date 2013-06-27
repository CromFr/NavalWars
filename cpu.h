#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "battle.h"
#include "divers.h"
#include "ui.h"

//Constantes
#define DIFFICULTE_FACILE 1
#define DIFFICULTE_MOYEN 2
#define DIFFICULTE_DIFFICILE 3
#define DIFFICULTE_TRES_DIFFICILE 4



//Structure vector
struct vect
{
int x;
int y;
};

//Structure vecteur prioritaires
struct vectprio
{
int x;
int y;
int prio;
};

//DEFINITION VARIABLES GLOBALES
extern int nGrille[4][10][10];

extern int bCpuATouche;
extern struct vect vTouche;
extern int bPaire;
extern struct vect vPrecedent;
extern int firstTime;              // En global
extern struct vectprio everTried[9]; //

//Liées au réseau
extern struct sockaddr_in si_me, si_other;
extern int sock_send, sock_recv;


void ActionCPU(int nDifficulte);
struct vect CoordAleatoire(int nDifficulte, int bPaire);
void TirerCPU(struct vect vTirer);
void GetPriorities(struct vectprio *vpPossibilites);
void SystAntiDepassementCPU(int nSens, int nDirection, int *nX, int *nY, struct vectprio *vpPossibilites);
void ScanAndConvertPLOUF(int nGrilleType, int nTypeToConvert);
void ChercherAncienneCaseTouchee(int nGrilleType);

int caseVide(int ligne, int colonne, int IA_or_player);
void niveauMoyen2(void);
void switchGrille(int ligne, int colonne);
void randomCase(int* ligne, int* colonne);
int VerifCaseAdj2(int ligne, int colonne);
void PutCaseAdj2(int ligne, int colonne);



#endif // CPU_H_INCLUDED
