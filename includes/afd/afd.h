#ifndef _AFD_H_
#define _AFD_H_

#include <stdio.h>
#include <stdlib.h>

#include "../afn/afn.h"

typedef struct
{
    Ensemble etat;
    Ensemble ensembles[MAX_ALPHABET];
} Row;

typedef struct
{
    Row rows[MAX_TRANSITIONS];
    int taille;
} TableTransition;

typedef struct
{
    AFN afd;
    TableTransition table;
} AFD;

AFD determiniser(AFN afn);

void afficher_table_transition(TableTransition table_transition, Ensemble alphabets);

void afficher_afd(AFD afd);

#endif
