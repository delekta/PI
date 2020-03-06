//
// Created by Kamil Delekta on 06.03.2020.
//
//Program losuje liczbę 0≤X≤100. Napisz funkcję, która zgaduje wartość X.
//W pętli losujemy n∈[0,100]. Jeżeli X=n zgadliśmy X, jeżeli nie na podstawie4
//wartości X i n ograniczamy przedział, z którego losujemy kolejne n.
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int zgadnij(int a, int b){
    // % (b - a + 1) to make [a, b] not [a, b)
    return (rand() % (b - a + 1)) + a;
}
int main() {
    srand(time(NULL));
    int x = rand() % 101;
    int n;
    int a = 0;
    int b = 100;
    printf("%d \n", x);
    // or we can use stdbool.h
    while (1 > 0){
        printf("Nasz przedzial to [ %d, %d] \n", a, b);
        n = zgadnij(a, b);
        if (n == x){
            printf("Udało sie x == %d \n", n);
            break;
        }
        else if (x < n){
            b = n - 1;
        }
        else{
            a = n + 1;
        }
    }
    return 0;
}
