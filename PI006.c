//
// Created by Kamil Delekta on 12.03.2020.
//
// Dzielenie tablic
//Dana jest tablica liczb całkowitych, T1, o długości n. Napisz program, który na wejściu
//otrzymuje wartości T1 i dzieli ją na dwie tablice, T2 i T3, tak, by w jednej z nich znalazły
//się elementy parzyste a w drugiej nieparzyste. Następnie posortuj obie tablice.
//Wejscie:
//W pierwszym wierszu standardowego wejścia znajduje się liczba naturalna, n (z zakresu
//[1,1000]) reprezentująca rozmiar tablicy T1. Kolejne n wierszy zawiera wartości tablicy T1.
//Wyjscie:
//Pierwszy wiersz standardowego wyjścia programu powinien zawierać dwie liczby całkowite
//e i o (odpowiednio długości tablicy T2 elementów parzystych i tablicy T3 elementów
//nieparzystych) a następnie e wierszy z wartościami T2 posortowanymi rosnąco i o wierszy
//z wartościami T3 również posortowanymi rosnąco.
#include <stdio.h>
#include <stdlib.h>
void sort(int* t, int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (t[j] > t[j + 1]) {
                int temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
}

int split(int* t1, int* t2, int* t3, int n) {
    int e = 0;
    int o = 0;
    for(int i = 0; i < n; i++){
        if(t1[i] % 2 == 0){
            t2[e] = t1[i];
            e++;
        }
        else{
            t3[o] = t1[i];
            o++;
        }
    }
    return e;
}

void print(int* t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", t[i]);
    }
}

int main() {

    int n;
    scanf("%d", &n);

    int *t1 = (int*)malloc(n* sizeof(int));
    int *t2 = (int*)malloc(n* sizeof(int));
    int *t3 = (int*)malloc(n* sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &t1[i]);
    }

    int e = split(t1, t2, t3, n);
    int o = n - e;

    sort(t2, e);
    sort(t3, o);

    printf("%d %d\n", e, o);
    print(t2, e);
    print(t3, o);

    free(t1);
    free(t2);
    free(t3);
}
