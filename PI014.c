// Radix Sort
// Napisz program, który posortuje ciągi znaków reprezentujące liczby w ciąg niemalejący.
// Program powinien stworzyć tablicę z wczytanych danych, a następnie posortować ją po-zycyjnie.
// W pierwszym wierszu standardowego wejścia znajduje się jedna dodatnia liczba całkowita
// Z oznaczająca liczbę zestawów danych do wczytania.
// Po niej następujeZzestawów danych. Każdy z zestawów składa się z:
// •wiersza z liczbami n  ik,
// •n wierszy z liczbami do posortowania, przy czym każda z tych liczb
// jest być liczbąnaturalną k-cyfrową.
// Na standardowym wyjściu programu powinno znaleźć się Z zestawów ponwierszy każdy
// z kolejnymi wyrazami posortowanych ciągów
#include<stdio.h>
#include<stdlib.h>

int digit(char* number, int position) {
    return (int)(number[position] - '0');
}

void sortByPosition(char **tab, int n, int pos) {
    int k = 10;
    static int counters[10];
    // Basically, “array” is a “pointer to the first element of
    // array” but “&array” is a “pointer to whole array of 5 int”
    char** result = malloc(n*sizeof(char*));

    for(int i = 0; i < k; i++) {
        counters[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        counters[digit(tab[i], pos)]++;
    }
    for(int i = 1; i < k; i++) {
        counters[i] += counters[i - 1];
    }
    for(int i = n - 1; i >= 0; i--) {
        counters[digit(tab[i], pos)]--;
        result[counters[digit(tab[i], pos)]] = tab[i];
    }
    for(int i = 0; i < n; i++) {
        tab[i] = result[i];
    }



}

void radixSort(char** tab, int n, int length) {
    for(int i = length - 1; i >= 0; i--) {
        sortByPosition(tab, n, i);
    }
}

int main() {
    int Z;
    scanf("%d", &Z);

    while (Z--) {
        int n, k;
        scanf("%d", &n);
        scanf("%d", &k);
        char **arr = malloc(n*sizeof(char*));
        for(int j = 0; j < n; j++){
            arr[j] = malloc((k + 1) * sizeof(char));
        }
        for(int i=0; i<n; i++) {
            scanf("%s", arr[i]);
        }

        radixSort(arr, n, k);
        for(int i=0; i<n; i++) {
            printf("%s\n", arr[i]);
            free(arr[i]);
        }
        free(arr);
    }
}
