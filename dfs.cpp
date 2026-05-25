#include <iostream>
#include <vector>
#include <utility>
#include "dfs.h"

using namespace std;

void dfsRecursivo(vector<vector<pair<int, int> > >& adj, int vertice, vector<bool>& visitado) {

    // Marca o vertice atual como visitado e mostra ele
    visitado[vertice] = true;
    cout << vertice << " ";

    // Anda todos os proximos do vertice
    for (vector<pair<int, int> >::iterator it = adj[vertice].begin();
         it != adj[vertice].end();
         ++it) {

        int vizinho = it->first;

        // So visita se ainda nao foi
        if (!visitado[vizinho]) {
            dfsRecursivo(adj, vizinho, visitado);
        }
    }
}

void dfs(vector<vector<pair<int, int> > >& adj, int vertices, int origem) {

    if (origem < 0 || origem >= vertices) {
        cout << "Vertice de origem invalido!\n";
        return;
    }

    vector<bool> visitado(vertices, false);

    cout << "\n===== DFS (Busca em Profundidade) =====\n";
    cout << "Origem: " << origem << "\n";
    cout << "Ordem de visita: ";

    dfsRecursivo(adj, origem, visitado);

    cout << "\n=======================================\n";
}


bool verificarConectividade(vector<vector<pair<int, int> > >& adj, int vertices) {

    if (vertices == 0) return true;

    vector<bool> visitado(vertices, false);

    // Faz DFS silenciosa a partir do vertice 0
    dfsRecursivo(adj, 0, visitado);

    // Verifica se todos os vertices foram
    for (int i = 0; i < vertices; i++) {
        if (!visitado[i]) {
            return false;  // Encontrou vertice que não foi
        }
    }

    return true;
}