//
// Created by Kamil Delekta on 06.03.2020.
//
//Napisz program, który wczytuje liczbę całkowitą N a następnie oblicza i drukuje
//na ekran wartość N!. Uwaga: silnia bardzo szybko powoduje przepełnienie
//całkowitoliczbowe. Sprawdź dla jakich wartości N program wyprowadza
//prawidłowy wynik. Przetestuj działanie programu dla różnych typów danych
//(dla ułatwienia można zastosować definicję typedef).
//For int %d
//For long int %ld
//For long long int %lld
//For unsigned long long int %llu

#include <stdio.h>

typedef unsigned long long typ;

typ silnia_r(unsigned long n){
    if(n == 0) return 1;
    return n * silnia_r(n - 1);
}

typ silnia_i(unsigned long n){
    typ res = 1;
    while(n > 0){
        res  = res * n;
        n--;
    }
    return res;
}
int main() {
    unsigned long n;
    printf("Podaj liczbe z ktorej policzyc silnie:");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("i = %d \n", i);
        printf("Wynik (recursive) : %llu \n", silnia_r(i));
        printf("Wynik (iterative) : %llu \n\n", silnia_i(i));
    }

    return 0;
}
