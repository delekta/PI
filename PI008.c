//
// Created by Kamil Delekta on 12.03.2020.
//
// Laczenie tablic
//Dane są dwie tablice liczb całkowitych, T1 i T2, o długościach odpowiednio m i n. Napisz
//program, który na wejściu otrzymuje wartości obu tablic i sortuje je rosnąco. Następnie
//utwórz nową tablicę, T3, o długości co najwyżej m + n, która powstaje przez połączenie
//tablic T1 i T2 w taki sposób, aby:
//1. Zachować rosnące uporządkowanie wartości tablicy
//2. Wartości tablicy T3 były unikalne
//Uwaga: W tym zadaniu używamy dynamicznie alokowanej pamięci.
//Wejscie:
//W pierwszym wierszu standardowego wejścia znajdują się dwie liczby naturalne, 1 < m, n <1000
//reprezentujące odpowiednio rozmiary tablic T1 i T2. Kolejne m+n wierszy zawiera wartości tablic
//T1 oraz T2 (w tej kolejności).
//Wyjscie:
//Kolejne wiersze standardowego wyjścia programu powinny zawierać posortowane i unikalne wartości tablicy T3.
#include <stdio.h>
#include <stdlib.h>
void sort(int* t, int n) {
    for(int i = n - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(t[j] > t[j + 1]){
                int temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
}
int merge(int *t1, int *t2, int* t3, int m, int n) {
    int i = 0;
    int j = 0;
    int k = 0;
    int last;
    while(i < m && j < n){
        if (t1[i] < t2[j]){
            t3[k] = t1[i];
            last = t1[i];
        }
        else if(t2[j] < t1[i]){
            t3[k] = t2[j];
            last = t2[j];
        }
        else{
            t3[k] = t1[i];
            last = t1[i];
        }
        k++;
        while(i < m && t1[i] == last) i++;
        while(j < n && t2[j] == last) j++;
    }
    while(i < m){
        t3[k] = t1[i];
        last = t1[i];
        k++;
        while(i < m && t1[i] == last) i++;
    }
    while(j < n){
        t3[k] = t2[j];
        last = t2[j];
        k++;
        while(j < n && t2[j] == last) j++;
    }
    return k;
}

void print(int* t, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d\n",t[i]);
    }
}

int main() {

    int m, n;
    scanf("%d %d", &m, &n);

    int *t1 = (int*)malloc(m* sizeof(int));
    int *t2 = (int*)malloc(n* sizeof(int));
    int *t3 = (int*)malloc((m + n)* (sizeof(int)));

    for (int i = 0; i < m; i++) {
        scanf("%d", &t1[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &t2[i]);
    }

    sort(t1, m);
    sort(t2, n);

    int l = merge(t1, t2, t3, m, n);

    print(t3, l);

    free (t1);
    free (t2);
    free (t3);
}
