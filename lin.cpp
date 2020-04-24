#include <stdio.h>
#include <list>

using namespace std;

list<int> *linia;

list<int> *graf;

int akt_linia;

bool czy_euler;

int n;


void euler(int u)
{
    while (!graf[u].empty())
    {
        int v = graf[u].front();
        graf[v].remove(u);
        graf[u].pop_front();
        euler(v);
    }

    if (!czy_euler && u == 0) {
        akt_linia++;
    } else {
        linia[akt_linia].push_back(u);
    }
}

void znajdz_linie(){
    czy_euler = true;
    for (int i = 1; i <= n; i++)
    {
        // dodaj sasiada do kazdego miasta o nieparzystym stopniu
        if (graf[i].size() % 2 == 1)
        {
            graf[i].push_back(0);
            graf[0].push_back(i);
            czy_euler = false;
        }
    }

    akt_linia = 0;

    if (czy_euler) {
        euler(1);
    } else {
        euler(0);
    }

    int liczba_linii = 0;
    for (int i = 0; i <= akt_linia; i++)
    {
        if (linia[i].size()>1)
            liczba_linii++;
    }

    printf("%d\n", liczba_linii);

    for (int i = 0; i <= liczba_linii; i++)
    {
        if (linia[i].size() > 1)
        {
            printf("%lu ", linia[i].size());
            for (list<int>::iterator it = linia[i].begin(); it != linia[i].end(); it++)
            {
                printf("%d ", *it);
            }
            printf("\n");
        }
    }
}

void przygotuj_graf(){
    int m, u, v;
    scanf("%d %d", &n, &m);

    graf = new list<int>[n+2];
    linia = new list<int>[n+2];

    for(int i=0; i<m; i++) {
        scanf("%d %d", &u, &v);
        graf[u].push_back(v);
        graf[v].push_back(u);
    }
}

int main() {
    int Z;

    scanf("%d", &Z);

    while (Z > 0) {
        Z--;
        
        przygotuj_graf();

        znajdz_linie();

        delete[] graf;
        delete[] linia;
    }
}