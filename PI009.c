// Szyfr Cezara - modyfikacja
//Napisz program, który szyfruje zadany tekst używając zmodyfikowanego szyfru Cezara.
// Zasada działania szyfru jest następująca: każda litera tekstu przesunięta jest o stałą liczbę
// liter “w prawo”. Nazwijmy jąprzesunięciemi oznaczmys. Np. dla wartościs = 3 słowo “ala”
// przekształca się w słowo“dod”. Przesunięcia są obliczane na zasadzie modulo, zatem litera
// z przesunięta o 3 stanie sięliterąc.Nasza  modyfikacja  polega  na  założeniu,  że
// wartość  przesunięcia s jest  równa  długości pierwszego słowa tekstu. Spacje nie są szyfrowane.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 101	//	100 chars + nullbyte
void encrypt(char* message) {
    int i = 0;
    while (message[i] == ' ')i++;
    int s = 0;
    while (message[i] != ' ' && message[i + 1] != '\0') {
        i += 1;
        s += 1;
    }
    char ch;
    for(int i = 0; message[i + 1] != '\0'; i++) {
        ch = message[i];
        if(ch != ' ') {
            if (isupper(ch)) {
                ch = (ch + s - 65) % 26 + 65;
            } else {
                ch = (ch + s - 97) % 26 + 97;
            }
            message[i] = ch;
        }
    }
}

int main() {
    char message[N];
    fgets(message, N, stdin);
    encrypt(message);
    printf("%s\n", message);
}

