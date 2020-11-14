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
	Liste mylist = creerListeVide();
    bool b1 = estVideListe(mylist);
    printf("%d \n", b1);

    Voiture v1, v2, v3;
    char tmpMarque[MAX_LEN+1];
    char tmpImmatriculation[MAX_LEN+1];

    const char *tmp[2] = {"1234 AE 75", "VH 529 FE"};
    v1 = voi_creer("Trombine", 2005, 34587, 2, tmp);
    v2 = voi_creerCopie(v1);
    v3 = voi_creerCopie(v1);
    voi_addImmatriculation(v2, "VY 749 RT");
    voi_setKilometrage(v2, 38951);

    ajouterTeteListe(mylist, v1);
    ajouterTeteListe(mylist, v2);
    ajouterPosListe(mylist, v2, 1);

    voi_afficher(recupTeteListe(mylist));
    voi_afficher(recupPosListe(mylist, 1));
    voi_afficher(recupPosListe(mylist, 2));

    //detruireListe(&mylist);

    return EXIT_SUCCESS;
}
