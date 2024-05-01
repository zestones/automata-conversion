#ifndef _AFN_H_
#define _AFN_H_

#include <stdio.h>
#include <stdlib.h>

#include "../ensemble/ensemble.h"

#define MAX_ALPHABET 256
#define MAX_TRANSITIONS 100

typedef struct
{
    Etat depart;
    char symbole;
    Etat arrivee;
} Transition;

typedef struct
{
    Transition transitions[MAX_TRANSITIONS];
    int taille_transitions;

    Ensemble etats_initiaux;
    Ensemble etats_finaux;
    Ensemble etats;
    Ensemble alphabets;
} AFN;

AFN creer_afn();

void definir_etats(AFN *afn, Etat *etats, int taille);

void definir_alphabets(AFN *afn, char *alphabets, int taille);

void ajouter_etat_final(AFN *afn, Etat etat);

void ajouter_etat_initial(AFN *afn, Etat etat);

void ajouter_transition(AFN *afn, Etat depart, char symbole, Etat arrivee);

Ensemble recuperer_etats_suivants(AFN afn, Etat etat, char symbole);

void afficher_afn(AFN afn);

#endif