#include <stdio.h>
#include <stdlib.h>

#include "../includes/test/test.h"
#include "../includes/afn/afn.h"
#include "../includes/afd/afd.h"

int main()
{
    // Premier automate : a
    AFN automate_simple_a = creer_automate_simple_a();
    afficher_afn(automate_simple_a);
    AFD afd = determiniser(automate_simple_a);
    afficher_afd(afd);

    char *mot = "aa";
    int est_accepte = est_mot_accepte(automate_simple_a, mot);
    fprintf(stdout, "> Le mot \"%s\" est : %s \n", mot, est_accepte ? "Accepte" : "Non Accepte");

    mot = "a";
    est_accepte = est_mot_accepte(automate_simple_a, mot);
    fprintf(stdout, "> Le mot \"%s\" est : %s \n", mot, est_accepte ? "Accepte" : "Non Accepte");

    // --------------------------------- //
    //    Deuxième automate : b*a+b
    // --------------------------------- //
    AFN automate_simple_ab = creer_automate_simple_ab();
    afficher_afn(automate_simple_ab);
    afd = determiniser(automate_simple_ab);
    afficher_table_transition(afd.table, automate_simple_ab.alphabets);
    afficher_afd(afd);

    mot = "a";
    est_accepte = est_mot_accepte(afd.afd, mot);
    fprintf(stdout, "> Le mot \"%s\" est : %s \n", mot, est_accepte ? "Accepte" : "Non Accepte");

    mot = "babbbbbbaaaaaaaab";
    est_accepte = est_mot_accepte(automate_simple_ab, mot);
    fprintf(stdout, "> Le mot \"%s\" est : %s \n", mot, est_accepte ? "Accepte" : "Non Accepte");

    // --------------------------------- //
    //    Troisième automate :
    // --------------------------------- //
    AFN automate_complex_ab = creer_automate_complex_ab();
    afficher_afn(automate_complex_ab);
    afd = determiniser(automate_complex_ab);
    afficher_afd(afd);

    mot = "aabbaab";
    est_accepte = est_mot_accepte(automate_complex_ab, mot);
    fprintf(stdout, "> Le mot \"%s\" est : %s \n", mot, est_accepte ? "Accepte" : "Non Accepte");

    // --------------------------------- //
    //    Quatrième automate :
    // --------------------------------- //
    AFN automate_complex_abc = creer_automate_complex_abc();
    afficher_afn(automate_complex_abc);
    afd = determiniser(automate_complex_abc);
    afficher_afd(afd);

    mot = "abc";
    est_accepte = est_mot_accepte(automate_complex_abc, mot);
    fprintf(stdout, "> Le mot \"%s\" est : %s \n", mot, est_accepte ? "Accepte" : "Non Accepte");

    exit(EXIT_SUCCESS);
}