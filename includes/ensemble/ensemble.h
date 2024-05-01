#ifndef _ENSEMBLE_H_
#define _ENSEMBLE_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

typedef int Etat;

typedef struct
{
    int taille;
    Etat elements[MAX_ELEMENTS];
} Ensemble;

Ensemble creer_ensemble_vide();

Ensemble cree_ensemble_singleton(Etat element);

Ensemble cree_ensemble(Etat *elements, int taille);

Ensemble union_ensemble(Ensemble ensemble1, Ensemble ensemble2);

int appartient(Ensemble ensemble, Etat element);

void ajouter_element(Ensemble *ensemble, Etat element);

void supprimer_element(Ensemble *ensemble, Etat element);

void afficher_ensemble(Ensemble ensemble);

#endif
