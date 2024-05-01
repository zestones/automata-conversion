#include "../../includes/afn/afn.h"

AFN creer_afn()
{
    AFN afn;

    afn.etats = creer_ensemble_vide();
    afn.etats_finaux = creer_ensemble_vide();
    afn.etats_initiaux = creer_ensemble_vide();

    for (int i = 0; i < MAX_TRANSITIONS; i++)
    {
        afn.transitions[i].depart = -1;
        afn.transitions[i].symbole = '\0';
        afn.transitions[i].arrivee = -1;
    }

    afn.taille_transitions = 0;
    return afn;
}

void definir_etats(AFN *afn, Etat *etats, int taille)
{
    afn->etats = creer_ensemble(etats, taille);
}

void definir_alphabets(AFN *afn, char *alphabets, int taille)
{
    Etat ascii[taille];
    for (int i = 0; i < taille; i++)
    {
        ascii[i] = (int)alphabets[i];
    }

    afn->alphabets = creer_ensemble(ascii, taille);
}

void ajouter_etat_final(AFN *afn, Etat etat)
{
    ajouter_element(&afn->etats_finaux, etat);
}

void ajouter_etat_initial(AFN *afn, Etat etat)
{
    ajouter_element(&afn->etats_initiaux, etat);
}

void ajouter_transition(AFN *afn, Etat depart, char symbole, Etat arrivee)
{
    for (int i = 0; i < MAX_TRANSITIONS; i++)
    {
        if (afn->transitions[i].depart == -1)
        {
            afn->transitions[i].depart = depart;
            afn->transitions[i].symbole = symbole;
            afn->transitions[i].arrivee = arrivee;
            afn->taille_transitions++;
            break;
        }
    }
}

Ensemble recuperer_etats_suivants(AFN afn, Etat etat, char symbole)
{
    Ensemble etats_suivants = creer_ensemble_vide();
    for (int i = 0; i < afn.taille_transitions; i++)
    {
        if (afn.transitions[i].depart == etat && afn.transitions[i].symbole == symbole)
        {
            ajouter_element(&etats_suivants, afn.transitions[i].arrivee);
        }
    }

    return etats_suivants;
}

static void afficher_transition(AFN afn)
{
    printf("Transitions:\n");
    printf("+--------+---------+---------+\n");
    printf("| Depart | Symbole | Arrivee |\n");
    printf("+--------+---------+---------+\n");
    for (int i = 0; i < MAX_TRANSITIONS; i++)
    {
        if (afn.transitions[i].depart == -1)
        {
            break;
        }

        printf("|   %2d   |    %c    |   %2d    |\n", afn.transitions[i].depart, afn.transitions[i].symbole, afn.transitions[i].arrivee);
    }
    printf("+--------+---------+---------+\n");
}

void afficher_afn(AFN afn)
{
    printf("\nEtats initiaux: ");
    afficher_ensemble(afn.etats_initiaux);

    printf("\nEtats finaux: ");
    afficher_ensemble(afn.etats_finaux);

    printf("\n\n");
    afficher_transition(afn);
}