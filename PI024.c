// Skiplist
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct Node {
    int height;
    int val;
    struct Node** next;
} Node;

typedef struct SkipList {
    int max_height;
    Node* start;
} SkipList;

int get_height(int max_height){
    int height = 1;
    double p = 0.5;
    while (height < max_height && (rand() / (RAND_MAX + 1.) > p)) height++;
    return height;
}

Node* newNode(int val, int height) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->height = height;
    n->val = val;
    n->next = (Node**)malloc(height*sizeof(Node*));
    for(int i=0; i < n->height; i++) {
        n -> next[i] = NULL;
    }
    return n;
}

SkipList* createSkipList(int max_height) {
    SkipList* skiplist = (SkipList*)malloc(sizeof(SkipList));
    skiplist -> max_height = max_height;

    // wartownik
    skiplist -> start = newNode(-INT_MAX, max_height);

    // chyba nie potrzebne, bo jest to robione w newNode
    for(int i=0; i<max_height; i++) {
        skiplist -> start -> next[i] = NULL;
    }

    return skiplist;
}

void insert_node(SkipList* skiplist, Node* node) {
    Node* curr = skiplist -> start;
    int curr_height = skiplist -> max_height - 1;
    while (curr_height >= 0) {
        while(curr->next[curr_height] != NULL && curr->next[curr_height]->val < node->val) {
            curr = curr->next[curr_height];
        }
        if(curr_height < node -> height) {
            node->next[curr_height] = curr->next[curr_height];
            curr->next[curr_height] = node;
        }
        curr_height--;
    }
}

Node* find_val(SkipList* skiplist, int val) {
    Node* curr = skiplist -> start;
    int curr_height = skiplist -> max_height - 1;
    while (curr_height >= 0) {
        while(curr -> next[curr_height] != NULL && curr -> next[curr_height] -> val < val) {
            curr = curr -> next[curr_height];
        }
        curr_height--;
    }
    if(curr -> next[0] -> val == val) {
        return *curr -> next;
    }
    else{
        return NULL;
    }
}

void remove_node(SkipList* skiplist, Node* node) {
    Node* curr = skiplist -> start;
    Node* tmp = NULL;
    int curr_height = skiplist->max_height - 1;
    while (curr_height >= 0) {
        while(curr -> next[curr_height] != NULL && curr -> next[curr_height]->val < node->val) {
            curr = curr -> next[curr_height];
        }
        if(curr_height < node->height) {
            curr -> next[curr_height] = curr -> next[curr_height]->next[curr_height];
        }
        curr_height--;
    }

}

int main() {

    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    while(Z--){
        int max_height;
        int num_insertions;
        int num_removes;
        int num_find;

        scanf("%d", &max_height);
        scanf("%d", &num_insertions);
        scanf("%d", &num_removes);
        scanf("%d", &num_find);

        SkipList* skiplist = createSkipList(max_height);

        int val;
        while(num_insertions--){
            scanf("%d", &val);
            int height = get_height(max_height);
            // printf("%d", height);

            Node* new_node = newNode(val, height);
            insert_node(skiplist, new_node);
        }

        while(num_removes--) {
            scanf("%d", &val);
            Node* n = find_val(skiplist, val);
            if(n != NULL) {
                remove_node(skiplist, n);

                free(n->next);
                free(n);

            }
        }

        while(num_find--){
            scanf("%d", &val);
            if (find_val(skiplist, val) == NULL) {
                printf("%s\n", "N");
            }
            else{
                printf("%s\n", "Y");
            }
        }


        // delete skiplist
        Node* n = skiplist -> start;
        while(n!=NULL) {
            Node* tmp = n;
            n = n->next[0];
            free(tmp -> next);
            free(tmp);
        }
        free(skiplist);
    }
}
