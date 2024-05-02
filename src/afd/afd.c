#include "../../includes/afd/afd.h"

void afficher_table_transition(TableTransition table_transition, Ensemble alphabets)
{
    fprintf(stdout, "\n\n==========================================================\n");
    fprintf(stdout, "      Table de transition de l'automate deterministe      \n");
    fprintf(stdout, "==========================================================\n");

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

static void trouver_etats_finaux(AFD *afd, AFN afn)
{
    for (int i = 0; i < afd->table.taille; i++)
    {
        for (int j = 0; j < cardinalite(afn.etats_finaux); j++)
        {
            if (appartient(afd->table.rows[i].etat, afn.etats_finaux.elements[j]))
            {
                ajouter_etat_final(&afd->afd, i + 1);
                break;
            }
        }
    }
}

static void trouver_transitions(AFD *afd, AFN afn)
{
    for (int i = 0; i < afd->table.taille; i++)
    {
        for (int j = 0; j < cardinalite(afn.alphabets); j++)
        {
            for (int k = 0; k < afd->table.taille; k++)
            {
                if (est_egal(afd->table.rows[i].ensembles[j], afd->table.rows[k].etat))
                {
                    ajouter_transition(&afd->afd, i + 1, afn.alphabets.elements[j], k + 1);
                    break;
                }
            }
        }
    }
}

static void trouver_etat_initial(AFD *afd, AFN afn)
{
    for (int i = 0; i < afd->table.taille; i++)
    {
        if (est_egal(afd->table.rows[i].etat, afn.etats_initiaux))
        {
            ajouter_etat_initial(&afd->afd, i + 1);
            break;
        }
    }
}

static void traitement_etats_initiaux(AFD *afd, AFN afn)
{
    afd->table.taille = 1;
    afd->table.rows[0].etat = afn.etats_initiaux;
    for (int i = 0; i < cardinalite(afn.alphabets); i++)
    {
        Ensemble etats_suivants = creer_ensemble_vide();
        for (int j = 0; j < cardinalite(afn.etats_initiaux); j++)
        {
            Ensemble etats = recuperer_etats_suivants(afn, afn.etats_initiaux.elements[j], afn.alphabets.elements[i]);
            etats_suivants = union_ensemble(etats_suivants, etats);
        }
        afd->table.rows[0].ensembles[i] = etats_suivants;
    }
}

AFD determiniser(AFN afn)
{
    AFD afd;
    afd.afd = creer_afn();
    afd.afd.alphabets = afn.alphabets;

    traitement_etats_initiaux(&afd, afn);
    for (int i = 0; i < afd.table.taille; i++)
    {
        for (int j = 0; j < cardinalite(afn.alphabets); j++)
        {
            // On ignore les ensembles vides
            if (est_vide(afd.table.rows[i].ensembles[j]))
            {
                continue;
            }

            // On vérifie si l'ensemble existe déjà dans la table
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
                for (int k = 0; k < cardinalite(afn.alphabets); k++)
                {
                    Ensemble etats_suivants = creer_ensemble_vide();
                    for (int l = 0; l < cardinalite(afd.table.rows[i].ensembles[j]); l++)
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

    trouver_etat_initial(&afd, afn);
    trouver_etats_finaux(&afd, afn);
    trouver_transitions(&afd, afn);

    return afd;
}

void afficher_afd(AFD afd)
{
    fprintf(stdout, "\n\n==========================================================\n");
    fprintf(stdout, "           Automate deterministe equivalent      \n");
    fprintf(stdout, "==========================================================\n");

    afficher_table_transition(afd.table, afd.afd.alphabets);
    afficher_afn(afd.afd);
}