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
        while((*liste)->tete != NULL)
        {
            Element * suiv = (*liste)->tete->suivant;

            // On détruit et libère la mémoire de la voiture de l'élément de la tête
            voi_detruire(&((*liste)->tete->voiture));
            free((*liste)->tete->voiture);

            // On libère l'élément et précédents
            free((*liste)->tete->precedent);
                        
            // On pointe le prochain élément sur la tête
            (*liste)->tete = suiv;
        }
        
        // On libère la mémoire de la liste
        free((*liste)->tete);
        free((*liste)->queue);
        free(*liste);  
    }
}

void viderListe(Liste liste)
{
    if(liste != NULL)
    {
        while(liste->tete != NULL)
            {
                Element* suiv = liste->tete->suivant;

                // On détruit et libère la mémoire de la voiture de l'élément de la tête
                voi_detruire(&(liste->tete->voiture));
                free(liste->tete->voiture);

                // On libère l'élément et précédents
                free(liste->tete->precedent);

               // On pointe le prochain élément sur la tête
                liste->tete = suiv;
            }
        // On libère le dernier élément de la queue
        free(liste->queue);

        // On réinitialise les valeurs de la liste
        liste->tete = NULL;
        liste->queue = NULL;
        liste->taille = 0;
    }
}


/*------------------------------------*
 * Fonctions vérification de la liste
 *------------------------------------*/

bool estVideListe(Liste liste)
{
    return (liste->taille == 0) && (liste->tete == NULL) && (liste->queue == NULL);
}


/*------------------------------------*
 * Fonctions récupération d'un element
 *------------------------------------*/

Element * recupElemPosListe(const_Liste liste, int position)
{
    myassert(position >= 0, "La position doit etre positive");
    myassert(position < liste->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    // Si la position correspond a la tete de la liste
    if (position  == 0)
    {
        return liste->tete;
    }
    // Si la position correspond a la queue de la liste
    else if (position == (liste->taille - 1))
    {
        return liste->queue;
    }
    // Si la position correspond ni a la tete ni a la queue
    else
    {
        Element * elem = NULL;

        // Si la position est plus proche de la tete on rentre par la tete
        if(position < (liste->taille / 2))
        {
            elem = liste->tete;

            for (int i = 0; i < position; i++)
            {
                elem = elem->suivant;
            }
            
            return elem;
        }
        // Si la position est plus proche de la queue on rentre par la queue
        else
        {
            elem = liste->queue;

            for (int i = (liste->taille - 1); i > position; i--)
            {
                elem = elem->precedent;
            }
            
            return elem;
        }
    }
}

Voiture recupTeteListe(const_Liste liste)
{
    return liste->tete->voiture;
}

Voiture recupQueueListe(const_Liste liste)
{
    return liste->queue->voiture;
}

Voiture recupPosListe(const_Liste liste, int position)
{      
    myassert(position >= 0, "La position doit etre positive");
    myassert(position < liste->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    // Si la position correspond a la tete de la liste
    if (position  == 0)
    {
        recupTeteListe(liste);
    }
    // Si la position correspond a la queue de la liste
    else if (position == liste->taille)
    {
        recupQueueListe(liste);
    }
    // Si la position correspond ni a la tete ni a la queue
    else
    {
        Element * elem = recupElemPosListe(liste, position);

        return elem->voiture;
    }
}


/*------------------------------*
 * Fonctions ajout d'un element
 *------------------------------*/

void ajouterListeVide(Liste liste, Element * elem)
{
    // Pas de suivant ni précédent
    elem->precedent = NULL;
    elem->suivant = NULL;

    // La tete et la queue sont le nouveau element
    liste->tete = elem;
    liste->queue = elem;
}

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
        // Nouvel element a ajouter
        Element * elem = (Element *) malloc(sizeof(struct element));
        elem->voiture = voiture;

        // On stocke le futur precedent et le futur suivant de l'element a ajouter
        Element * suiv = recupElemPosListe(liste, position);
        Element * prec = suiv->precedent;

        // On met l'element precedent et suivant dans le nouveau element
        elem->precedent = prec;
        elem->suivant = suiv;

        // On met a jour le suivant du precedent de l'element qui a ete ajoute
        prec->suivant = elem;

        // On met a jour le precedent du suivant de l'element qui a ete ajoute
        suiv->precedent = elem;
    
        liste->taille++;
    }
}


