// HAS CYCLE?
// WEJSCIE:
// Pierwsza linia zawiera dwie liczby całkowite n, k będące odpowiednio liczbą wierzchołków i liczbą krawędzi grafu.
// W kolejnych k wierszach znajdują się opisy krawędzi złożone z dwóch liczb 0¬ a, b ¬ n−1 oznaczających,
// że graf zawiera krawędź z a do b.
// WYJSCIE:
//Pierwsza linia standardowego wyjścia zawiera dokładnie jedno słowo: OK jeśli odpowiednia kolejność istnieje
// (graf jest acykliczny) lub CYCLE w przeciwnym przypadku. Dla grafu acyklicznego wyjście zawiera dodatkową
// linię złożoną z n liczbcałkowitych-przykładową kolejność instalacji pakietów.


#include <stdio.h>
#include <stdlib.h>

typedef struct vertex{
    int visited;
}vertex;


typedef struct graph{
    vertex *arr;
}graph;

typedef struct Stack {
    int top;
    int size;
    int* array;
}Stack;


Stack* create_stack(int size)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->size = size;
    stack->array = (int*)malloc(stack->size * sizeof(int));
    return stack;
}

int pop(struct Stack* stack)
{
    int x=stack->array[stack->top];
    stack->top--;
    return x;
}

void push(struct Stack* stack, int v)
{
    stack->top++;
    stack->array[stack->top] = v;
}

int is_empty(struct Stack* stack)
{
    if(stack->top==-1) return 1;
    else return 0;
}

int dfs(graph graph, int **arr, int v, int n, int started)
{
    // printf("%d %d\n", v, started);
    if(v==started && graph.arr[started].visited == 1) return 0;
    graph.arr[v].visited = 1;

    for(int i=0;i<n;i++)
    {
        if(arr[v][i] == 1)
        {
            if(dfs(graph,arr,i,n,started) == 0)
                return 0;
        }
    }
    return 1;

}

void topological_sort(graph graph, int **arr, struct Stack* stack, int v, int n)
{
    for(int i=0;i<n;i++)
    {
        if(arr[v][i] == 1 && graph.arr[i].visited==0)
        {
            topological_sort(graph,arr,stack,i,n);
        }
    }
    push(stack,v);
    graph.arr[v].visited = 1;
}

void has_cycle(graph graph, int ** array, int n){
    for(int i=0;i<n;i++)
    {
        if(dfs(graph,array,i,n,i) == 0)
        {
            printf("CYCLE");
            return;
        }
        // printf("%s", "end");
        for(int j=0;j<n;j++)
        {
            graph.arr[j].visited=0;
        }
    }

    printf("OK\n");
    struct Stack* stack = create_stack(n);
    for(int i=0;i<n;i++)
    {
        if(graph.arr[i].visited==0)
            topological_sort(graph,array,stack,i,n);
    }

    while(is_empty(stack) == 0)
        printf("%d ",pop(stack));

    free(stack->array);
    free(stack);
}


int main()
{
    int n,k;

    graph graph;
    scanf("%d %d",&n,&k);

    int **array = malloc(n*sizeof(int*));
    graph.arr = malloc(n*sizeof(vertex));

    for(int i=0; i<n; i++)
    {
        array[i]=malloc(n*sizeof(int));
    }

    for(int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            array[i][j]=0;
    }

    for(int i=0;i<k;i++)
    {
        int v1, v2;
        scanf("%d %d",&v1,&v2);
        array[v1][v2]=1;
    }

    for(int i=0;i<n;i++)
    {
        vertex v;
        v.visited=0;
        graph.arr[i]=v;
    }

    has_cycle(graph, array, n);

    free(graph.arr);
    free(array);
}
