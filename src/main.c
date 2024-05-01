#include <stdio.h>
#include <stdlib.h>

#include "../includes/afn/afn.h"

int main()
{
    AFN afn = creer_afn();

    Etat etats[] = {0, 1, 2, 3};
    definir_etats(&afn, etats, 4);

    ajouter_etat_initial(&afn, 0);
    ajouter_etat_final(&afn, 3);

    ajouter_transition(&afn, 0, 'a', 0);
    ajouter_transition(&afn, 0, 'b', 0);
    ajouter_transition(&afn, 0, 'a', 1);
    ajouter_transition(&afn, 1, 'b', 3);

    afficher_afn(afn);
}