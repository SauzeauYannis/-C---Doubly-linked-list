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

Liste creerListeVide(void);

void viderListe(Liste * liste);

void detruireListe(Liste * liste);


/*------------------------------------*
 * Fonctions vérification de la liste
 *------------------------------------*/

bool estVideListe(Liste liste);


/*------------------------------*
 * Fonctions ajout d'un element
 *------------------------------*/

void ajouterTeteListe(Liste liste, Voiture voiture);

void ajouterQueueListe(Liste liste, Voiture voiture);

void ajouterPosListe(Liste liste, Voiture voiture, int position);


/*------------------------------------*
 * Fonctions suppression d'un element
 *------------------------------------*/

void supprimerTeteListe(Liste liste);

void supprimerQueueListe(Liste liste);

void supprimerPosListe(Liste liste, int position);


/*------------------------------------*
 * Fonctions récupération d'un element
 *------------------------------------*/

Voiture recupTeteListe(Liste liste);

Voiture recupQueueListe(Liste liste);

Voiture recupPosListe(Liste liste, int position);


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