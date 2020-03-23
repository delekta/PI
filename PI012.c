// Heap Sort
// Napisz program, który posortuje liczby w ciąg niemalejący.
// Program powinien stworzyć tablicę z wczytanych danych, a następnie posortować ją al-gorytmem HeapSort
// W pierwszym wierszu standardowego wejścia znajduje się jedna dodatnia liczba całkowita Z
// oznaczająca liczbę zestawów danych do wczytania. Po niej następuje Z zestawów danych który każdy składa się z:
// • wiersza z liczbą n
// • n wierszy z liczbami do posortowani
// Na standardowym wyjściu programu powinno znaleźć się Z zestawów ponwierszy każdy
// z kolejnymi wyrazami posortowanych ciągów

#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int *a, int n, int root){
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int max = root;
    if(left < n && a[left] > a[max]){
        max = left;
    }
    if(right < n && a[right] > a[max]){
        max = right;
    }
    if(max != root){
        swap(&a[root], &a[max]);
        heapify(a, n, max);
    }
}

void buildHeap(int *a, int n){
    for(int i = (n / 2) - 1; i >= 0; i--){
        heapify(a, n, i);
    }
}

void heapSort(int *a, int n) {
    buildHeap(a, n);
    for(int j = n - 1; j >= 0; j--){
        swap(&a[0], &a[j]);
        heapify(a, j, 0);
    }
}

int main() {
    int Z;
    scanf("%d", &Z);

    while (Z--) {
        int n;
        scanf("%d", &n);
        int *a = malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        heapSort(a, n);
        for(int i = 0; i < n; i++) {
            printf("%d\n", a[i]);
        }
        free(a);
    }
}

