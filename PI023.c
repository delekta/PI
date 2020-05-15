// tablica z mieszaniem podwojnym
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef enum {
    TAKEN, DELETED, FREE
} Stage;


typedef struct node {
    Stage stage;
    char name[31];
    char number[31];
} node;

int hashFun1(char *str, int n) {

    int c;

    unsigned long hash1 = 5381;

    while((c = *str++)) hash1 = ((hash1 << 5) + hash1) + c;

    return hash1 % n;
}

int hashFun2(char *str, int n) {

    int c;

    unsigned long hash2 = 0;

    while((c = *str++)) hash2 = c + (hash2 << 6) + (hash2 << 16) - hash2;

    if (hash2 % 2 == 0) {
        hash2++;
    }

    return hash2 % n;
}

void Remove(node *phoneBook, char *key, int n, int size) {
    int hash1 = hashFun1(key, n);
    int hash2 = hashFun2(key, n);

    for(int i = 0; i < size; i++)
    {
        int idx = (hash1 + i * hash2) % size;
        if(phoneBook[idx].stage != FREE)
        {
            if(strcmp(phoneBook[idx].name, key) == 0 && phoneBook[idx].stage == TAKEN)
            {
                phoneBook[idx].stage = DELETED;
                return;
            }
        } else return;
    }
}

void Add(node *phoneBook, char *key, char *value, int n, int size)
{
    int hash1 = hashFun1(key, n);
    int hash2 = hashFun2(key, n);

    for(int i = 0; i < size; i++)
    {
        int idx = (hash1 + i * hash2) % size;
        if(phoneBook[idx].stage != TAKEN)
        {
            phoneBook[idx].stage = TAKEN;

            strcpy(phoneBook[idx].name, key);
            strcpy(phoneBook[idx].number, value);

            return;
        }
    }
}

node *Get(node *phoneBook, char *key, int n, int size) {
    int hash1 = hashFun1(key, n);
    int hash2 = hashFun2(key, n);

    for(int i = 0; i < size; i++)
    {
        int idx = (hash1 + i * hash2) % size;
        if(phoneBook[idx].stage != FREE)
        {
            if(strcmp(phoneBook[idx].name, key) == 0 && phoneBook[idx].stage == TAKEN) {
                return &phoneBook[idx];
            }
        } else break;
    }

    return NULL;
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
            switch(type[0])
            {

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