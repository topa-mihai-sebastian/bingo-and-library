#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct // structura de carti corespunzatoare
{
    int ID, anul;
    char titlu[41], autor[21], *descrierea;
} Carte;

void afisare(Carte *vectorCarti, int i)
{ // functia afiseaza cartea individuala
    printf("%d\n", vectorCarti[i].ID);
    printf("%s\n", vectorCarti[i].titlu);
    printf("%s\n", vectorCarti[i].autor);
    printf("%d\n", vectorCarti[i].anul);
    printf("%s\n", vectorCarti[i].descrierea);
}

void search(char element[41], Carte *vectorCarti, int numarCarti) //"element" este ce este dupa comanda
{
    int i, ok = 0;
    if (isdigit(element[0])) // verificam daca primul element este cifra
    {
        // cautam anul
        for (i = 0; i < numarCarti; i++)
        {
            if (vectorCarti[i].anul == atoi(element)) // daca s-a gasit anul afisam cartea respectiva
            {
                afisare(vectorCarti, i);
                ok = 1;
                printf("\n");
            }
        }
        if (ok == 0)
            printf("NOT FOUND\n\n"); // in cazul in care nu s-a gasit anul
    }
    else // este sir de caractere
    {
        ok = 0;
        for (i = 0; i < numarCarti; i++)
        {
            if (strcmp(element, vectorCarti[i].titlu) == 0 || strcmp(element, vectorCarti[i].autor) == 0)
            { // comparam ori cu titlul ori cu autorul
                // daca se gaseste afisam cartea respectiva
                afisare(vectorCarti, i);
                ok = 1;
                printf("\n");
            }
        }
        if (ok == 0) // in cazul in care nu s-a gasit nici titlul nici autorul
            printf("NOT FOUND\n\n");
    }
}

void replace(Carte *vectorCarti, int numarCarti, char *cuvantVechi, char *cuvantNou)
{
    int i;
    for (i = 0; i < numarCarti; i++)
    {
        char *descriereAct, *final, *p;                        // declaram niste auxiliare
        descriereAct = vectorCarti[i].descrierea;              // il initializez
        p = descriereAct;                                      // fac o copie
        final = malloc(strlen(vectorCarti[i].descrierea) + 1); //+1 pentru '\0' ///char are size 1
        final[0] = '\0';                                       // in initializam cu un sir gol
        while (*p != '\0')                                     // cat timp nu dam de finalul sirului
        {
            if (strstr(p, cuvantVechi) == p)
            {
                strcat(final, cuvantNou);
                // "final" v-a fi sirul final, cel pe care il vom copia in descrierea cartii
                p += strlen(cuvantVechi); // mutam cursorul la dreapta cu numarul de elemente a cuvantului vechi
            }
            else
            {
                strncat(final, p, 1);
                // daca nu se gaseste cuvantul vechi se copiaza doar un caracter
                p++;
            }
        }

        strcpy(vectorCarti[i].descrierea, final); // bagam in sirul principal descrierea finala
        free(final);                              // eliberal memoria pentru sirul "final" auxiliar
    }
}

void add_book(Carte *vectorCarti, int pozitie)
{
    scanf("%d", &vectorCarti[pozitie].ID);        // citim ID-ul
    getchar();                                    // golim bufferul
    fgets(vectorCarti[pozitie].titlu, 51, stdin); // citim titlul
    vectorCarti[pozitie].titlu[strlen(vectorCarti[pozitie].titlu) - 1] = '\0';
    fgets(vectorCarti[pozitie].autor, 31, stdin); // citim autorul
    vectorCarti[pozitie].autor[strlen(vectorCarti[pozitie].autor) - 1] = '\0';
    scanf("%d", &vectorCarti[pozitie].anul); // citim anul(numar natural)
    getchar();                               // golim bufferul

    vectorCarti[pozitie].descrierea = (char *)malloc(501 * sizeof(char)); // ii alocam dimensiune maxima
    fgets(vectorCarti[pozitie].descrierea, 501, stdin);                   // citim descrierea si apoi o realocam cu dimenisunea necesara
    vectorCarti[pozitie].descrierea = realloc(vectorCarti[pozitie].descrierea, strlen(vectorCarti[pozitie].descrierea) + 1);
    //+1 pentri'\0'
    vectorCarti[pozitie].descrierea[strlen(vectorCarti[pozitie].descrierea) - 1] = '\0'; // stergem "\n"
}

