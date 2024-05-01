#include "../../includes/test/test.h"

AFN creer_automate_simple_a()
{
    AFN automate = creer_afn();

    Etat etats[] = {1, 2};
    definir_etats(&automate, etats, 2);

    char *alphabets = "a";
    definir_alphabets(&automate, alphabets, 1);

    ajouter_etat_initial(&automate, 1);
    ajouter_etat_final(&automate, 2);

    ajouter_transition(&automate, 1, 'a', 2);
    return automate;
}

AFN creer_automate_simple_ab()
{
    AFN automate = creer_afn();

    Etat etats[] = {1, 2, 3};
    definir_etats(&automate, etats, 3);

    char *alphabets = "ab";
    definir_alphabets(&automate, alphabets, 2);

    ajouter_etat_initial(&automate, 1);
    ajouter_etat_final(&automate, 3);

    ajouter_transition(&automate, 1, 'a', 1);
    ajouter_transition(&automate, 1, 'b', 1);
    ajouter_transition(&automate, 1, 'a', 2);
    ajouter_transition(&automate, 2, 'b', 3);

    return automate;
}

AFN creer_automate_complex_ab()
{
    AFN automate = creer_afn();

    Etat etats[] = {1, 2, 3};
    definir_etats(&automate, etats, 3);

    char *alphabets = "ab";
    definir_alphabets(&automate, alphabets, 2);

    ajouter_etat_initial(&automate, 1);
    // ajouter_etat_initial(&automate, 2);

    ajouter_etat_final(&automate, 2);
    // ajouter_etat_final(&automate, 3);

    ajouter_transition(&automate, 1, 'a', 2);
    ajouter_transition(&automate, 1, 'b', 2);

    ajouter_transition(&automate, 2, 'a', 3);

    ajouter_transition(&automate, 3, 'b', 2);
    ajouter_transition(&automate, 3, 'a', 1);
    ajouter_transition(&automate, 3, 'b', 1);

    return automate;
}

AFN creer_automate_complex_abc()
{
    AFN automate = creer_afn();

    Etat etats[] = {1, 2, 3};
    definir_etats(&automate, etats, 3);

    char *alphabets = "abc";
    definir_alphabets(&automate, alphabets, 2);

    ajouter_etat_initial(&automate, 1);
    ajouter_etat_initial(&automate, 2);

    ajouter_etat_final(&automate, 2);
    ajouter_etat_final(&automate, 3);

    ajouter_transition(&automate, 1, 'a', 2);
    ajouter_transition(&automate, 1, 'b', 2);
    ajouter_transition(&automate, 1, 'c', 2);

    ajouter_transition(&automate, 2, 'a', 3);
    ajouter_transition(&automate, 2, 'b', 3);
    ajouter_transition(&automate, 2, 'c', 3);

    ajouter_transition(&automate, 3, 'b', 2);
    ajouter_transition(&automate, 3, 'a', 1);
    ajouter_transition(&automate, 3, 'b', 1);
    ajouter_transition(&automate, 3, 'c', 1);

    return automate;
}
