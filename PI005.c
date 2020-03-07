//
// Created by Kamil Delekta on 07.03.2020.
//
//Dana jest tablica liczb całkowitych o zadanej długości n. Napisz program, który znajduje spójny podciąg
// o największej sumie. Ponieważ elementy tablicy mogą być ujemne, rozwiązaniem nie jest cała tablica.
//Przykład:
//Dla tablicy {1, 2, -5, 4, -3, 2} rozwiązaniem jest 4 (pojedynczy element o indeksie 3). Jeżeli wszystkie
// elementy tablicy są ujemne to rozwiązaniem jest 0 (podciąg o długości 0).
#include <stdio.h>

int main() {
    int tab[6] = {-1, -2, -5, -4, -3, 2};
    int n = sizeof(tab) / sizeof(tab[0]);
    int sum = 0;
    int sum_max = 0;
    int start = 0;
    int end = 0;
    //[start, end)
    for(int p = 0; p < n; p++){
        for(int k = p + 1; k <= n; k++) {
            sum = 0;
            for (int i = p; i < k; i++){
                sum += tab[i];
            }
            if(sum > sum_max){
                sum_max = sum;
                start = p;
                end = k;
            }
        }
    }
    printf("Podzciag o najwiekszej sumie idx: [%d, %d), suma: %d", start, end, sum_max);
    return 0;
}
