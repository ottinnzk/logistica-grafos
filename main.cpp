#include <iostream>
#include "grafo.h"
#include "dijkstra.h"
#include "dfs.h"          // Adicionado (DFS) - Pedro
 
using namespace std;
 
int main() {
 
    int vertices;
    int opcao = 1;
 
    cout << "=================================\n";
    cout << "     SISTEMA DE GRAFOS C++\n";
    cout << "=================================\n\n";
 
    cout << "Digite a quantidade inicial de vertices: ";
    cin >> vertices;
 
    Grafo g(vertices);
 
    g.inserirAresta(0, 1, 4);
    g.inserirAresta(0, 2, 7);
    g.inserirAresta(1, 2, 5);
    g.inserirAresta(1, 3, 2);
    g.inserirAresta(2, 4, 8);
    g.inserirAresta(3, 4, 6);
    g.inserirAresta(3, 5, 3);
    g.inserirAresta(4, 5, 9);
 
    do {
 
        cout << "\n=========== MENU ===========\n";
        cout << "1 - Inserir Vertice\n";
        cout << "2 - Inserir Aresta\n";
        cout << "3 - Remover Aresta\n";
        cout << "4 - Remover Vertice\n";
        cout << "5 - Mostrar Grafo\n";
        cout << "6 - Menor caminho\n";       // Adicionado (Dijkstra) - Otto
        cout << "7 - DFS\n";                 // Adicionado (DFS) - Pedro
        cout << "8 - Verificar Conectividade\n"; // Adicionado (DFS) - Pedro
        cout << "0 - Sair\n";
        cout << "============================\n";
 
        cout << "Escolha uma opcao: ";
        cin >> opcao;
 
        switch(opcao) {
 
            case 1: {
                g.inserirVertice();
                break;
            }
 
            case 2: {
                int u, v, peso;
                cout << "Vertice origem: ";
                cin >> u;
                cout << "Vertice destino: ";
                cin >> v;
                cout << "Peso da aresta: ";
                cin >> peso;
                g.inserirAresta(u, v, peso);
                break;
            }
 
            case 3: {
                int u, v;
                cout << "Vertice origem: ";
                cin >> u;
                cout << "Vertice destino: ";
                cin >> v;
                g.removerAresta(u, v);
                break;
            }
 
            case 4: {
                int v;
                cout << "Digite o vertice a remover: ";
                cin >> v;
                g.removerVertice(v);
                break;
            }
 
            case 5: {
                g.mostrar();
                break;
            }
 
            // Adicionado - Otto
            case 6: {
                int origem, destino;
                cout << "Vertice de origem: ";
                cin >> origem;
                cout << "Vertice de destino: ";
                cin >> destino;
                dijkstra(g.getAdj(), g.getVertices(), origem, destino);
                break;
            }
 
            // Adicionado (DFS) - Pedro
            case 7: {
                int origem;
                cout << "Vertice de origem: ";
                cin >> origem;
                dfs(g.getAdj(), g.getVertices(), origem);
                break;
            }
 
            // Adicionado (DFS) - Pedro
            case 8: {
                if (verificarConectividade(g.getAdj(), g.getVertices()))
                    cout << "\nO grafo E conexo!\n";
                else
                    cout << "\nO grafo NAO e conexo!\n";
                break;
            }
 
            case 0: {
                cout << "\nEncerrando programa...\n";
                break;
            }
 
            default: {
                cout << "\nOpcao invalida!\n";
            }
        }
 
    } while(opcao != 0);
 
    return 0;
}