/*------------------------------------*
 * Fonctions suppression d'un element
 *------------------------------------*/

void supprimerTeteListe(Liste liste)
{
    myassert(!estVideListe(liste), "La liste est vide");

    if(liste->taille == 1)
    {
        viderListe(liste);
    }
    else
    {
       Element* suiv = liste->tete->suivant;

        // On détruit et libère la mémoire de la voiture de l'élément de la tête
        voi_detruire(&(liste->tete->voiture));
        free(liste->tete->voiture);

        // On libère la tête courante de la liste
        free(liste->tete);
    
        // On pointe le prochain élément sur la tête de la liste
        liste->taille--;
        liste->tete = suiv;
        liste->tete->precedent = NULL;
    }
}

void supprimerQueueListe(Liste liste)
{
    myassert(!estVideListe(liste), "La liste est vide");

    if(liste->taille == 1)
    {
        viderListe(liste);
    }
    else 
    {
        Element* pred = liste->queue->precedent;
    
        // On détruit et libère la mémoire de la voiture de l'élément de la queue
        voi_detruire(&(liste->queue->voiture));
        free(liste->queue->voiture);
    
        // On libère la queue courante de la liste
        free(liste->queue);

        // On pointe le prochain élément sur la tête de la liste
        liste->taille--;
        liste->queue = pred;
        liste->queue->suivant = NULL;
    }
}

void supprimerPosListe(Liste liste, int position)
{
    myassert(liste->taille > 0, "la taille de la liste doit être strictement supérieur à 0");
    myassert(position >= 0, "La position doit etre positive");
    myassert(position <= liste->taille, "La position ne doit pas etre plus grande que la taille de la liste");

        Element* elem = recupElemPosListe(liste, position);
        Element* suiv = elem->suivant;
        Element* pred = elem->precedent;
 
        // On pointe les bonnes valeurs pour les suivants et précédents

        if(position == 0)
        {
            supprimerTeteListe(liste); 
        }
        else if(position == liste->taille-1)
        {
            supprimerQueueListe(liste);  
        } 
        else if(liste->taille == 1)
        {
            viderListe(liste);
        } 
        else
        {
            elem->suivant->precedent = pred;
            elem->precedent->suivant = suiv;
         
            // On détruit la voiture de l'élément à la position donné
            voi_detruire(&(elem->voiture));
            free(elem->voiture);

            // On libère l'élément de la position courante
            free(elem);        
            liste->taille--;
        }
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

Collection col_creer()
{
    Collection self = (Collection)malloc(sizeof(struct CollectionP));
    
    self->estTriee = false;
    self->listeVoitures = NULL;

    return self;
}

Collection col_creerCopie(const_Collection source)
{
    Collection self = (Collection)malloc(sizeof(struct CollectionP));

    self->estTriee = source->estTriee;
    
    int size = source->listeVoitures->taille;
    for(int i=0; i<size; i++)
    {   
        // On récupère chaque voiture à la position courante
        Voiture v = recupPosListe(source, i);
        // Puis on l'ajoute à la queue de la liste
        ajouterQueueListe(self, voi_creerCopie(v));
    }

    return self;
}

void col_detruire(Collection *pself)
{
    detruireListe(&((*pself)->listeVoitures));
    free(*pself);
}

void col_vider(Collection self)
{
    viderListe(self->listeVoitures);
    self->estTriee = false;
}


/*------------------------*
 * Focntions d'accesseurs
 *------------------------*/

int col_getNbVoitures(const_Collection self)
{
    myassert(self->listeVoitures != NULL, "col_getNbvoitures : la liste ne doit pas être vide");

    return self->listeVoitures->taille;
}

Voiture col_getVoiture(const_Collection self, int pos)
{
    myassert(self->listeVoitures != NULL, "col_getVoiture : la liste ne doit pas être vide");
    myassert(pos >= 0, "La position doit etre positive");
    myassert(pos <= self->listeVoitures->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    return recupPosListe(self, pos);
}

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
