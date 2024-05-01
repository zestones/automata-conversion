#include "../../includes/afn/afn.h"

AFN creer_afn()
{
    AFN afn;

    afn.etats = creer_ensemble_vide();
    afn.etats_finaux = creer_ensemble_vide();
    afn.etats_initiaux = creer_ensemble_vide();

    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        afn.transitions[i].depart = -1;
        afn.transitions[i].symbole = '\0';
        afn.transitions[i].arrivee = -1;
    }

    return afn;
}

void definir_etats(AFN *afn, Etat *etats, int taille)
{
    afn->etats = cree_ensemble(etats, taille);
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
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        if (afn->transitions[i].depart == -1)
        {
            afn->transitions[i].depart = depart;
            afn->transitions[i].symbole = symbole;
            afn->transitions[i].arrivee = arrivee;
            break;
        }
    }
}

static void afficher_transition(AFN afn)
{
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        if (afn.transitions[i].depart == -1)
        {
            break;
        }

        printf("%d -- %c --> %d\n", afn.transitions[i].depart, afn.transitions[i].symbole, afn.transitions[i].arrivee);
    }
}

void afficher_afn(AFN afn)
{
    printf("Etats initiaux: ");
    afficher_ensemble(afn.etats_initiaux);

    printf("\nEtats finaux: ");
    afficher_ensemble(afn.etats_finaux);

    printf("\nTransitions:\n");
    afficher_transition(afn);
}