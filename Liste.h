/*-------------------------------------*
 * DECLARATION DES METHODES DE LISTE.H
 *-------------------------------------*/

#ifndef LISTE_H
#define LISTE_H

/*-----------------------*
 * Structure de la liste
 *-----------------------*/
typedef struct element Element;

struct ListeP;

typedef struct ListeP * Liste;
typedef const struct ListeP * const_Liste;

/*-------------------------------------*
 * Fonctions initialisation de la liste
 *-------------------------------------*/

Liste creerListeVide(void);

void detruireListe(Liste * liste);

void viderListe(Liste liste);

/*------------------------------------*
 * Fonctions vérification de la liste
 *------------------------------------*/

bool estVideListe(Liste liste);

/*------------------------------------*
 * Fonctions récupération d'un element
 *------------------------------------*/

Element * recupElemPosListe(const_Liste liste, int position);

Voiture recupTeteListe(const_Liste liste);

Voiture recupQueueListe(const_Liste liste);

Voiture recupPosListe(const_Liste liste, int position);

/*------------------------------*
 * Fonctions ajout d'un element
 *------------------------------*/

void ajouterListeVide(Liste liste, Element * elem);

void ajouterTeteListe(Liste liste, Voiture voiture);

void ajouterQueueListe(Liste liste, Voiture voiture);

void ajouterPosListe(Liste liste, Voiture voiture, int position);

/*------------------------------------*
 * Fonctions suppression d'un element
 *------------------------------------*/

void supprimerTeteListe(Liste liste);

void supprimerQueueListe(Liste liste);

void supprimerPosListe(Liste liste, int position);

#endif
