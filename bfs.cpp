#include "bfs.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void bfs(vector<vector<pair<int,int>>>& adj, int vertices, int origem) {

    // marca todos como nao visitado
    vector<bool> visitado(vertices, false);

    // guarda a distancia de saltos de cada vertice
    // comeca tudo com -1 (significa "nao alcancado ainda")
    vector<int> saltos(vertices, -1);

    // fila agora guarda par de (vertice, salto atual)
    queue<pair<int,int>> fila;

    // origem tem 0 saltos
    visitado[origem] = true;
    saltos[origem] = 0;
    fila.push(make_pair(origem, 0));

    cout << "\n==============================\n";
    cout << "   RESULTADO DO BFS\n";
    cout << "==============================\n";
    cout << "Ordem de visita:\n\n";

    while (!fila.empty()) {

        // agora pega o par (vertice, salto)
        int atual = fila.front().first;
        int saltoAtual = fila.front().second;
        fila.pop();

        // imprime o vertice e quantos saltos ele tem
        cout << "  Vertice " << atual 
             << " | saltos: " << saltoAtual << "\n";

        // percorre os vizinhos
        for (int i = 0; i < (int)adj[atual].size(); i++) {

            int vizinho = adj[atual][i].first;

            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                // vizinho tem um salto a mais que o atual
                saltos[vizinho] = saltoAtual + 1;
                fila.push(make_pair(vizinho, saltoAtual + 1));
            }
        }
    }

    // PARTE 2: verifica conectividade

    cout << "\n==============================\n";
    cout << "   VERIFICACAO DE ALCANCE\n";
    cout << "==============================\n";

    vector<int> naoAlcancados;

    for (int i = 0; i < vertices; i++) {
        if (!visitado[i]) {
            naoAlcancados.push_back(i);
        }
    }

    if (naoAlcancados.empty()) {
        cout << "Todos os vertices sao alcancaveis!\n";
        cout << "Grafo totalmente conectado: SIM\n";
    } else {
        cout << "Vertices NAO alcancaveis a partir de " << origem << ": ";
        for (int i = 0; i < (int)naoAlcancados.size(); i++) {
            cout << naoAlcancados[i];
            if (i != (int)naoAlcancados.size() - 1) cout << ", ";
        }
        cout << "\nGrafo totalmente conectado: NAO\n";
    }

    cout << "==============================\n";
}
