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
        printf("%d\n", ascii[i]);
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

static Ensemble recuperer_etats_suivants(AFN afn, Etat etat, char symbole)
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

static void afficher_table_transition(TableTransition table_transition, Ensemble alphabets)
{
    // affiche les colonnes
    fprintf(stdout, "+--------------------------------------------------------+\n");
    fprintf(stdout, "| \t Ensemble \t |");
    for (int i = 0; i < alphabets.taille; i++)
    {
        fprintf(stdout, "\t %c \t |", alphabets.elements[i]);
    }
    fprintf(stdout, "\n+--------------------------------------------------------+\n");

    // affiche les lignes
    for (int i = 0; i < table_transition.taille; i++)
    {
        fprintf(stdout, "| \t ");
        afficher_ensemble(table_transition.rows[i].etat);
        fprintf(stdout, " \t |");

        for (int j = 0; j < alphabets.taille; j++)
        {
            fprintf(stdout, "\t");
            afficher_ensemble(table_transition.rows[i].ensembles[j]);
            fprintf(stdout, "\t|");
        }
        fprintf(stdout, "\n");
    }

    // affiche la ligne de fin
    fprintf(stdout, "+--------------------------------------------------------+\n");
}

static void traitement_etats_initiaux(AFN afn, TableTransition *table_transition)
{
    table_transition->taille = cardinalite(afn.etats_initiaux);
    for (int i = 0; i < afn.etats_initiaux.taille; i++)
    {
        table_transition->rows[i].etat = creer_ensemble_singleton(afn.etats_initiaux.elements[i]);
        for (int j = 0; j < afn.alphabets.taille; j++)
        {
            Ensemble etats_suivants = recuperer_etats_suivants(afn, afn.etats_initiaux.elements[i], afn.alphabets.elements[j]);
            table_transition->rows[i].ensembles[j] = etats_suivants;
        }
    }
}

AFN determiniser(AFN afn)
{
    AFN afd = creer_afn();
    TableTransition table_transition;

    traitement_etats_initiaux(afn, &table_transition);
    for (int i = 0; i < table_transition.taille; i++)
    {
        for (int j = 0; j < afn.alphabets.taille; j++)
        {
            if (est_vide(table_transition.rows[i].ensembles[j]))
            {
                continue;
            }

            int existe = 0;
            for (int k = 0; k < table_transition.taille; k++)
            {
                if (est_egal(table_transition.rows[i].ensembles[j], table_transition.rows[k].etat))
                {
                    existe = 1;
                    break;
                }
            }

            if (!existe)
            {
                table_transition.rows[table_transition.taille].etat = table_transition.rows[i].ensembles[j];

                for (int k = 0; k < afn.alphabets.taille; k++)
                {
                    Ensemble etats_suivants = creer_ensemble_vide();
                    for (int l = 0; l < table_transition.rows[i].ensembles[j].taille; l++)
                    {
                        Ensemble etats = recuperer_etats_suivants(afn, table_transition.rows[i].ensembles[j].elements[l], afn.alphabets.elements[k]);
                        etats_suivants = union_ensemble(etats_suivants, etats);
                    }
                    table_transition.rows[table_transition.taille].ensembles[k] = etats_suivants;
                }
                table_transition.taille++;
            }
        }
    }

    afficher_table_transition(table_transition, afn.alphabets);

    return afd;
}

static void afficher_transition(AFN afn)
{
    for (int i = 0; i < MAX_TRANSITIONS; i++)
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