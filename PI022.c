// adresowania otwarte z szukaniem kwadratowym
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TAKEN, DELETED, FREE,
} Stage;

typedef struct node {
    Stage stage;
    char name[31];
    char number[31];
} node;

int hash(char *str, int i, int n, int size) {
    int c;

    unsigned long idx = 5381;

    while((c = *str++)) idx = idx * 33 + c;

    return (idx % n + i * (1 + i) / 2) % size;
}

void Add(node *phoneBook, char *key, char *value, int n, int size)
{
    for(int i = 0; i < size; i++)
    {
        int idx = hash(key, i, n, size);
        if(phoneBook[idx].stage != TAKEN)
        {
            phoneBook[idx].stage = TAKEN;

            strcpy(phoneBook[idx].name, key);
            strcpy(phoneBook[idx].number, value);
            return;
        }
    }
}

node *Get(node *phoneBook, char *key, int n, int size)
{
    for(int i = 0; i < size; i++)
    {
        int idx = hash(key, i, n, size);
        if(phoneBook[idx].stage != FREE)
        {
            if(strcmp(phoneBook[idx].name, key) == 0 && phoneBook[idx].stage == TAKEN) {
                return &phoneBook[idx];
            }
        }
        else
            break;
    }

    return NULL;
}

void Remove(node *phoneBook, char *key, int n, int size) {
    for(int i = 0; i < size; i++) {
        int idx = hash(key, i, n, size);
        if(phoneBook[idx].stage != FREE) {
            if( strcmp(phoneBook[idx].name, key) == 0 && phoneBook[idx].stage == TAKEN){
                phoneBook[idx].stage = DELETED;
                return;
            }
        } else return;
    }
}

int main() {

    int Z;

    scanf("%d", &Z);

    while(Z--)
    {
        int n, k;

        char type[2];
        char key[31];
        char value[31];

        scanf("%d %d", &n, &k);

        int size = 2;
        while(size < n) size *= 2;

        node *phoneBook = malloc(size * sizeof(node));

        for(int i = 0; i < size; i++) phoneBook[i].stage = FREE;

        while(k--)
        {
            scanf(" %c %s", type, key);

            switch(type[0]) {

                case 'r':
                {
                    Remove(phoneBook, key, n, size);
                    break;
                }

                case 'a':
                {
                    scanf("%s", value);
                    Add(phoneBook, key, value, n, size);
                    break;
                }

                case 'g':
                {
                    node *res = Get(phoneBook, key, n, size);

                    if(res != NULL)
                    {
                        printf("%s\n",res -> number);
                    }
                    else
                    {
                        printf("\n");
                    }
                    break;
                }
            }
        }

        free(phoneBook);
    }
}