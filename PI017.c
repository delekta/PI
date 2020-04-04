// Kolorowanka
// Napisz program, który na wejściu otrzymuje kwadratową tablicę reprezentującą częściowo
// pokolorowany obrazek (0 oznacza brak koloru) i wypełnia wskazane niepokolorowane
// obszary podanymi kolorami. Program wczytuje współrzędne punktu oraz kod koloru i
// maluje na ten kolor wszystkie pola sąsiednie (o wspólnej krawędzi). Postępujemy tak do
// napotkania granicy planszy lub pola wcześniej pokolorowanego.

// Wykorzystaj kolejkę. W pętli pobierz jeden punkt z kolejki, koloruj go (jeśli jeszcze nie
// ma koloru) i umieść w kolejce wszystkie sąsiednie pola (czyli takie, które mają wspólną
// krawędź z bieżącym).

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pixel{
    int row;
    int column;
}pixel;

typedef struct queue{
    int first, last, size;
    pixel *arr;
}queue;

queue *create_quaue(int size) {
    queue *q = malloc(sizeof(queue));
    q -> first = 0;
    q -> last = 0;
    q -> size = size;
    q -> arr = malloc(size * sizeof(pixel));
    return q;
}

void del_queue(queue *q) {
    free(q -> arr);
    free(q);
}

pixel get(queue *q) {
    if(q -> first + 1 < q -> size){
        q -> first++;
        return q -> arr[q -> first];
    }else {
        q -> first = 0;
        return q -> arr[q -> first];
    }
}

void put(int row, int column, queue *q) {
    if(q -> last + 1 < q -> size) {
        q -> last++;
        q -> arr[q -> last].row = row;
        q -> arr[q -> last].column = column;
    } else {
        q -> last = 0;
        q -> arr[q -> last].row = row;
        q -> arr[q -> last].column = column;
    }
}

bool empty(queue *q){
    return q -> first == q -> last;
}

bool may_i(int **image, pixel p, int n) {
    if (p.row >= n || p.column >= n || p.row < 0 || p.column < 0) return false;
    if (image[p.row][p.column] == 0) return true;
    else return false;
}

void colour(int **image, int n, int row, int column, int color) {
    queue *queue = create_quaue(n * n * n);
    put(row, column, queue);
    while(! empty(queue)){
        pixel q = get(queue);
        if(may_i(image, q, n)){
            put(q.row, q.column + 1, queue);
            put(q.row, q.column - 1, queue);
            put(q.row + 1, q.column, queue);
            put(q.row - 1, q.column, queue);

            image[q.row][q.column] = color;
        }
    }
    del_queue(queue);
}

int main() {


    int n, k;
    scanf("%d %d", &n, &k);
    int **arr = malloc(n * sizeof(int*));
    for (int i = 0 ; i < n; i++) {
        arr[i] = malloc(n * sizeof(int));
    }


    for (int y = 0; y < n; y++){
        for(int x = 0; x < n; x++) {
            scanf("%d" , &arr[y][x]);
        }
    }

    int row, column,color;
    for (int i = 0; i < k; i++) {
        scanf("%d %d %d", &row, &column, &color);

        colour(arr, n, row, column, color);
    }

    for (int y = 0; y < n; y++){
        for(int x = 0; x < n; x++) {
            printf("%d " , arr[y][x]);
        }
        printf("\n");
    }

    for(int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}