#include "dijkstra.h"
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

void dijkstra(vector<vector<pair<int, int> > >& adj,
              int vertices,
              int origem,
              int destino) {

    // Vetor de distâncias (custos mínimos)
    vector<int> dist(vertices, INT_MAX);

    // Guarda o vértice anterior do caminho
    vector<int> anterior(vertices, -1);

    // Fila de prioridade (menor custo primeiro)
    priority_queue<pair<int,int>,
                   vector<pair<int,int> >,
                   greater<pair<int,int> > > fila;

    // Distância da origem para ela mesma = 0
    dist[origem] = 0;

    // Insere origem na fila
    fila.push(make_pair(0, origem));

    // Enquanto houver vértices na fila
    while (!fila.empty()) {

        // Pega o vértice com menor custo atual
        int custoAtual = fila.top().first;
        int u          = fila.top().second;

        fila.pop();

        // Ignora caminhos piores
        if (custoAtual > dist[u])
            continue;

        // Percorre os vizinhos do vértice atual
        for (int i = 0; i < (int)adj[u].size(); i++) {

            int vizinho     = adj[u][i].first;
            int custoAresta = adj[u][i].second;

            // Calcula novo custo
            int novoCusto = dist[u] + custoAresta;

            // Atualiza se encontrou caminho melhor
            if (novoCusto < dist[vizinho]) {

                dist[vizinho] = novoCusto;

                // Guarda de onde veio
                anterior[vizinho] = u;

                // Adiciona na fila
                fila.push(make_pair(novoCusto, vizinho));
            }
        }
    }

    cout << "\n==============================\n";
    cout << "   RESULTADO DO DIJKSTRA\n";
    cout << "==============================\n";

    // Verifica se existe caminho
    if (dist[destino] == INT_MAX) {

        cout << "Nao existe caminho entre "
             << origem << " e "
             << destino << "!\n";

        cout << "==============================\n";
        return;
    }

    // Mostra o custo total
    cout << "Custo total: "
         << dist[destino] << "\n";

    // Reconstrói o caminho percorrido
    vector<int> caminho;

    for (int v = destino; v != -1; v = anterior[v]) {
        caminho.push_back(v);
    }

    // Exibe o caminho na ordem correta
    cout << "Caminho: ";

    for (int i = (int)caminho.size() - 1; i >= 0; i--) {

        cout << caminho[i];

        if (i != 0)
            cout << " --> ";
    }

    cout << "\n";
    cout << "==============================\n";
}
