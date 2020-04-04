// Kalkulator ONP
// Wejscie:
// W pierwszym wierszu standardowego wejścia znajdują się dwie liczby naturalne:
// n(1¬n¬1000) - liczba operandów (liczb) w podanym wyrażeniu orazk(1¬k¬8) -maksymalna
// długość każdej liczby w zapisie dziesiętnym. W drugim wierszu znajduje sięwyrażenie
// zapisane w formie ONP, zawierającenliczb całkowitych, w którym wszystkieoperandy i
// operatory oddzielone są białymi znakami. Można założyć, że wyrażenie jestpoprawne.
// Wyjscie:
//Na standardowym wyjściu programu powinna znaleźć się jedna liczba całkowita
// - obli-czona wartość wyrażenia.

#include <stdio.h>
#include <stdlib.h>

int convert (char * num, int length)
{
    int res = 0;
    int idx = 0;
    int multiplier = 1;

    for(int i = 1; i < length && num[i] != '\0'; i++) multiplier *= 10;

    while (multiplier > 0)
    {
        res += (num[idx] - 48) * multiplier;
        multiplier /= 10;
        idx++;
    }

    return res;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *arr = malloc(n * sizeof(int));
    int idx = -1;

    while(n > 0 || idx > 0){
        char *opr = malloc((k + 1) * sizeof(char));
        scanf("%s", opr);
        if(idx > 0 && (opr[0] == '+' || opr[0] == '-' || opr[0] == '*' || opr[0] == '/')) {
            int a = arr[idx];
            idx--;
            int b = arr[idx];
            if(opr[0] == '+'){
                arr[idx] = b + a;
            }else if(opr[0] == '-'){
                arr[idx] = b - a;
            }else if(opr[0] == '*'){
                arr[idx] = b * a;
            }else if(opr[0] == '/'){
                arr[idx] = b / a;
            }
        }
        else {
            n--;
            idx++;
            arr[idx] = convert(opr, k);
        }
    }
    printf("%d", arr[0]);
    free(arr);
}