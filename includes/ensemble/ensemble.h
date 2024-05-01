#ifndef _ENSEMBLE_H_
#define _ENSEMBLE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Etat;

typedef struct
{
    int taille;
    Etat *elements;
} Ensemble;

Ensemble creer_ensemble_vide();

Ensemble creer_ensemble_singleton(Etat element);

Ensemble creer_ensemble(Etat *elements, int taille);

int cardinalite(Ensemble ensemble);

int est_vide(Ensemble ensemble);

int est_egal(Ensemble ensemble1, Ensemble ensemble2);

Ensemble intersection_non_vide(Ensemble ensemble1, Ensemble ensemble2);

Ensemble union_ensemble(Ensemble ensemble1, Ensemble ensemble2);

int appartient(Ensemble ensemble, Etat element);

void ajouter_element(Ensemble *ensemble, Etat element);

void supprimer_element(Ensemble *ensemble, Etat element);

void afficher_ensemble(Ensemble ensemble);

#endif
