/************************************************
 * Module de Collection : corps
 * Auteurs : Benjamin Chevais et Yannis Sauzeau
 ************************************************/


/*----------------*
 * Include System
 *----------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*---------------*
 * Include perso
 *---------------*/

#include "Voiture.h"
#include "Collection.h"
#include "myassert.h"
#include "Liste.h"

/*-----------------------*
 * Structure de la liste
 *-----------------------*/

typedef struct element
{
    Voiture voiture;
    struct element * precedent;
    struct element * suivant;
} Element;

struct ListeP
{
    int taille;
    Element * tete;
    Element * queue;
};

typedef struct ListeP * Liste;
typedef const struct ListeP * const_Liste;


/*-------------------------------------*
 * Fonctions initialisation de la liste
 *-------------------------------------*/

Liste creerListeVide(void)
{
    Liste list = (Liste)malloc(sizeof(struct ListeP));

    list->taille = 0;
    list->tete = NULL;
    list->queue = NULL;

    return list;
}

void detruireListe(Liste * liste)
{
    if((*liste) != NULL)
    {
        while((*liste)->tete->suivant != NULL)
        {
            // On détruit et libère la mémoire de la voiture de l'élément de la tête
            voi_detruire(&((*liste)->tete->voiture));
            printf("test1\n");
            
            free((*liste)->tete->voiture);
            printf("test2\n");
            
            // On libère la mémoire de la tête
            
            printf("test3\n");
            Element* suiv = (*liste)->tete->suivant;
            
            (*liste)->tete = NULL;
            printf("test4\n");
            
            free((*liste)->tete);
             printf("test5\n");
            
            // On pointe le prochain élément sur la tête
            (*liste)->tete = suiv;
            printf("test6\n");
        }
        
        // On libère la mémoire de la liste
        printf("test7\n");
        (*liste) = NULL;
        
        printf("test8\n");
        free(liste);
        printf("test9\n");
        
    } else {
        myassert((*liste) == NULL, "La liste est nulle");        
    }
}

void viderListe(Liste * liste)
{
    while((*liste)->tete->suivant != NULL)
    {
        // On détruit et libère la mémoire de la voiture de l'élément de la tête
        voi_detruire(&(*liste)->tete->voiture);
        free((*liste)->tete->voiture);
        // On libère la mémoire de la tête
        (*liste)->tete = NULL;
        free((*liste)->tete);
        // On pointe le prochain élément sur la tête
        (*liste)->tete = (*liste)->tete->suivant;
    }
    (*liste)->queue = NULL;
    (*liste)->taille = 0;
}


/*------------------------------------*
 * Fonctions vérification de la liste
 *------------------------------------*/

bool estVideListe(Liste liste)
{
    return (liste->taille == 0) && (liste->tete == NULL) && (liste->queue ==NULL);
}


/*------------------------------*
 * Fonctions ajout d'un element
 *------------------------------*/

void ajouterTeteListe(Liste liste, Voiture voiture)
{
    // Nouvel element à ajouter
    Element * elem = (Element *) malloc(sizeof(struct element));
    elem->voiture = voiture;

    // Si il n'y a pas d'element dans la liste
    if (estVideListe(liste))
    {
        ajouterListeVide(liste, elem);
    }
    // Si il y a déjà des elements dans la liste
    else
    {
        // Suivant est l'ancienne tete et pas de precedent
        elem->suivant = (Element *) malloc(sizeof(struct element));
        elem->suivant = liste->tete;
        elem->precedent = NULL;

        // L'ancienne tete a la nouvelle tete en precedent
        (liste->tete)->precedent = elem;

        // Seule la tete change
        liste->tete = elem;
    }
    
    liste->taille++;
}

void ajouterQueueListe(Liste liste, Voiture voiture)
{
    // Nouvel element à ajouter
    Element * elem = (Element *) malloc(sizeof(struct element));
    elem->voiture = voiture;

    // Si il n'y a pas d'element dans la liste
    if (estVideListe(liste))
    {
        ajouterListeVide(liste, elem);
    }
    // Si il y a deja des elements dans la liste
    else
    {
        // Precedent est l'ancienne queue et pas de suivant
        elem->precedent = (Element *) malloc(sizeof(struct element));
        elem->precedent = liste->queue;
        elem->suivant = NULL;

        // L'ancienne queue a la nouvelle queue en suivant
        (liste->queue)->suivant = elem;

        // Seule la queue change
        liste->queue = elem;
    }
    
    liste->taille++;
}

