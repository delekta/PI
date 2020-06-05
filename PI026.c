// Plagiat
// Zaimplementuj program obliczający odległość edycyjną między dwoma tekstami. Odległość edycyjna to minimalna liczba
// operacji wstawienia, usunięcia lub zamiany znaku w pierwszym tekście, by uzyskać drugi tekst

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX = 200;

int min(int a, int b, int c)
{
    int tmp;
    if(a < b) tmp = a;
    else tmp = b;

    if(tmp < c) return tmp;
    else return c;

}

void distance(char* string1, int len1, char* string2, int len2) {

    int **dp = malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        dp[i] = malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i <= len1; i++)
        dp[i][0] = i;

    for (int j = 0; j <= len2; j++)
        dp[0][j] = j;

    int subCost;
    for (int i = 1; i <= len1; i++){
        for (int j = 1; j <= len2; j++) {
            if (string1[i - 1] == string2[j - 1]) subCost = 0;
            else subCost = 1;
            dp[i][j] = min(dp[i - 1][j] + 1,
                           dp[i][j - 1] + 1,
                           dp[i - 1][j - 1] + subCost);
        }
    }

    printf("%d", dp[len1][len2]);

    for(int i = 0; i <= len1; i++){
        free(dp[i]);
    }
    free(dp);
}


int main() {
    char* string1 = malloc(MAX*sizeof(char));
    char* string2 = malloc(MAX*sizeof(char));

    scanf("%[^\n]", string1);
    scanf("%c\n", string2); // reads \n
    scanf("%[^\n]", string2);
    distance(string1, strlen(string1), string2, strlen(string2));
    free(string1);
    free(string2);
    return 0;
}
