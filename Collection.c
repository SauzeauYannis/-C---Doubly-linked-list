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

/*----------*
 * Macros
 *----------*/

#define POS_TETE 0
#define POS_QUEUE(liste) (liste->taille - 1)

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
    Liste list = (Liste) malloc(sizeof(struct ListeP));

    list->taille = 0;
    list->tete = NULL;
    list->queue = NULL;

    return list;
}

void viderListe(Liste liste)
{
    if(liste != NULL)
    {
        while(liste->tete != NULL)
            {
                Element * suiv = liste->tete->suivant;

                // On détruit et libère la mémoire de la voiture de l'élément de la tête
                voi_detruire(&(liste->tete->voiture));
                free(liste->tete->voiture);

                // On libère l'élément précédent
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

void detruireListe(Liste * liste)
{
    if((*liste) != NULL)
    {
        // On vide la liste
        viderListe(*liste);
        
        // Puis on libère la mémoire de la liste
        free((*liste)->tete);
        free((*liste)->queue);
        free(*liste);  
    }
}

/*------------------------------------*
 * Fonctions vérification de la liste
 *------------------------------------*/

bool estVideListe(Liste liste)
{
    // On vérifie si la taille est nulle et si la tete et la queue sont nulles
    return (liste->taille == 0) && (liste->tete == NULL) && (liste->queue == NULL);
}


/*------------------------------------*
 * Fonctions récupération d'un element
 *------------------------------------*/

Element * recupElemPosListe(const_Liste liste, int position)
{
    myassert(position >= POS_TETE, "La position doit etre positive");
    myassert(position <= liste->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    // Si la position correspond à la tête de la liste
    if (position  == POS_TETE)
    {
        return liste->tete;
    }
    // Si la position correspond à la queue de la liste
    else if (position == POS_QUEUE(liste))
    {
        return liste->queue;
    }
    // Si la position correspond ni à la tete ni à la queue
    else
    {
        Element * elem = NULL;

        // Si la position est plus proche de la tete on rentre par la tete
        if(position < (liste->taille / 2))
        {
            elem = liste->tete;

            for (int i = POS_TETE; i < position; i++)
            {
                elem = elem->suivant;
            }
            
            return elem;
        }
        // Si la position est plus proche de la queue on rentre par la queue
        else
        {
            elem = liste->queue;

            for (int i = POS_QUEUE(liste); i > position; i--)
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
    myassert(position >= POS_TETE, "La position doit être positive");
    myassert(position <= liste->taille, "La position ne doit pas être plus grande que la taille de la liste");

    // Si la position correspond a la tete de la liste
    if (position  == POS_TETE)
    {
        return recupTeteListe(liste);
    }
    // Si la position correspond a la queue de la liste
    else if (position == POS_QUEUE(liste))
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
    // On ajoute un seul et unique élément quand la liste est vide
    // l'élément n'a pas de suivant ni de précédent
    elem->precedent = NULL;
    elem->suivant = NULL;

    // Le nouvel élément est la tete et la queue de la liste 
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
        // Le suivant est l'ancienne tete et n'a pas de precedent
        elem->suivant = liste->tete;
        elem->precedent = NULL;

        // L'ancienne tete a la nouvelle tete en précédent
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
    // Si il y a déjà des elements dans la liste
    else
    {
        // L'élément précédent est l'ancienne queue et n'a pas de suivant
        elem->precedent = liste->queue;
        elem->suivant = NULL;

        // L'ancienne queue à la nouvelle queue en suivant
        (liste->queue)->suivant = elem;

        // Seule la queue change
        liste->queue = elem;
    }
    
    liste->taille++;
}

void ajouterPosListe(Liste liste, Voiture voiture, int position)
{
    myassert(position >= POS_TETE, "La position doit etre positive");
    myassert(position <= liste->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    // Si la position correspond a la tete de la liste
    if (position  == POS_TETE)
    {
        ajouterTeteListe(liste, voiture);
    }
    // Si la position correspond a la queue de la liste
    else if (position == (POS_QUEUE(liste) + 1))
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

        // On met à jour le suivant du precedent de l'element qui a ete ajoute
        prec->suivant = elem;

        // On met à jour le precedent du suivant de l'element qui a ete ajoute
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

    // S'il n'ya qu'un élément dans la liste, on la vide
    if(liste->taille == 1)
    {
        viderListe(liste);
    }
    else
    {
        // S'il y'a plusieurs éléments dans la liste
       Element * suiv = liste->tete->suivant;

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

    // S'il n'ya qu'un élément dans la liste, on la vide
    if(liste->taille == 1)
    {
        viderListe(liste);
    }
    else 
    {
        // S'il y'a plusieurs éléments dans la liste
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
    myassert(position >= POS_TETE, "La position doit etre positive");
    myassert(position <= liste->taille, "La position ne doit pas etre plus grande que la taille de la liste");

    Element* elem = recupElemPosListe(liste, position);
    Element* suiv = elem->suivant;
    Element* pred = elem->precedent;
 

        if(position == POS_TETE)
        {
            supprimerTeteListe(liste); 
        }
        else if(position == POS_QUEUE(liste))
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
    Collection self = (Collection) malloc(sizeof(struct CollectionP));
    
    self->estTriee = true;
    self->listeVoitures = NULL;

    return self;
}

Collection col_creerCopie(const_Collection source)
{
    Collection self = (Collection) malloc(sizeof(struct CollectionP));

    self->estTriee = source->estTriee;
    self->listeVoitures = creerListeVide();
    
    for(int i = POS_TETE; i <= POS_QUEUE(source->listeVoitures); i++)
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
    myassert(!estVideListe(self->listeVoitures), "La liste ne doit pas être vide");

    return self->listeVoitures->taille;
}

Voiture col_getVoiture(const_Collection self, int pos)
{
    myassert(self->listeVoitures != NULL, "La liste ne doit pas être vide");
    myassert(pos >= POS_TETE, "La position doit etre positive");
    myassert(pos <= self->listeVoitures->taille, "La position ne doit pas etre plus grande que la taille de la liste");

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

    // Puis on ajoute la voiture à la queue
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
    // Si la liste n'est pas vide alors au procède a l'ajout avec tri
    else
    {
        // Creer une copie de voiture pour l'ajouter a la liste
        Voiture v = voi_creerCopie(voiture);

        // Initialisation de la voiture sur l'elemennt en tete de liste pour pouvoir comparer les annnes
        Voiture vParcourue = recupTeteListe(self->listeVoitures);
        int i = POS_TETE;

        // On parcourt la liste tant qu'on a pas trouvé une voiture plus recente que la voiture a ajouter
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
        // Puis on l'ajoute à la position trouvé
        ajouterPosListe(self->listeVoitures, v, i);
    }
}

void col_supprVoitureSansTri(Collection self, int pos)
{
    myassert(!estVideListe(self->listeVoitures), "La liste ne doit pas être vide");
    
    supprimerPosListe(self->listeVoitures, pos);
    
    // On supprime un élément sans tri la liste n'est alors plus trié
    self->estTriee = false;
}

void col_supprVoitureAvecTri(Collection self, int pos)
{
    myassert(!estVideListe(self->listeVoitures), "La liste ne doit pas être vide");
    myassert(self->estTriee == true, "La liste doit être trié");

    supprimerPosListe(self->listeVoitures, pos);    
}

void col_trier(Collection self)
{
    // On trie la liste uniquement si elle n'est pas déjà triée
    if (!self->estTriee)
    {
        // On parcourt de la queue à la tête
        for (int i = POS_QUEUE(self->listeVoitures); i > POS_TETE; i--) 
        {
            // On dit suppose que la liste est trié
            self->estTriee = true;

            // On parcourt de la tête jusqu'à l'indice - 1 de la boucle précédente
            for (int j = POS_TETE; j < i; j++)
            {
                // On récupère la voiture parcourue et celle qui suit
                Voiture v = recupPosListe(self->listeVoitures, j);
                Voiture vSuivant = recupPosListe(self->listeVoitures, j + 1);

                // Si l'année de la voiture suivante est plus petit que l'année 
                // de la voiture parcourue, alors la liste n'est pas triée
                if (voi_getAnnee(vSuivant) < voi_getAnnee(v))
                {
                    // On échange les deux voitures et on dit donc que la liste
                    // n'est pas triée
                    voi_swap(v, vSuivant);
                    self->estTriee = false;
                }
            }
            // S'il il n'y a pas eu d'échange de voitures alors c'est que la liste
            // est déjà triée on peut donc arrêté le parcours de la liste
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
    if (estVideListe(self->listeVoitures))
    {
        printf("[************* COLLECTION **************]\n");
        printf("[**** La collection est vide\n");
        printf("[************* FIN AFFICHAGE COLLECTION **************]\n");
    }
    else
    {
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
        
        for(int i = POS_TETE; i <= POS_QUEUE(self->listeVoitures); i++)
        {
            printf("---------------------------\n");
            printf("Voiture %d : \n", i);
            voi_afficher(recupPosListe(self->listeVoitures, i));
            printf("---------------------------\n");
        }

        printf("[************* FIN AFFICHAGE COLLECTION **************]\n");
    }
}


/*--------------------------------------*
 * Fonctions entrées-sorties fichiers
 *--------------------------------------*/

void col_ecrireFichier(const_Collection self, FILE *fd)
{
    // On écrit dans le fichier si la collection est triée puis le nombre de voiture
    fwrite(&(self->estTriee), sizeof(bool), 1, fd);
    fwrite(&(self->listeVoitures->taille), sizeof(int), 1, fd);

    for(int i = POS_TETE; i <= POS_QUEUE(self->listeVoitures); i++)
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

    // On lit le booleen de tri est la taille
    fread(&(self->estTriee), sizeof(bool), 1, fd);
    int t;
    fread(&t, sizeof(int), 1, fd);

    // Puis on lit chaque voiture du fichier
    self->listeVoitures = creerListeVide();
    for (int i = POS_TETE; i < t; i++)
    {
        Voiture v = voi_creerFromFichier(fd);
        ajouterPosListe(self->listeVoitures, v, i);
    }
}