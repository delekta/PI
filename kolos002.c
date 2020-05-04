// Dana jest kwadratowa tablica liczb całkowitych, T o wymiarach n×n. Proszę napisać program, który wczyta ze
// standardowego wejścia liczbę n oraz tablicę T a następnie obliczy i wydrukuje tablicę W taką, że W[i][j] jest
// sumą wszystkich ośmiu liczb z tablicy T sąsiadującychzelementem T[i][j] (poziomo,pionowoipoprzekątnych).
// Dlaelementów leżących na brzegach tablicy T należy uwzględnić odpowiednio mniejszą liczbę sąsiadów.

# include <stdio.h>
# include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int **T = malloc(n * sizeof(int*));
    int **W = malloc(n * sizeof(int*));
    for(int  i = 0; i < n; i++){
        T[i] = malloc(n * sizeof(int));
        W[i] = malloc(n * sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &T[i][j]);
        }
    }

    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int sum = 0;
            if (i > 0 && j > 0){
                sum += T[i - 1][j - 1];
            }
            if(i > 0){
                sum += T[i - 1][j];
            }
            if(i > 0 && j < n - 1){
                sum += T[i - 1][j + 1];
            }
            if(j > 0){
                sum += T[i][j - 1];
            }
            if(j > 0 && i < n - 1){
                sum += T[i + 1][j - 1];
            }
            if(i < n - 1){
                sum += T[i + 1][j];
            }
            if(i < n - 1 && j < n - 1){
                sum += T[i + 1][j + 1];
            }
            if(j < n - 1){
                sum += T[i][j + 1];
            }
            W[i][j] = sum;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", W[i][j]);
        }
        printf("\n");
    }



    for(int  i = 0; i < n; i++){
        free(T[i]);
        free(W[i]);
    }
    free(T);
    free(W);
    return 0;
}
