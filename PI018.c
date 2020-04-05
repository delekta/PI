// Callcenter
// Napisz program, który symuluje działaniecall centerfirmy usługowej. Na wejściu poja-
// wiają się zgłoszenia klientów oraz informacje o możliwości odebrania kolejnego połączenia.
// Połączenia powinny być odbierane w kolejności zgłoszeń (FIFO).
// Wejscie:
// W pierwszym wierszu standardowego wejścia znajduje się jedna dodatnia liczba całkowita
// n oznaczająca liczbę operacji. Po niej następujenwierszy z operacjami.
// Każda operacja ma format:<typ> <sekundy> [numer]
// Mozliwe typy operacji:
// a [add] dodaje nr do kolejki
// r [remove] usun numer z kolejki i wydrukuj informacje
// Wyjscie:
// Standardowe wyjście programu powinno tyle wierszy ile odebrano połączeń (operacje r).
// Każdy wiersz składa się z numeru telefonu i (po spacji) czasu oczekiwania na połączenie.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct callcenter{
    char *nr;
    int time;
}callcenter;

typedef struct queue{
    int first, last, size;
    callcenter *arr;
}queue;

queue *create_queue(int size) {
    queue *q = malloc(sizeof(queue));
    q -> first = 0;
    q -> last = 0;
    q -> size = size;
    q -> arr = malloc(size * sizeof(callcenter));
    return q;
}

void del_queue(queue *q) {
    free(q -> arr);
    free(q);
}

callcenter get(queue *q) {
    if(q -> first + 1 < q -> size){
        q -> first++;
        return q -> arr[q -> first];
    }else {
        q -> first = 0;
        return q -> arr[q -> first];
    }
}

void put(char* nr, int time, queue *q) {
    if(q -> last + 1 < q -> size) {
        q -> last++;
        q -> arr[q -> last].nr = nr;
        q -> arr[q -> last].time = time;
    } else {
        q -> last = 0;
        q -> arr[q -> last].nr = nr;
        q -> arr[q -> last].time = time;
    }
}

bool empty(queue *q){
    return q -> first == q -> last;
}

int main() {
    int n;
    scanf("%d", &n);
    queue *que = create_queue(n);
    queue *res = create_queue(n);

    char nr[n][16];
    int idx_nr = 0;

    for(int i = 0; i < n; i++) {
        char type;
        int time;
        scanf(" %c %d", &type, &time);
        if(type == 'a'){

            scanf(" %s", &nr[idx_nr]);
            put(nr[idx_nr], time, que);

            idx_nr++;
        }
        else if(type == 'r'){
            callcenter mem = get(que);
            int t = time - mem.time;
            put(mem.nr, t, res);
        }
    }
    while(!empty(res)){
        callcenter ans = get(res);
        printf("%s %d  \n", ans.nr, ans.time);
    }
}