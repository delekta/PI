// ARE CONNECTED?
// Dana jest mapa połączeń między miastami.Napisz program ,który wczyta mapę połączeń,
// a następnie stwierdzi, czy między podanymi parami miast istnieją połączenia.
// Wejscie:
// W pierwszym wierszu standardowego wejścia znajdują się trzy liczby: n to liczba miast (wierzchołków grafu),
// k to liczba istniejących połączeń między miastami, a p to liczba połączeń wyszukiwanych przez użytkowników systemu
// Wyjscie:
// Na standardowym wyjściu programu powinno znaleźć się p linii, każda zawierająca jedno słowo - YES,
// jeśli istnieje połączenie między podanymi miastami, NO w przeciwnym przypadku.
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
}node;

void dfs(node **graph, int *connected, int v, int color){
    connected[v] = color;
    node *neighbour = graph[v];
    while(neighbour != NULL){
        if(connected[neighbour -> val] == -1){
            dfs(graph, connected, neighbour -> val, color);
        }
        neighbour = neighbour -> next;
    }
}

void dfs_mark(node **graph, int *connected, int n){
    int color = -1;
    for(int v = 0;v < n; v++){
        if(connected[v] == -1){
            color++;
            dfs(graph, connected, v, color);
        }
    }
}

void print(node* head){
    node* curr = head;

    while (curr != NULL){
        printf("%d ", curr->val );
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    node **graph = malloc(n * sizeof(node*));

    for(int i = 0;i < n; i++) graph[i] = NULL;

    for(int i = 0; i < k; i++){
        node *v1 = (node*)malloc((sizeof(node)));
        node *v2 = (node*)malloc((sizeof(node)));


        scanf(" %d %d", &(v1 -> val), &(v2 -> val));
        v1 -> next = NULL;
        v2 -> next = NULL;

        v1 -> next = graph[v2 -> val];
        graph[v2 -> val] = v1;

        printf("%d :", v2 -> val);
        print(graph[v2 -> val]);

        v2 -> next = graph[v1 -> val];
        graph[v1 -> val] = v2;

        printf("%d :", v1 -> val);
        print(graph[v1 -> val]);
    }

    int **searched = malloc(p * sizeof(int*));
    for(int i = 0; i < p; i++){
        searched[i] = malloc(2 * sizeof(int));
    }
    for(int j = 0; j < p; j++){
        scanf("%d %d", &searched[j][0], &searched[j][1]);
    }


    int *connected = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) connected[i] = -1;

    dfs_mark(graph, connected, n);

    for(int i = 0; i < n; i++){
        printf("%d", connected[i]);
    }
    printf("\n");

    for(int i = 0; i < p; i++){
        int v1 = searched[i][0];
        int v2 = searched[i][1];
        if (connected[v1] == connected[v2]){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }

    free(connected);

    for(int i = 0; i < p; i++){
        free(searched[i]);
    }
    free(searched);

    for(int i = 0; i < n; i++){
        free(graph[i]);
    }
    free(graph);
}