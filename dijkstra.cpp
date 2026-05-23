#include "dijkstra.h"
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

void dijkstra(vector<vector<pair<int, int> > >& adj, int vertices, int origem, int destino) {

    vector<int> dist(vertices, INT_MAX);
    vector<int> anterior(vertices, -1);

    priority_queue<pair<int,int>,
                   vector<pair<int,int> >,
                   greater<pair<int,int> > > fila;

    dist[origem] = 0;
    fila.push(make_pair(0, origem));

    while (!fila.empty()) {
        int custoAtual = fila.top().first;
        int u          = fila.top().second;
        fila.pop();

        if (custoAtual > dist[u]) continue;

        for (int i = 0; i < (int)adj[u].size(); i++) {
            int vizinho     = adj[u][i].first;
            int custoAresta = adj[u][i].second;
            int novoCusto   = dist[u] + custoAresta;

            if (novoCusto < dist[vizinho]) {
                dist[vizinho]     = novoCusto;
                anterior[vizinho] = u;
                fila.push(make_pair(novoCusto, vizinho));
            }
        }
    }

    cout << "\n==============================\n";
    cout << "   RESULTADO DO DIJKSTRA\n";
    cout << "==============================\n";

    if (dist[destino] == INT_MAX) {
        cout << "Nao existe caminho entre " << origem << " e " << destino << "!\n";
        cout << "==============================\n";
        return;
    }

    cout << "Custo total: " << dist[destino] << "\n";

    vector<int> caminho;
    for (int v = destino; v != -1; v = anterior[v]) {
        caminho.push_back(v);
    }

    cout << "Caminho: ";
    for (int i = (int)caminho.size() - 1; i >= 0; i--) {
        cout << caminho[i];
        if (i != 0) cout << " --> ";
    }
    cout << "\n";
    cout << "==============================\n";
}
