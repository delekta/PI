#include <iostream>
#include <climits>
#include <vector>
#include <utility>

using namespace std;

const int INF = INT_MAX/2;

typedef struct Node {
    vector <pair<Node *, int>> neighbours;
    int val, dist;
} Node;

Node *newNode(int val) {
    Node *n = new Node;
    n->val = val;
    n->dist = INF;
    return n;
}

void addEdge(Node *u, Node *v, int w) {
    pair <Node *, int> edge(v, w);
    u->neighbours.push_back(edge);
}

void relax(Node *v, Node *u, int weight) {
    if(u->dist > v->dist + weight)
        u->dist = v->dist + weight;
}

bool bellmann_ford(Node **nodes, int n, Node *start) {

    start->dist = 0;

    for(int i = 1;i < n;i++) {
        for(int v = 0;v < n;v++)
            for(auto u: nodes[v]->neighbours){
                relax(nodes[v], u.first, u.second);
            }
    }
    for(int v = 0;v < n;v ++)
        for(auto u: nodes[v]->neighbours)
            if(u.first -> dist > nodes[v] -> dist + u.second)
                return false;
    return true;

}




int main() {
    int N, k, start, end;
    cin >> N >> k;
	cin >> start >> end;
    Node *nodes[N];
    for (int i = 0; i < N; i++) nodes[i] = newNode(i);

    for (int i = 0; i < k; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(nodes[u], nodes[v], w);
    }

    if (!bellmann_ford(nodes, N, nodes[start])) cout << "CYCLE" << endl;
    else if (nodes[end]->dist < INF) cout << nodes[end]->dist << endl;
    else cout << "NO" << endl;

    for (int i = 0; i < N; i++) delete nodes[i];
}