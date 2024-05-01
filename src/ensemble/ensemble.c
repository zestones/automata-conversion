#include "../../includes/ensemble/ensemble.h"

Ensemble creer_ensemble_vide()
{
    Ensemble ensemble;
    ensemble.taille = 0;
    return ensemble;
}

Ensemble cree_ensemble_singleton(Etat element)
{
    Ensemble ensemble;
    ensemble.taille = 1;
    ensemble.elements[0] = element;
    return ensemble;
}

Ensemble cree_ensemble(Etat *elements, int taille)
{
    Ensemble ensemble;
    ensemble.taille = taille;

    for (int i = 0; i < taille; i++)
    {
        ensemble.elements[i] = elements[i];
    }

    return ensemble;
}

Ensemble union_ensemble(Ensemble ensemble1, Ensemble ensemble2)
{
    Ensemble ensemble;
    ensemble.taille = ensemble1.taille + ensemble2.taille;

    for (int i = 0; i < ensemble1.taille; i++)
    {
        ensemble.elements[i] = ensemble1.elements[i];
    }

    for (int i = 0; i < ensemble2.taille; i++)
    {
        if (!appartient(ensemble1, ensemble2.elements[i]))
        {
            ensemble.elements[ensemble1.taille + i] = ensemble2.elements[i];
        }
    }

    return ensemble;
}

int appartient(Ensemble ensemble, Etat element)
{
    for (int i = 0; i < ensemble.taille; i++)
    {
        if (ensemble.elements[i] == element)
        {
            return 1;
        }
    }

    return 0;
}

void ajouter_element(Ensemble *ensemble, Etat element)
{
    if (!appartient(*ensemble, element))
    {
        ensemble->elements[ensemble->taille] = element;
        ensemble->taille++;
    }
}

void supprimer_element(Ensemble *ensemble, Etat element)
{
    for (int i = 0; i < ensemble->taille; i++)
    {
        if (ensemble->elements[i] == element)
        {
            for (int j = i; j < ensemble->taille - 1; j++)
            {
                ensemble->elements[j] = ensemble->elements[j + 1];
            }

            ensemble->taille--;
            break;
        }
    }
}

void afficher_ensemble(Ensemble ensemble)
{
    printf("{");

    for (int i = 0; i < ensemble.taille; i++)
    {
        printf("%d", ensemble.elements[i]);

        if (i < ensemble.taille - 1)
        {
            printf(", ");
        }
    }

    printf("}\n");
}