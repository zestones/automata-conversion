#include <stdio.h>
#include <stdlib.h>

#include "../includes/afn/afn.h"

int main()
{
    AFN afn = creer_afn();

    Etat etats[] = {1, 2, 3};
    definir_etats(&afn, etats, 3);

    char *alphabets = "ab";
    definir_alphabets(&afn, alphabets, 2);

    ajouter_etat_initial(&afn, 1);
    ajouter_etat_final(&afn, 3);

    ajouter_transition(&afn, 1, 'a', 1);
    ajouter_transition(&afn, 1, 'b', 1);
    ajouter_transition(&afn, 1, 'a', 2);
    ajouter_transition(&afn, 2, 'b', 3);

    afficher_afn(afn);
    AFN afd = determiniser(afn);

    // AFN afn = creer_afn();

    // Etat etats[] = {1, 2, 3};
    // definir_etats(&afn, etats, 3);

    // char *alphabets = "ab";
    // definir_alphabets(&afn, alphabets, 2);

    // ajouter_etat_initial(&afn, 1);
    // ajouter_etat_final(&afn, 2);

    // ajouter_transition(&afn, 1, 'a', 2);
    // ajouter_transition(&afn, 1, 'b', 2);

    // ajouter_transition(&afn, 2, 'a', 3);

    // ajouter_transition(&afn, 3, 'b', 2);
    // ajouter_transition(&afn, 3, 'b', 1);
    // ajouter_transition(&afn, 3, 'a', 1);

    // afficher_afn(afn);
    // AFN afd = determiniser(afn);
}