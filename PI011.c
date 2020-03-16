// Liczby najierwsze
// Dana jest liczba całkowita dodatnian. Napisz program, który znajduje wszystkie liczby
// pierwsze mniejsze odn, których cyfry tworzą ciąg niemalejący
# include <stdio.h>
int pierwsza(int num){
    if(num % 2 == 0) return 0;
    for(int j = 3; j * j <= num; j+=2){
        if(num % j == 0) return 0;
    }
    return 1;
}
int nierosnace(int num) {
    int d1 = num % 10;
    num /= 10;
    while(num > 0){
        int d2 = num % 10;
        num /= 10;
        if (d1 < d2) return 0;
        d1 = d2;
    }
    return 1;
}
int main() {
    int n;
    scanf("%d", &n);
    if(n > 2) printf("%d\n", 2);
    for(int i = 3; i < n; i+=2) {
        if(pierwsza(i)){
            if(nierosnace(i)) {
                printf("%d\n", i);
            }
        }
    }
    return 0;
}
