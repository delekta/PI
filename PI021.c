// haszowanie łańcuchowe

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct node{
    char* number;
    char* name;
    struct node *next;
}node;

int hash( int n, char* key){
    int len = strlen(key);
    int idx = 0;
    for(int i = 0; i < len; i++){
        char c = key[i];
        idx += c;
        idx %= 30;
    }
    idx %= n;
    return idx;
}

void add(node **phoneBook, int n, char* name, char* number){
    int idx = hash(n, name);
    node* curr = phoneBook[idx];
    if(curr == NULL){
        node *new = malloc(sizeof(node));
        new -> number = number;
        new -> name = name;
        new -> next = NULL;
        phoneBook[idx] = new;
    }
    else{
        while(curr -> next != NULL){
            curr = curr->next;
        }
        node *new = malloc(sizeof(node));
        new -> number = number;
        new -> name = name;
        new -> next = NULL;
        curr -> next = new;
    }
}

void delete(node **phoneBook, int n, char* name){
    int idx = hash(n, name);
    node* curr = phoneBook[idx];
    node* prev = phoneBook[idx];
    if(prev == NULL){
        return;
    }


    while(curr != NULL && curr -> name != name){
        prev = curr;
        curr = curr -> next;
    }
    if(curr == NULL){
        return;
    }
    if(prev == curr){
        phoneBook[idx] = curr -> next;
    }
    else{
        // dla jednego też będzie działac
        prev -> next = curr -> next;
        free(curr);
    }


}

void get(node **phoneBook, int n, char* name){
    int idx = hash(n, name);
    node* curr = phoneBook[idx];
    if(curr == NULL){
        printf("\n");
        return;
    }
    while(curr -> next != NULL && curr -> name != name){
        curr = curr -> next;
    }
    if(curr -> name == name){
        printf("%s\n", curr -> number);
        return;
    }
    printf("\n");
}

void print_all_phone_book(node **phoneBook, int n){
    for(int i = 0; i < n; i++){
        node *curr = phoneBook[i];
        printf("idx: %d", i);
        while(curr != NULL){
            printf("Name: %s, Nr: %s", curr -> name, curr -> number);
            curr = curr -> next;
        }
        printf("\n");
    }
}


int main() {
    int Z;
    scanf("%d", &Z);

    while(Z--){

        int n;
        scanf("%d", &n);
        node **phoneBook = malloc(n * sizeof(node*));

        for(int i = 0; i < n; i++){
            phoneBook[i] = NULL;
        }

        int k;
        scanf("%d", &k);
        for(int i = 0; i < k; i++){
            char typ;
            char* name = malloc(30 * sizeof(char));
            // wazna spacja przed %c
            scanf(" %c %s", &typ, name);
            if(typ == 'a'){
                char* number = malloc(30 * sizeof(char));
                scanf(" %s", number);
                add(phoneBook, n, name, number);
            }
            else if(typ == 'r'){
                delete(phoneBook, n, name);
            }
            else if(typ == 'g'){
                get(phoneBook, n, name);
            }
            free(name);
            // print_all_phone_book(phoneBook, n);
        }
    }
    return 0;
}
