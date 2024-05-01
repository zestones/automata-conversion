#include "../../includes/ensemble/ensemble.h"

Ensemble creer_ensemble_vide()
{
    Ensemble ensemble;
    ensemble.taille = 0;
    return ensemble;
}

Ensemble creer_ensemble_singleton(Etat element)
{
    Ensemble ensemble;
    ensemble.taille = 1;
    ensemble.elements = (Etat *)malloc(sizeof(Etat));
    ensemble.elements[0] = element;
    return ensemble;
}

Ensemble creer_ensemble(Etat *elements, int taille)
{
    Ensemble ensemble;
    ensemble.taille = taille;
    ensemble.elements = (Etat *)malloc(taille * sizeof(Etat));

    for (int i = 0; i < taille; i++)
    {
        ensemble.elements[i] = elements[i];
    }

    return ensemble;
}

int cardinalite(Ensemble ensemble) { return ensemble.taille; }

int est_vide(Ensemble ensemble)
{
    return ensemble.taille == 0;
}

int est_egal(Ensemble ensemble1, Ensemble ensemble2)
{
    if (ensemble1.taille != ensemble2.taille)
    {
        return 0;
    }

    for (int i = 0; i < ensemble1.taille; i++)
    {
        if (!appartient(ensemble2, ensemble1.elements[i]))
        {
            return 0;
        }
    }

    return 1;
}

Ensemble intersection_non_vide(Ensemble ensemble1, Ensemble ensemble2)
{
    Ensemble ensemble;
    ensemble.taille = 0;
    ensemble.elements = (Etat *)malloc(ensemble1.taille * sizeof(Etat));

    for (int i = 0; i < ensemble1.taille; i++)
    {
        if (appartient(ensemble2, ensemble1.elements[i]))
        {
            ensemble.elements[ensemble.taille] = ensemble1.elements[i];
            ensemble.taille++;
        }
    }

    return ensemble;
}

Ensemble union_ensemble(Ensemble ensemble1, Ensemble ensemble2)
{
    Ensemble ensemble;
    int taille = 0;
    ensemble.taille = ensemble1.taille + ensemble2.taille;
    ensemble.elements = (Etat *)malloc((ensemble.taille) * sizeof(Etat));

    for (int i = 0; i < ensemble1.taille; i++)
    {
        ensemble.elements[i] = ensemble1.elements[i];
        taille++;
    }

    for (int i = 0; i < ensemble2.taille; i++)
    {
        if (!appartient(ensemble, ensemble2.elements[i]))
        {
            ensemble.elements[taille] = ensemble2.elements[i];
            taille++;
        }
    }

    ensemble.taille = taille;
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
        ensemble->elements = (Etat *)realloc(ensemble->elements, (ensemble->taille + 1) * sizeof(Etat));
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

    printf("}");
}