void ajouterPosListe(Liste liste, Voiture voiture, int position)
{
    myassert(position >= 0, "La position doit etre positive");
    myassert(position <= liste->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    // Si la position correspond a la tete de la liste
    if (position  == 0)
    {
        ajouterTeteListe(liste, voiture);
    }
    // Si la position correspond a la queue de la liste
    else if (position == liste->taille)
    {
        ajouterQueueListe(liste, voiture);
    }
    // Si la position correspond ni a la tete ni a la queue
    else
    {
        // Nouvel element à ajouter
        Element * elem = (Element *) malloc(sizeof(struct element));
        elem->voiture = voiture;

        // On stocke le futur precedent et le futur suivant de l'element a ajouter
        Element * suiv;
        Element * prec;

        // Si la position est plus proche de la tete on rentre par la tete
        if(position < (liste->taille / 2))
        {
            // On prend la tete de la liste
            suiv = liste->tete->suivant;
            prec = liste->tete;

            // On parcours la liste pour avoir le futur precedent et le futur suivant de l'element a ajouter
            for (int i = 1; i < position; i++)
            {
                suiv = suiv->suivant;
                prec = suiv->precedent;
            }
        }
        // Si la position est plus proche de la queue on rentre par la queue
        else
        {
            // On prend la queue de la liste
            suiv = liste->queue;
            prec = liste->queue->precedent;

            // On parcours la liste pour avoir le futur precedent et le futur suivant de l'element a ajouter
            for (int i = 1; i < position; i++)
            {
                prec = prec->precedent;
                suiv = prec->suivant;
            }
        }

        // On met l'element precedent et suivant dans le nouveau element
        elem->precedent = (Element *) malloc(sizeof(struct element));
        elem->suivant = (Element *) malloc(sizeof(struct element));
        elem->precedent = prec;
        elem->suivant = suiv;

        // On met a jour le suivant du precedent de l'element qui a ete ajoute
        prec->suivant = elem;

        // On met a jour le precedent du suivant de l'element qui a ete ajoute
        suiv->precedent = elem;
    
        liste->taille++;
    }
}

void ajouterListeVide(Liste liste, Element * elem)
{
    // Pas de suivant ni précédent
    elem->precedent = NULL;
    elem->suivant = NULL;

    // La tete et la queue sont le nouveau element
    liste->tete = (Element *) malloc(sizeof(struct element));
    liste->queue = (Element *) malloc(sizeof(struct element));
    liste->tete = elem;
    liste->queue = elem;
}


/*------------------------------------*
 * Fonctions suppression d'un element
 *------------------------------------*/

void supprimerTeteListe(Liste liste);

void supprimerQueueListe(Liste liste);

void supprimerPosListe(Liste liste, int position);


/*------------------------------------*
 * Fonctions récupération d'un element
 *------------------------------------*/

Voiture recupTeteListe(const_Liste liste)
{
    return liste->tete->voiture;
}

Voiture recupQueueListe(const_Liste liste);

Voiture recupPosListe(Liste liste, int position)
{
    Element * elem = liste->tete;

    for (int i = 0; i < position; i++)
    {
        elem = elem->suivant;
    }

    return elem->voiture;
}


/*---------------------------*
 * Structure de la collection
 *---------------------------*/

struct CollectionP
{
	bool estTriee;
    Liste listeVoitures;
};


/*------------------------------------------*
 * Fonctions initialisation de la structure
 *------------------------------------------*/

Collection col_creer();

Collection col_creerCopie(const_Collection source);

void col_detruire(Collection *pself);

void col_vider(Collection self);


/*------------------------*
 * Focntions d'accesseurs
 *------------------------*/

int col_getNbVoitures(const_Collection self);

Voiture col_getVoiture(const_Collection self, int pos);

void col_addVoitureSansTri(Collection self, const_Voiture voiture);

void col_addVoitureAvecTri(Collection self, const_Voiture voiture);

void col_supprVoitureSansTri(Collection self, int pos);

void col_supprVoitureAvecTri(Collection self, int pos);

void col_trier(Collection self);


/*----------------------*
 * Fonction d'affichage
 *----------------------*/

void col_afficher(const_Collection self);


/*--------------------------------------*
 * Fonctions entrées-sorties fichiers
 *--------------------------------------*/

void col_ecrireFichier(const_Collection self, FILE *fd);

void col_lireFichier(Collection self, FILE *fd);