void citireCarti(Carte *vectorCarti, int numarCarti)
{
    int i;
    for (i = 0; i < numarCarti; i++) // pentru fiecare carte citim caracteristicile ei
    {
        scanf("%d", &vectorCarti[i].ID); // citim ID-ul
        getchar();                       // golim bufferul

        fgets(vectorCarti[i].titlu, 51, stdin); // citim titlul
        vectorCarti[i].titlu[strlen(vectorCarti[i].titlu) - 1] = '\0';
        fgets(vectorCarti[i].autor, 31, stdin); // citim autorul
        vectorCarti[i].autor[strlen(vectorCarti[i].autor) - 1] = '\0';
        scanf("%d", &vectorCarti[i].anul); // citim anul(numar natural)
        getchar();                         // golim bufferul

        vectorCarti[i].descrierea = (char *)malloc(501 * sizeof(char)); // ii alocam dimensiune maxima
        fgets(vectorCarti[i].descrierea, 501, stdin);                   // citim descrierea si apoi o realocam cu dimenisunea necesara
        vectorCarti[i].descrierea = (char *)realloc(vectorCarti[i].descrierea, strlen(vectorCarti[i].descrierea) + 1);
        //+1 pentri'\0'
        vectorCarti[i].descrierea[strlen(vectorCarti[i].descrierea) - 1] = '\0'; // stergem "\n"
    }
}

int main()
{
    int i, numarCarti, numarComenzi;
    scanf("%d", &numarCarti);
    char comanda[200], aux[200];
    Carte *vectorCarti = (Carte *)malloc((numarCarti) * sizeof(Carte));
    // definim un vector de tip Carte si ii  alocam memorie
    getchar(); // GOLIM BUFFERUL
    citireCarti(vectorCarti, numarCarti);
    ///////////////////////
    scanf("%d", &numarComenzi);
    getchar();
    // golim bufferul

    for (i = 0; i < numarComenzi; i++)
    {
        fgets(comanda, 200, stdin);

        comanda[strlen(comanda) - 1] = '\0';

        strcpy(aux, comanda);

        if (strncmp(comanda, "SEARCH", strlen("SEARCH")) == 0)
        {
            strcpy(comanda, comanda + 7);
            //+7 pentru ca elementul respectiv se alfa 7 pozitii mai la dreapta
            search(comanda, vectorCarti, numarCarti);
        }
        else if (strncmp(comanda, "REPLACE", strlen("REPLACE")) == 0)
        {
            char *primulSpatiu = strchr(comanda, ' '), cuvant1[41], cuvant2[41];
            // spatiul de dupa REPLACE
            if (primulSpatiu != NULL)
            {
                char *alDoileaSpatiu = strchr(primulSpatiu + 1, ' ');
                // spatiul de dupa "cuvant1"
                if (alDoileaSpatiu != NULL)
                {
                    int lungimeCuvant1 = alDoileaSpatiu - (primulSpatiu + 1);
                    // calculam lungimea primului cuvant pentru a folosi strncpy
                    strncpy(cuvant1, primulSpatiu + 1, lungimeCuvant1);
                    cuvant1[lungimeCuvant1] = '\0'; // inchidem primul cuvant
                    strcpy(cuvant2, alDoileaSpatiu + 1);
                    // acesta se afla dupa al doilea spatiu
                    replace(vectorCarti, numarCarti, cuvant1, cuvant2);
                }
            }
        }
        else if (strncmp(comanda, "ADD_BOOK", strlen("ADD_BOOK")) == 0)
        {
            numarCarti++;
            // marim numarul de carti deoarece mai adaugam o carte
            vectorCarti = realloc(vectorCarti, (numarCarti) * sizeof(Carte));
            // realocam memoria
            add_book(vectorCarti, numarCarti - 1);
            // adugam cartea la pozitia aia deoarece vectorul porneste de la 0
        }
    }

    printf("%d\n", numarCarti);
    for (i = 0; i < numarCarti; i++)
        afisare(vectorCarti, i);
    // eliberam memoria
    for (i = 0; i < numarCarti; i++)
        free(vectorCarti[i].descrierea); // eliberam memoria pentru descrierea fiecarei carti
    free(vectorCarti);                   // eliberam vectorul de carti
    return 0;
}