#include <stdio.h>
#include <stdlib.h>

#include "../includes/test/test.h"
#include "../includes/afn/afn.h"
#include "../includes/afd/afd.h"

int main()
{
    AFN automate_simple_a = creer_automate_simple_a();
    afficher_afn(automate_simple_a);
    AFD afd = determiniser(automate_simple_a);
    afficher_table_transition(afd.table, automate_simple_a.alphabets);
    afficher_afn(afd.afd);

    char *mot = "aaa";
    int est_accepte = est_mot_accepte(afd.afd, mot);
    fprintf(stdout, "> Le mot \"%s\" est %s : \n", mot, est_accepte ? "accepte" : "non accepte");
}