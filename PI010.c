// Równe połowki
// Napisz program, który przyjmuję tablicę liczb naturalnych i zwraca taki indeks, że sumy
// wartości elementów tablicy na lewo i na prawo od wyznaczonego miejsca są równe. Można
// założyć, że rozwiązanie istnieje
# include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int tab[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &tab[i]);
    }
    int i = -1;
    int j  = n;
    int sum1 = 0;
    int sum2 = 0;
    while (j - i != 2) {
        if(sum2 < sum1) {
            j--;
            sum2 += tab[j];
        }
        else {
            i++;
            sum1 += tab[i];
        }
    }
    printf("%d", i + 1);
    return 0;
}
