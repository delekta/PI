// Testowe kolokwium 06.04.2020
// Dana jest tablica liczb całkowitych,T o długości n. Napisz program, który na wejściu
// otrzymuje wartości elementów tej tablicy i wyprowadza na standardowe wyjście krotność
// pojawienia się każdej z wartości.Uwaga:W tym zadaniu używamy dynamicznie alokowanej pamięci.
// Wyjscie:
// <unikalna wartosc> <jej krotnosc>

# include <stdio.h>
# include <stdlib.h>

// if exist return index
int exist(int el, int length, int *val){
    for(int i = 0; i < length; i++){
        if(val[i] == el) return i;
    }
    return -1;
}





int main() {
    int n;
    scanf("%d", &n);

    int *T = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++) {
        scanf("%d", &T[i]);
    }

    int k = 0;
    int *val = malloc(n * sizeof(int));
    int *count = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++) {
        count[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        int idx = exist(T[i], k, val);
        if(idx != -1){
            count[idx]++;
        }
        else{
            val[k] = T[i];
            count[k] = 1;
            k++;
        }
    }

    for(int i = 0; i < k; i++){
        printf("%d %d\n", val[i], count[i]);
    }

    free(T);
    free(val);
    free(count);

    return 0;
}
