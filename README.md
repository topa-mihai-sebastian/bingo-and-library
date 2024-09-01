# bingo-and-library

# ----BINGO----

După ce se citește numărul de carduri, cardurile și numărul de bile, se apelează funcția `citesteBile()`. Această funcție citește bile până când se strigă BINGO (dacă există un jucător câștigător, funcția nu va mai citi bile).

Am folosit lungimea numelui bilei pentru a determina ce bilă este (de exemplu, dacă o bilă are lungimea 8, este vorba despre o bilă SWAP).

Unele bile au lungimi egale, deci trebuie să le diferențiez după primul caracter.

**Note importante:**
- Pentru a colora pătrățelul, am folosit înmulțirea numărului respectiv cu `-1`.
- Astfel, nu creez un vector de matrice separat de tip `char`.
- Dacă se citește `B-10` iar pe card se află numărul `10`, atunci numărul de pe card va deveni `-10` și, la operațiile de ordonare, mă voi folosi de modulul fiecărui număr.

De fiecare dată când se citește o bilă, se verifică dacă există un câștigător.
Pentru fiecare linie, coloană sau diagonală colorată (cu elemente negative), vectorul punctaj crește cu 10.
Folosesc un fel de vector de frecvență.

Dacă există mai mulți jucători cu același punctaj, atunci câștigătorul va fi cel cu indice mai mic.

---

# ----BIBLIOTECA-----

Se citește numărul de cărți, apoi alocăm dinamic vectorul de cărți.
Golim buffer-ul deoarece în acesta se află `"\n"`.
Cităm toate cărțile folosind funcția `citireCarti()`.
Cităm numărul de comenzi, iar apoi golim buffer-ul.

Cităm fiecare comandă cu `fgets` și apoi punem `\n` la final.

Verificăm ce comandă s-a citit și efectuam operațiile corespunzătoare:

## `search`
- Verificăm dacă elementul este număr sau șir de caractere.
  - Dacă este șir de caractere, căutăm toate cărțile care au titlul sau autorul egal cu acea valoare.
  - Dacă este număr, căutăm toate cărțile care au anul egal cu acea valoare.

## `replace`
- Parcurgem toate cărțile.
  - Pentru fiecare carte se efectuează:
    - Declarăm niște șiruri de caractere temporale pentru a nu pierde șirul inițial.
    - Dacă se găsește cuvântul vechi (`strstr`), concatenăm într-un auxiliar cuvântul nou și mărim poziția de pe care căutăm cu exact `strlen(cuvantVechi)`.
    - Altfel, doar concatenăm următorul caracter și mărim poziția de pe care căutăm cu 1.

## `add_book`
- Citim o carte în mod normal.
- În `main`, trebuie să realocăm vectorul de cărți (trebuie mărită dimensiunea cu 1).

Afisăm numărul de cărți din bibliotecă.
Afisăm fiecare carte.

La final, eliberăm memoria alocată fiecărei descrieri, apoi eliberăm memoria alocată vectorului de cărți.
