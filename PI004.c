//
// Created by Kamil Delekta on 06.03.2020.
//
//Znajdź pole powierzchni ograniczone osią Ox i wykresem funkcji sin(x) w przedziale
// [a,b] metodą Monte Carlo. Dane wejściowe: a,b,N (liczba losowanych punktów).
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int main() {
    srand(time(NULL));
    int n = 10000;
    int c = 0;
    double tabX[n];
    double tabY[n];
    for (int i = 0; i < n; i++){
        // prostokat pi * 2
        tabX[i] = ((float)rand() / (float)(RAND_MAX)) * M_PI;
        tabY[i] = ((float)rand() / (float)(RAND_MAX))* 2 - 1;
        if (cos(tabX[i]) > 0){
            if(tabY[i] < cos(tabX[i]) && tabY[i] > 0) c++;
        }
        else{
            if(tabY[i] > cos(tabX[i]) && tabY[i] < 0) c++;
        }
        //printf("X: %g, Y: %g \n", tabX[i], tabY[i]);
    }
    double area = (M_PI * 2)*((float)c / (float)n);
    printf("area = %g", area);
    return 0;
}
