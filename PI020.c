// HAS CYCLE?
// WEJSCIE:
// Pierwsza linia zawiera dwie liczby całkowite n, k będące odpowiednio liczbą wierzchołków i liczbą krawędzi grafu.
// W kolejnych k wierszach znajdują się opisy krawędzi złożone z dwóch liczb 0¬ a, b ¬ n−1 oznaczających,
// że graf zawiera krawędź z a do b.
// WYJSCIE:
//Pierwsza linia standardowego wyjścia zawiera dokładnie jedno słowo: OK jeśli odpowiednia kolejność istnieje
// (graf jest acykliczny) lub CYCLE w przeciwnym przypadku. Dla grafu acyklicznego wyjście zawiera dodatkową
// linię złożoną z n liczbcałkowitych-przykładową kolejność instalacji pakietów.


# include <stdio.h>
# include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
}node;

void print(node* head){
    node* curr = head;

    while (curr != NULL){
        printf("%d ", curr->val );
        curr = curr->next;
    }
    printf("\n");
}

node* push_back(node *head, node* new){
    node* curr = head;
    if(curr == NULL){
        head = new;
    }
    else{
        while(curr -> next != NULL){
            curr = curr -> next;
        }
        curr -> next = new;
    }

    return head;
}

int dfs(node **graph, int *visited, int v){
    visited[v] = 1;
    node *neighbour = graph[v];
    while(neighbour != NULL){
        if(visited[neighbour -> val] == -1){
            if(dfs(graph, visited, neighbour -> val) == 1){
                return 1;
            }
        }
        else if(visited[neighbour -> val] == 1){
            return 1;
        }
        neighbour = neighbour -> next;
    }
    return 0;
}

void dfs_print(node **graph, int *visited, int v){
    visited[v] = 1;
    printf("%d ", v);
    node *neighbour = graph[v];
    if(neighbour != NULL){
        if(visited[neighbour -> val] == -1){
            dfs_print(graph, visited, neighbour -> val);
        }
    }
}

void has_cycle(node **graph, int *visited, int n){
    for(int v = 0;v < n; v++){
        if(visited[v] == -1){
            if(dfs(graph, visited, v) == 1){
                printf("CYCLE");
                return;
            }
        }
    }
    printf("OK\n");
    for(int i = 0; i < n; i++) visited[i] = -1;

    for(int v = 0;v < n; v++){
        if(visited[v] == -1  && graph[v] != NULL){
            dfs_print(graph, visited, v);
            return;
        }
    }

}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);

    node **graph = malloc(n * sizeof(node*));

    for(int i = 0;i < n; i++) graph[i] = NULL;

    for(int i = 0; i < k; i++){

        int a;
        node *b = (node*)malloc((sizeof(node)));


        scanf(" %d %d", &a, &(b -> val));
        b -> next = NULL;

        graph[a] = push_back(graph[a], b);
    }

    int *visited = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) visited[i] = -1;

    has_cycle(graph, visited, n);

    free(visited);
    for(int i = 0; i < n; i++){
        free(graph[i]);
    }
    free(graph);
}
