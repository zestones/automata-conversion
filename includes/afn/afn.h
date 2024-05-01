#ifndef _AFN_H_
#define _AFN_H_

#include <stdio.h>
#include <stdlib.h>

#include "../ensemble/ensemble.h"

typedef struct
{
    Etat depart;
    char symbole;
    Etat arrivee;
} Transition;

typedef struct
{
    Transition transitions[MAX_ELEMENTS];

    Ensemble etats_initiaux;
    Ensemble etats_finaux;
    Ensemble etats;
} AFN;

AFN creer_afn();

void definir_etats(AFN *afn, Etat *etats, int taille);

void ajouter_etat_final(AFN *afn, Etat etat);

void ajouter_etat_initial(AFN *afn, Etat etat);

void ajouter_transition(AFN *afn, Etat depart, char symbole, Etat arrivee);

AFN determiniser(AFN afn);

void afficher_afn(AFN afn);

#endif