#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "myassert.h"

#include "Voiture.h"
#include "Liste.h"
#include "Collection.h"


int main(int argc, char const *argv[])
{
	Liste mylist = creerListeVide();
    bool b1 = estVideListe(mylist);
    printf("%d \n", b1);
    return 0;
}
