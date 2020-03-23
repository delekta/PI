// Sortowanie szybkie
// Napisz program, który posortuje liczby w ciąg niemalejący.
// Program powinien stworzyć tablicę z wczytanych danych, a następnie posortować ją algorytmem QuickSort.
// W pierwszym wierszu standardowego wejścia znajduje się jedna dodatnia liczba całkowita
// Z oznaczająca liczbę zestawów danych do wczytania. Po niej następuje Z zestawów danych,
// który każdy składa się z:
// •wiersza z liczba n,
// •n wierszy z liczbami do posortowania
//Na standardowym wyjściu programu powinno znaleźć się Z zestawów
// ponwierszy każdyz kolejnymi wyrazami posortowanych ciągów

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}



int partition(int *arr, int left, int right){
    int pivot = arr[right];
    int i = left;
    for(int j = left; j < right; j++){
        if(arr[j] < pivot){
            swap(&arr[j], &arr[i]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

int randPartition(int *arr, int left, int right){
    int r = rand() % (right - left) + left;
    swap(&arr[r], &arr[right]);
    return partition(arr, left, right);
}

void quicksort(int *arr, int left, int right){
    if(right > left){
        int pi = randPartition(arr, left, right);
        quicksort(arr, left, pi - 1);
        quicksort(arr, pi + 1, right);
    }
}

int main() {
    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    while(Z--){
        int n;
        scanf("%d", &n);
        int *arr = malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            scanf("%d", &arr[j]);
        }

        quicksort(arr, 0, n - 1);

        for(int k = 0; k < n; k++){
            printf("%d\n", arr[k]);
        }
        free(arr);
    }


    return 0;
}
