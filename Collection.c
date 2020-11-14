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
            voi_detruire(&(*liste)->tete->voiture);
            free((*liste)->tete->voiture);
            // On libère la mémoire de la tête
            (*liste)->tete = NULL;
            free((*liste)->tete);
            // On pointe le prochain élément sur la tête
            (*liste)->tete = (*liste)->tete->suivant;
        }
        // On libère la mémoire de la liste
        free(*liste);
        (*liste) = NULL;
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
        // L'ancienne tete a l'elem en precedent


        // Suivant est l'ancienne tete et pas de precedent
        elem->suivant = (Element *) malloc(sizeof(struct element));
        elem->suivant = liste->tete;
        elem->precedent = NULL;

        // Seule la tete change
        liste->tete = elem;
    }
    
    liste->taille++;
}

void ajouterQueueListe(Liste liste, Voiture voiture)
{
    // Nouvel element à ajouter

    Element * elem = (Element *) malloc(sizeof(struct element));

    // Si il n'y a pas d'element dans la liste
    if (estVideListe(liste))
    {
        ajouterListeVide(liste, elem);
    }
    // Si il y a déjà des elements dans la liste
    else
    {

    }
    
    liste->taille++;
}

void ajouterPosListe(Liste liste, Voiture voiture, int position)
{
    // Nouvel element à ajouter

    Element * elem = (Element *) malloc(sizeof(struct element));

    // Si il n'y a pas d'element dans la liste
    if (estVideListe(liste))
    {
        ajouterListeVide(liste, elem);
    }
    // Si il y a déjà des elements dans la liste
    else
    {

    }
    
    liste->taille++;
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
    
}

Voiture recupQueueListe(const_Liste liste)
{
    
}

Voiture recupPosListe(Liste liste, int position)
{
    
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
