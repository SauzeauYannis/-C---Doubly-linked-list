#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "myassert.h"

#include "Voiture.h"
#include "Liste.h"
#include "Collection.h"

#define MAX_LEN 1000


int main()
{
	// Liste mylist = creerListeVide();
    // bool b1 = estVideListe(mylist);
    // printf("%d \n", b1);

    Voiture v1, v2, v3, v4, v5, v6, v7;
    const char *tmp[2] = {"1234 AE 75", "VH 529 FE"};
    v1 = voi_creer("Voiture 1", 2001, 10, 2, tmp);
    v2 = voi_creer("Voiture 2", 2002, 20, 2, tmp);
    v3 = voi_creer("Voiture 3", 2003, 30, 2, tmp);
    v4 = voi_creer("Voiture 4", 2004, 40, 2, tmp);
    v5 = voi_creer("Voiture 5", 2005, 50, 2, tmp);
    v6 = voi_creer("Voiture 6", 2006, 60, 2, tmp);
    v7 = voi_creer("Voiture 7", 2007, 70, 2, tmp);

    /*------------------------
     * Test ajouterTeteListe
     *------------------------*/

    // ajouterTeteListe(mylist, v1);
    // ajouterTeteListe(mylist, v2);
    // ajouterTeteListe(mylist, v3);
    // ajouterTeteListe(mylist, v4);
    // ajouterTeteListe(mylist, v5);
    // ajouterTeteListe(mylist, v6);
    // ajouterTeteListe(mylist, v7);

    /*------------------------
     * Test ajouterQueueListe
     *------------------------*/

    // ajouterQueueListe(mylist, v1);
    // ajouterQueueListe(mylist, v2);
    // ajouterQueueListe(mylist, v3);
    // ajouterQueueListe(mylist, v4);
    // ajouterQueueListe(mylist, v5);
    // ajouterQueueListe(mylist, v6);
    // ajouterQueueListe(mylist, v7);

    /*----------------------
     * Test ajouterPosListe
     *---------------------*/

    // ajouterPosListe(mylist, v1, 0);
    // ajouterPosListe(mylist, v7, 1);
    // ajouterPosListe(mylist, v2, 1);
    // ajouterPosListe(mylist, v3, 2);
    // ajouterPosListe(mylist, v6, 3);
    // ajouterPosListe(mylist, v4, 3);
    // ajouterPosListe(mylist, v5, 4);

    // viderListe(mylist);

    /*----------------------
     * Test Affichage
     *---------------------*/
    
    // voi_afficher(recupPosListe(mylist, 0));
    // voi_afficher(recupPosListe(mylist, 1));
    // voi_afficher(recupPosListe(mylist, 2));
    // voi_afficher(recupPosListe(mylist, 3));
    // voi_afficher(recupPosListe(mylist, 4));
    // voi_afficher(recupPosListe(mylist, 5));
    // voi_afficher(recupPosListe(mylist, 6));

    /*-------------------------
     * Test supprimerTeteListe
     *------------------------*/

    // supprimerTeteListe(mylist);
    // supprimerTeteListe(mylist);
    // supprimerTeteListe(mylist);
    // supprimerTeteListe(mylist);
    // supprimerTeteListe(mylist);
    // supprimerTeteListe(mylist);
    // supprimerTeteListe(mylist);

    /*--------------------------
     * Test supprimerQueueListe
     *-------------------------*/

    // supprimerQueueListe(mylist);
    // supprimerQueueListe(mylist);
    // supprimerQueueListe(mylist);
    // supprimerQueueListe(mylist);
    // supprimerQueueListe(mylist);
    // supprimerQueueListe(mylist);
    // supprimerQueueListe(mylist);

    /*--------------------------
     * Test supprimerQueueListe
     *-------------------------*/

    // supprimerPosListe(mylist, 0);
    // supprimerPosListe(mylist, 2);
    // supprimerPosListe(mylist, 1);
    // supprimerPosListe(mylist, 3);
    // supprimerPosListe(mylist, 1);  
    // supprimerPosListe(mylist, 1);
    // supprimerPosListe(mylist, 0);

    // viderListe(mylist);

    // detruireListe(&mylist);

    /*----------------------
     * Test Collection
     *---------------------*/

    Collection mycol = col_creer();

<<<<<<< HEAD
    printf("nb voitures : %d\n", col_getNbVoitures(mycol));
    Voiture v = col_getVoiture(mycol, 0);

    col_afficher(mycol);
    
    col_vider(mycol);

    col_detruire(&mycol);
=======
    /*-----------------------------
     * Test col_addVoitureSansTri
     *----------------------------*/

    // col_addVoitureSansTri(mycol, v1);
    // col_addVoitureSansTri(mycol, v2);
    // col_addVoitureSansTri(mycol, v3);
    // col_addVoitureSansTri(mycol, v4);
    // col_addVoitureSansTri(mycol, v5);
    // col_addVoitureSansTri(mycol, v6);
    // col_addVoitureSansTri(mycol, v7);

    /*-----------------------------
     * Test col_addVoitureAvecTri
     *----------------------------*/

    col_addVoitureAvecTri(mycol, v1);
    col_addVoitureAvecTri(mycol, v3);
    col_addVoitureAvecTri(mycol, v7);
    col_addVoitureAvecTri(mycol, v5);
    col_addVoitureAvecTri(mycol, v2);
    col_addVoitureAvecTri(mycol, v4);
    col_addVoitureAvecTri(mycol, v6);

    /*------------------------
     * Test col_getVoiture()
     *-----------------------*/

    voi_afficher(col_getVoiture(mycol, 0));
    voi_afficher(col_getVoiture(mycol, 1));
    voi_afficher(col_getVoiture(mycol, 2));
    voi_afficher(col_getVoiture(mycol, 3));
    voi_afficher(col_getVoiture(mycol, 4));
    voi_afficher(col_getVoiture(mycol, 5));
    voi_afficher(col_getVoiture(mycol, 6));
    
    col_vider(mycol);

    col_detruire(&mycol);

    voi_detruire(&v1);
    voi_detruire(&v2);
    voi_detruire(&v3);
    voi_detruire(&v4);
    voi_detruire(&v5);
    voi_detruire(&v6);
    voi_detruire(&v7);
>>>>>>> 60ff58eec9620d59a4a49ccdf2c42d61b45d1236

    return EXIT_SUCCESS;
}
