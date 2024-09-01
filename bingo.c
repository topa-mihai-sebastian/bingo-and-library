#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void interschimbareColoane(int v[200][5][5], int numarCarduri, int coloana1, int coloana2) // functia specifica bilei SWAP
{
    int k, i, aux;
    for (k = 0; k < numarCarduri; k++)
        for (i = 0; i < 5; i++)
        // interschimbam valorile dorite folosind un auxiliar
        {
            aux = v[k][i][coloana1];
            v[k][i][coloana1] = v[k][i][coloana2];
            v[k][i][coloana2] = aux;
        }
}

void ordonareCrescatoare(int v[200][5][5], int numarCarduri, int n) // functia specifica bilei ASC
{                                                                   // sortom coloana dorita folosind Bubble Sort
    int i, j, k, aux;
    for (k = 0; k < numarCarduri; k++)
        for (i = 0; i < 5; i++)
            for (j = 0; j < 4; j++)
                if (abs(v[k][j][n]) > abs(v[k][j + 1][n]))
                {
                    aux = v[k][j][n];
                    v[k][j][n] = v[k][j + 1][n];
                    v[k][j + 1][n] = aux;
                }
}

void ordonareDescrescatoare(int v[200][5][5], int numarCarduri, int n) // functia specifica bilei DSC
{
    // sortom coloana dorita folosind Bubble Sort
    int k, i, j, aux;
    for (k = 0; k < numarCarduri; k++)
        for (i = 0; i < 5; i++)
            for (j = 0; j < 4; j++)
                if (abs(v[k][j][n]) < abs(v[k][j + 1][n]))
                {
                    aux = v[k][j][n];
                    v[k][j][n] = v[k][j + 1][n];
                    v[k][j + 1][n] = aux;
                }
}

void mutareCiclica(int v[200][5][5], int numarCarduri, int coloana, int elemente) // functia specifica bilei SHIFT
{
    int aux, i, k, j;
    for (k = 0; k < numarCarduri; k++)
    {
        for (i = 0; i < elemente; i++)
        {
            aux = v[k][4][coloana];
            for (j = 4; j > 0; j--)
            {
                v[k][j][coloana] = v[k][j - 1][coloana];
            }
            v[k][0][coloana] = aux;
        }
    }
}

void citire(int v[200][5][5], int n) // functie de citire
{                                    // citim valorile tuturor cardurilor
    int k, i, j;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < 5; i++)
            for (j = 0; j < 5; j++)
                scanf("%d", &v[k][i][j]);
        v[k][2][2] = -v[k][2][2];
    }
}

void afisare(int v[5][5]) // functie de afisare
{
    // afisam valorile unui card
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
            if (v[i][j] < 0)
                printf("%c ", '#');
            else
                printf("%d ", v[i][j]);
        printf("\n");
    }
}

int valoareMaxima(int v[200], int N) // vreau sa vad care este valoarea maxima din vectorul de punctaje
{
    int i, max;
    max = v[0];
    for (i = 0; i < N; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

void verificare(int carduri[200][5][5], int punctaj[200], int N)
{ // aici calculam puntcajul fiecarui jucator
    int contorCarduri, i, j;
    for (contorCarduri = 0; contorCarduri < N; contorCarduri++)
    {
        for (i = 0; i < 5; i++) // cautarea pe linii
            for (j = 0; j < 5; j++)
                if (carduri[contorCarduri][i][j] > 0)
                    break;
                else if (j == 4)
                    punctaj[contorCarduri] += 10;
        for (i = 0; i < 5; i++) // cautarea pe coloane
            for (j = 0; j < 5; j++)
                if (carduri[contorCarduri][j][i] > 0)
                    break;
                else if (j == 4)
                    punctaj[contorCarduri] += 10;

        for (i = 0; i < 5; i++) // cautarea pe diagonala principala
            if (carduri[contorCarduri][i][i] > 0)
                break;
            else if (i == 4)
                punctaj[contorCarduri] += 10;

        for (i = 0; i < 5; i++) // cautarea pe idagonala secundara
            if (carduri[contorCarduri][i][4 - i] > 0)
                break;
            else if (i == 4)
                punctaj[contorCarduri] += 10;
    }
}

void citireBile(int carduri[200][5][5], int punctaj[200], int M, int N)
{
    int max = 0, ok = 0; // punctajul maxim de pana acum
    int contorBile, i, contorCarduri;
    char bilaCurenta[100], AUX[100];
    for (contorBile = 0; contorBile < M; contorBile++)
    {
        scanf("%s", bilaCurenta); // citim bila
        if (strlen(bilaCurenta) == 8)
        { // bila swap
            interschimbareColoane(carduri, N, atoi(&bilaCurenta[5]), atoi(&bilaCurenta[7]));
        }
        else if (strlen(bilaCurenta) == 9)
        { // bila shift
            mutareCiclica(carduri, N, atoi(&bilaCurenta[6]), atoi(&bilaCurenta[8]));
        }
        else if (strncmp(bilaCurenta, "SHOW", 4) == 0)
        {
            // bila show
            afisare(carduri[atoi(bilaCurenta + 5)]);
        }
        else if (strlen(bilaCurenta) == 5)
        {
            if (bilaCurenta[0] == 'A') // BILA ASC
            {
                ordonareCrescatoare(carduri, N, atoi(&bilaCurenta[4]));
            }
            else if (bilaCurenta[0] == 'D') // BILA DSC
            {
                ordonareDescrescatoare(carduri, N, atoi(&bilaCurenta[4]));
            }
        }
        if (strlen(bilaCurenta) <= 4)     // daca lungimea sirului citit este mai mic sau egal decat 4
        {                                 // atunci s-a citit o bila normala
            int i, j;                     // cautam in toata matricea pentru ca atunci cand se extrage o bila swap sa se schimbe si litera coloanei
            strcpy(AUX, bilaCurenta + 2); // eliminam primele doua elemente pentru a ajunge la numarul bilei
            strcpy(bilaCurenta, AUX);
            int numar = atoi(bilaCurenta);
            for (contorCarduri = 0; contorCarduri < N; contorCarduri++) // pentru fiecare jucator in parte
                for (i = 0; i < 5; i++)                                 // cautam bila respectiva pe coloana indicata
                    for (j = 0; j < 5; j++)
                        if (carduri[contorCarduri][i][j] == numar)
                        {
                            carduri[contorCarduri][i][j] = -numar;
                        }
        }
        verificare(carduri, punctaj, N);
        max = valoareMaxima(punctaj, N);
        if (max > 0)
        {
            for (i = 0; i < N; i++)
            {
                if (punctaj[i] == max)
                {
                    ok = 1;
                    printf("%d\n", i);
                    afisare(carduri[i]);
                    printf("%d\n", punctaj[i]);
                    break;
                }
            }
        }
        if (ok == 1)
            break;
    }

    for (i = 0; i < N; i++) // daca tot vectorul de puncte este null => ca nu exista niciun castigator
        if (punctaj[i] != 0)
            break;
        else if (i == N - 1 && punctaj[i] == 0)
            printf("NO WINNER\n");
}

int main()
{
    int carduri[200][5][5], punctaj[200] = {0}, N, M;
    scanf("%d", &N);                    // citire numar carduri
    citire(carduri, N);                 // citeriea tuturor cardurilor
    scanf("%d", &M);                    // citire numar bile
    citireBile(carduri, punctaj, M, N); // citim bilele si efectuam operatiile aferente (calculam si punctajul)
    return 0;
}