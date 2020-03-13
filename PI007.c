//
// Created by Kamil Delekta on 12.03.2020.
//
//Napisz program, który na wejściu otrzymuje macierz kwadratową i sprawdza, czy jest
//ona trójkątna dolna. Macierz L jest dolnotrójkątna, jeżeli lij = 0 dla i < j (czyli nad
//główną przekątną znajdują się elementy zerowe).
//Wejscie:
//W pierwszym wierszu standardowego wejścia znajduje się jedna liczba naturalna 1 <  n < 100 reprezentująca
//rozmiar macierzy. Kolejne n wierszy zawiera po n liczb naturalnych z zakresu [0,1000] - wiersze macierzy.
//Wyjscie:
//Na standardowym wyjściu programu powinno znaleźć się jedno słowo - YES, jeśli dana macierz
//jest trójkątna dolna, lub NO w przeciwnym przypadku
#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int L[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &L[i][j]);
        }
    }
    int b = 1;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(L[i][j] != 0){
                b = 0;
            }
        }
    }
    if(b){
        printf("YES");
    }
    else{
        printf("NO");
    }
    return 0;
}