// Dany jest wykaz wszystkich linii metra wraz z czasem przejazdu między kolejnymi przystankami dla każdej z nich.
// Napisz program, który dla zadanego układu linii obliczy minimalny czas podróży między dowolnymi dwoma stacjami.

#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX / 2;

typedef struct Segment {
    int town, travel_time;
} Segment;

typedef struct Line {
    Segment* segments;
    int number, length, start_town;
} Line;

Line* newLine(int number, int length, int start_town) {
    Line* l = new Line;
    l->number = number;
    l->length = length;
    l->start_town = start_town;
    l->segments = new Segment[length];
    return l;
}

typedef struct Node {
    int town, id;
    vector< pair<Node*, int> > neighbours;
} Node;

int** calculateTimesMatrix(Line** lines, int lines_no, int towns) {
    // put your code here
    int** results = new int*[towns];

    for(int v = 0; v < towns; v++) {
        results[v] = new int[towns];
        for (int u = 0; u < towns; u++)
            if (v == u) {
                results[v][u] = 0;
            }
            else {
                results[v][u] = INF;
            }
    }

    for(int i = 0; i < lines_no; i++)
    {
        Line* line = lines[i];
        int start = line->start_town;

        for(int j = 0; j < line->length ; j++)
        {
            Segment end = line->segments[j];

            results[start][end.town] = min(end.travel_time, results[start][end.town]);
            results[end.town][start] = min(end.travel_time, results[end.town][start]);



            start = end.town;
        }
    }

    for(int t = 0; t < towns; t++)

        for(int i = 0; i < towns; i++)

            for(int j = 0; j < towns; j++)

                if(results[i][j] > results[i][t] + results[t][j]) {
                    results[i][j] = results[i][t] + results[t][j];
                }

    return results;
}

int main() {
    int towns, lines_no, queries;

    cin >> towns >> lines_no >> queries;

    Line** lines = new Line*[lines_no];

    for (int i = 0; i < lines_no; i++) {

        int len, start;

        cin >> len >> start;

        lines[i] = newLine(i, len-1, start);

        for (int j = 0; j < len-1; j++) {

            int next, time;

            cin >> time >> next;

            lines[i]->segments[j].town = next;
            lines[i]->segments[j].travel_time = time;
        }
    }

    int** times = calculateTimesMatrix(lines, lines_no, towns);

    for (int i=0; i<queries; i++) {
        int u, v;
        cin >> u >> v;
        cout << times[u][v] << endl;
    }

    for (int i=0; i<towns; i++) delete[] times[i];
    delete[] times;
    for (int i=0; i<lines_no; i++) {
        delete[] lines[i]->segments;
        delete lines[i];
    }
    delete[] lines;
}

