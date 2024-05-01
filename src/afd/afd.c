#include "../../includes/afd/afd.h"

void afficher_table_transition(TableTransition table_transition, Ensemble alphabets)
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

AFD determiniser(AFN afn)
{
    AFD afd;
    afd.afd = creer_afn();

    traitement_etats_initiaux(afn, &afd.table);
    for (int i = 0; i < afd.table.taille; i++)
    {
        for (int j = 0; j < afn.alphabets.taille; j++)
        {
            if (est_vide(afd.table.rows[i].ensembles[j]))
            {
                continue;
            }

            int existe = 0;
            for (int k = 0; k < afd.table.taille; k++)
            {
                if (est_egal(afd.table.rows[i].ensembles[j], afd.table.rows[k].etat))
                {
                    existe = 1;
                    break;
                }
            }

            if (!existe)
            {
                afd.table.rows[afd.table.taille].etat = afd.table.rows[i].ensembles[j];
                for (int k = 0; k < afn.alphabets.taille; k++)
                {
                    Ensemble etats_suivants = creer_ensemble_vide();
                    for (int l = 0; l < afd.table.rows[i].ensembles[j].taille; l++)
                    {
                        Ensemble etats = recuperer_etats_suivants(afn, afd.table.rows[i].ensembles[j].elements[l], afn.alphabets.elements[k]);
                        etats_suivants = union_ensemble(etats_suivants, etats);
                    }
                    afd.table.rows[afd.table.taille].ensembles[k] = etats_suivants;
                }
                afd.table.taille++;
            }
        }
    }

    for (int i = 0; i < afd.table.taille; i++)
    {
        for (int j = 0; j < afn.etats_finaux.taille; j++)
        {
            if (appartient(afd.table.rows[i].etat, afn.etats_finaux.elements[j]))
            {
                ajouter_etat_final(&afd.afd, i);
                break;
            }
        }

        // TODO: comment determiner les etats initiaux de l'afd
        for (int j = 0; j < afn.etats_initiaux.taille; j++)
        {
            if (appartient(afd.table.rows[i].etat, afn.etats_initiaux.elements[j]))
            {
                ajouter_etat_initial(&afd.afd, i);
                break;
            }
        }
    }

    for (int i = 0; i < afd.table.taille; i++)
    {
        for (int j = 0; j < afn.alphabets.taille; j++)
        {
            for (int k = 0; k < afd.table.taille; k++)
            {
                if (est_egal(afd.table.rows[i].ensembles[j], afd.table.rows[k].etat))
                {
                    ajouter_transition(&afd.afd, i, afn.alphabets.elements[j], k);
                    break;
                }
            }
        }
    }

    return afd;
}
