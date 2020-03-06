//
// Created by Kamil Delekta on 05.03.2020.
//
//Paragon fiskalny zawiera następujące informacje: cenę jednostkową netto a,
//liczbę zakupionych sztuk towaru x oraz wysokość podatku VAT podaną w
//procentach p. Napisz program, który wczytuje powyższe dane z klawiatury, a
//następnie oblicza wartość netto zakupionego towaru, wartość podatku VAT oraz
//wartość towaru brutto. Wyniki obliczeń należy wypisać na ekranie w formie uproszczonego
//"paragonu fiskalnego".

#include <stdio.h>

//brutto = 1.23 netto
//netto = brutto/1,23

int main() {
    float netto;
    float proc;
    float sztuk;


    printf("Podaj cenne netto:");
    scanf("%f", &netto);
    printf("Podaj liczbe sztuk:");
    scanf("%f", &sztuk);
    printf("Podaj wysokosc podatku(w procentach):");
    scanf("%f", &proc);

    float cena_netto = cena_netto = netto * sztuk;
    float podatek = 0.01 * proc * cena_netto;
    float cena_brutto = cena_netto  + cena_netto * 0.01 * proc;

    printf("Wartosc netto zakupionego towaru: %g \n", cena_netto);
    printf("Wartosc podatku VAT: %g \n", podatek);
    printf("Wartosc towaru brutto: %g", cena_brutto);

    return 0;
}
