#include <iostream>
#include "grafo.h"

using namespace std;

// Construtor
Grafo::Grafo(int v) {
    vertices = v;
    adj.resize(v);
}

// Inserir novo vértice
void Grafo::inserirVertice() {

    adj.push_back(vector<pair<int, int> >());
    vertices++;

    cout << "Cidade inserida com sucesso!\n";
}

// Inserir aresta
void Grafo::inserirAresta(int u, int v, int peso) {

    adj[u].push_back(make_pair(v, peso));
    adj[v].push_back(make_pair(u, peso));

    cout << "Caminho inserido entre "
         << u << " e "
         << v << endl;
}

// Remover aresta
void Grafo::removerAresta(int u, int v) {

    // Remove u -> v
    for (vector<pair<int, int> >::iterator it = adj[u].begin();
         it != adj[u].end();
         ++it) {

        if (it->first == v) {
            adj[u].erase(it);
            break;
        }
    }

    // Remove v -> u
    for (vector<pair<int, int> >::iterator it = adj[v].begin();
         it != adj[v].end();
         ++it) {

        if (it->first == u) {
            adj[v].erase(it);
            break;
        }
    }

    cout << "Caminho removido!\n";
}

// Remover vértice
void Grafo::removerVertice(int v) {

    // Remove referências ao vértice
    for (int i = 0; i < vertices; i++) {

        for (vector<pair<int, int> >::iterator it = adj[i].begin();
             it != adj[i].end();) {

            if (it->first == v) {
                it = adj[i].erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // Remove o vértice
    adj.erase(adj.begin() + v);

    vertices--;

    cout << "Cidade removida!\n";
}

// Mostrar lista de adjacência
void Grafo::mostrar() {

    cout << "\n===== CENTROS DE DISTRIBUIÇÕES =====\n";

    for (int i = 0; i < vertices; i++) {

        cout << "Cidade " << i << ": ";

        for (vector<pair<int, int> >::iterator it = adj[i].begin();
             it != adj[i].end();
             ++it) {

            cout << "("
                 << it->first
                 << ", peso "
                 << it->second
                 << ") ";
        }

        cout << endl;
    }

    cout << endl;
}
