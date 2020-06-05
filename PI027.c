#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char MAX_NAME_SIZE = 30;

typedef struct node {
    struct node *left, *right, *parent;
    int key;
    char* name;
} node;

void add_(node* root, node* element){
    node* curr = root;
    node* prev = NULL;


    while(curr != NULL)
    {
        prev = curr;

        if(element -> key > curr -> key) curr = curr -> right;
        else curr = curr -> left;
    }

    element -> parent = prev;

    if(prev -> key < element -> key) prev -> right = element;
    else prev -> left = element;

}

node* find_(node* root, int number) {
    if(root == NULL) return NULL;
    if(root -> key == number) return root;
    node *tmp = root;

    while( tmp != NULL && tmp -> key != number )
    {
        if(number > tmp -> key)
            tmp = tmp -> right;

        else if(number < tmp -> key)
            tmp = tmp -> left;
    }
    if(tmp == NULL){
        return NULL;
    }
    else if(number == tmp -> key)
        return tmp;
}

node* findMin(node* root){
    if(root == NULL) return NULL;
    if(root->left == NULL) return root;
    return findMin(root->left);
}

node* remove_(node* root, int number) {
    if(root == NULL) return root;

    if(number < root -> key) root -> left = remove_(root -> left, number);
    else if(number > root -> key) root -> right = remove_(root -> right, number);
    else
    {
        if(root -> right == NULL)
        {
            node *tmp = root -> left;
            free(root);
            return tmp;
        }


        else if(root -> left == NULL)
        {
            node *tmp = root -> right;
            free(root);
            return tmp;
        }
        node *tmp = findMin(root->right);
        root -> key = tmp -> key;
        root -> name = tmp -> name;

        root -> right = remove_(root -> right,root -> key);
    }

    return root;
}

node* create_node(int key, char *name) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node -> name = malloc(MAX_NAME_SIZE*sizeof(char));

    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> key = key;
    strcpy(new_node -> name, name);

    return new_node;
}

void remove_tree(node* root){
    if(root == NULL) return;
    remove_tree(root->left);
    remove_tree(root->right);
    free(root);
}

int main() {
    int toAdd, toRemove, toFind;
    scanf("%d", &toAdd);
    scanf("%d", &toRemove);
    scanf("%d", &toFind);

    node *root = NULL;
    char *name = malloc(MAX_NAME_SIZE * sizeof(char));

    int number;
    if (toAdd-- > 0) {
        scanf("%d", &number);
        scanf("%s", name);
        root = create_node(number, name);
    }

    for(int i = 0; i < toAdd; i++) {
        scanf("%d", &number);
        scanf("%s", name);

        add_(root, create_node(number, name));
    }

    for(int j = 0; j < toRemove; j++){
        scanf("%d", &number);
        root = remove_(root, number);
    }

    for(int k = 0; k < toFind; k++) {
        scanf("%d", &number);
        node *x = find_(root, number);
        if (x == NULL){
            printf("%s \n", "NO");
        }
        else{
            printf("%s \n", x -> name);
        }
    }

    free(name);
    remove_tree(root);

}