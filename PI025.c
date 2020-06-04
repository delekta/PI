// Gra
// Dana jest kwadratowa plansza o boku N oraz dwa pola: początkowe i końcowe. Niektóre z pól planszy są zamalowane.
// Zadaniem gracza jest przejście pionkiem ze startu do mety tak, by nie stawać na zamalowanych kratkach. Pionek może
// się poruszać tylko o jedno pole w prawo, w dół albo na skos (czyli tak, by co najmniej jedna ze współrzędnych została
// powiększona o 1). Zaimplementuj program obliczający, na ile sposobów pionek może przejść z zadanego pola startowego
// do mety zgodnie z zasadami gry (w szczególności jeśli nie ma takiej możliwości, program powinien zwrócić 0).

#include <stdio.h>
#include <stdlib.h>
void count(int **array, int *counter, int x, int y, int x2, int y2, int N){
    if( x < 0 || y < 0 || x == N || y == N || array[y][x] == 0){
        return;
    }
    else if(x == x2 && y == y2){
        (*counter)++;
        return;
    }
    count(array, counter, x + 1, y, x2, y2, N);
    count(array, counter, x , y + 1, x2, y2, N);
    count(array, counter, x + 1, y + 1, x2, y2, N);
}

int main() {
    int N;
    scanf("%d", &N);

    int x1, y1, x2, y2;
    scanf("%d %d", &y1, &x1);
    scanf("%d %d", &y2, &x2);

    int** array = malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        array[i] = malloc(N * sizeof(int));
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%d", &array[i][j]);
        }
    }
    int counter = 0;
    count(array, &counter, x1, y1, x2, y2, N);
    printf("%d", counter);



    for(int i = 0; i < N; i++){
        free(array[i]);
    }
    free(array);

    return 0;
}
