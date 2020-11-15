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
        return recupTeteListe(liste);
    }
    // Si la position correspond a la queue de la liste
    else if (position == liste->taille -1)
    {
        return recupQueueListe(liste);
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
    myassert(!estVideListe(liste), "la liste est vide");

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
    myassert(!estVideListe(liste), "la liste est vide");

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
    myassert(!estVideListe(liste), "la liste est vide");
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
    
    self->estTriee = true;
    self->listeVoitures = NULL;

    return self;
}

Collection col_creerCopie(const_Collection source)
{
    Collection self = (Collection)malloc(sizeof(struct CollectionP));

    self->estTriee = source->estTriee;
    self->listeVoitures = creerListeVide();
    
    for(int i = 0; i < source->listeVoitures->taille; i++)
    {   
        // On récupère chaque voiture à la position courante
        Voiture v = recupPosListe(source->listeVoitures, i);
        // Puis on l'ajoute à la queue de la liste
        ajouterQueueListe(self->listeVoitures, voi_creerCopie(v));
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
    myassert(self->listeVoitures != NULL, "La liste ne doit pas être vide");

    return self->listeVoitures->taille;
}

Voiture col_getVoiture(const_Collection self, int pos)
{
    myassert(self->listeVoitures != NULL, "La liste ne doit pas être vide");
    myassert(pos >= 0, "La position doit etre positive");
    myassert(pos < self->listeVoitures->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    return voi_creerCopie(recupPosListe(self->listeVoitures, pos));
}

void col_addVoitureSansTri(Collection self, const_Voiture voiture)
{
    // Creer une copie de voiture pour l'ajouter a la liste
    Voiture v = voi_creerCopie(voiture);

    // Si la liste est null on doit creer une liste vide
    if (self->listeVoitures == NULL)
    {
        self->listeVoitures = creerListeVide();
    }

    ajouterQueueListe(self->listeVoitures, v);

    // Si la taille est de 1 alors la collection est triee
    if (self->listeVoitures->taille == 1)
    {
        self->estTriee = true;
    }
    // Si la taille est differente de 1 alors la collection n'est pas triee
    else
    {
        self->estTriee = false;
    }
}

void col_addVoitureAvecTri(Collection self, const_Voiture voiture)
{
    myassert(self->estTriee, "La collection doit etre triee");

    // Si la liste est null on doit creer une liste vide et y ajouter la premiere voiture
    if (self->listeVoitures == NULL)
    {
        self->listeVoitures = creerListeVide();
        col_addVoitureSansTri(self, voiture);
    }
    // Si la liste n'est pas vide alors au procede a l'ajout avec tri
    else
    {
        // Creer une copie de voiture pour l'ajouter a la liste
        Voiture v = voi_creerCopie(voiture);

        // Initialisation de la voiture sur l'elemennt en tete de liste pour pouvoir comparer les annnes
        Voiture vParcourue = recupTeteListe(self->listeVoitures);
        int i = 0;

        // Je parcourt la liste tant que j'ai pas trouvé une voiture plus recente que la voiture a ajouter
        while (voi_getAnnee(vParcourue) < voi_getAnnee(voiture))
        {
            i++;
            if (i < self->listeVoitures->taille)
            {
                vParcourue = recupPosListe(self->listeVoitures, i);
            }
            else
            {
                break;
            }
        }

        ajouterPosListe(self->listeVoitures, v, i);
    }
}

void col_supprVoitureSansTri(Collection self, int pos)
{
    myassert(self->listeVoitures != NULL, "La liste ne doit pas être vide");
    
    supprimerPosListe(self->listeVoitures, pos);
    self->estTriee = false;
}

void col_supprVoitureAvecTri(Collection self, int pos)
{
    myassert(self->listeVoitures != NULL, "La liste ne doit pas être vide");
    myassert(self->estTriee == true, "La liste doit être trié");

    supprimerPosListe(self->listeVoitures, pos);    
}

void col_trier(Collection self)
{
    if (!self->estTriee)
    {
        for (int i = (self->listeVoitures->taille - 1); i > 0; i--) 
        {
            self->estTriee = true;
            for (int j = 0; j < i; j++)
            {
                Voiture v = recupPosListe(self->listeVoitures, j);
                Voiture vSuivant = recupPosListe(self->listeVoitures, j + 1);

                if (voi_getAnnee(vSuivant) < voi_getAnnee(v))
                {
                    voi_swap(v, vSuivant);
                    self->estTriee = false;
                }
            }
            if (self->estTriee)
            {
                break;
            } 
        }
    }
}


/*----------------------*
 * Fonction d'affichage
 *----------------------*/

void col_afficher(const_Collection self)
{
    myassert(self->listeVoitures != NULL, "La liste ne doit pas être vide");

    int size = self->listeVoitures->taille;

    printf("[************* COLLECTION **************]\n");
    printf("[**** La collection contient %d voitures\n", size);
    
    if(self->estTriee)
    {
        printf("[**** La collection est triée\n");
    } else
    {
        printf("[**** La collection n'est pas triée\n");
    }
    
    for(int i = 0; i < size; i++)
    {
        printf("---------------------------\n");
        printf("Voiture %d : \n", i);
        voi_afficher(recupPosListe(self->listeVoitures, i));
        printf("---------------------------\n");
    }

    printf("[************* FIN AFFICHAGE COLLECTION **************]\n");
}


/*--------------------------------------*
 * Fonctions entrées-sorties fichiers
 *--------------------------------------*/

void col_ecrireFichier(const_Collection self, FILE *fd)
{
    fwrite(&(self->estTriee), sizeof(bool), 1, fd);
    fwrite(&(self->listeVoitures->taille), sizeof(int), 1, fd);

    int size = self->listeVoitures->taille;
    for(int i=0; i<size; i++)
    {
        const_Voiture v = recupPosListe(self->listeVoitures, i);
        voi_ecrireFichier(v, fd);
    }
}

void col_lireFichier(Collection self, FILE *fd)
{
    // Si la liste n'est pas vide alors on la vide
    if (self->listeVoitures != NULL)
    {
        viderListe(self->listeVoitures);
    }

    fread(&(self->estTriee), sizeof(bool), 1, fd);
    int t;
    fread(&t, sizeof(int), 1, fd);

    self->listeVoitures = creerListeVide();
    for (int i = 0; i < t; i++)
    {
        Voiture v = voi_creerFromFichier(fd);
        ajouterPosListe(self->listeVoitures, v, i);
    }
}