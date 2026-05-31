#include <iostream>
#include "grafo.h"
#include "dijkstra.h"
#include "dfs.h"          // Adicionado (DFS) - Pedro
#include "bfs.h"		 // Adicionado (BFS) - Rian
 
using namespace std;
 
int main() {
 
    int vertices;
    int opcao = 1;
 
    cout << "=================================\n";
    cout << "     LOGISTICA DE ENTREGAS C++\n";
    cout << "=================================\n\n";
 
    Grafo g(4);
 
    g.inserirAresta(0, 1, 3);
    g.inserirAresta(0, 2, 5);
    g.inserirAresta(2, 3, 8);
    g.inserirAresta(1, 3, 4);
    g.inserirAresta(1, 2, 10);
 
    do {
 
        cout << "\n=========== MENU ===========\n";
        cout << "1 - Inserir Cidade\n";
        cout << "2 - Inserir Caminho\n";
        cout << "3 - Remover Caminho\n";
        cout << "4 - Remover Cidade\n";
        cout << "5 - Mostrar Mapa\n";
        cout << "6 - Menor caminho\n";       // Adicionado (Dijkstra) - Otto
        cout << "7 - DFS\n";
		cout << "8 - BFS\n";                 // Adicionado (DFS) - Pedro
        cout << "9 - Verificar Conectividade\n"; // Adicionado (DFS) - Pedro
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
                cout << "Cidade de origem: ";
                cin >> u;
                cout << "Cidade de destino: ";
                cin >> v;
                cout << "Peso do caminho: ";
                cin >> peso;
                g.inserirAresta(u, v, peso);
                break;
            }
 
            case 3: {
                int u, v;
                cout << "Cidade de origem: ";
                cin >> u;
                cout << "Cidade de destino: ";
                cin >> v;
                g.removerAresta(u, v);
                break;
            }
 
            case 4: {
                int v;
                cout << "Digite a cidade a remover: ";
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
                cout << "Cidade de origem: ";
                cin >> origem;
                cout << "Cidade de destino: ";
                cin >> destino;
                dijkstra(g.getAdj(), g.getVertices(), origem, destino);
                break;
            }
 
            // Adicionado (DFS) - Pedro
            case 7: {
                int origem;
                cout << "Cidade de origem: ";
                cin >> origem;
                dfs(g.getAdj(), g.getVertices(), origem);
                break;
            }
            
            // Adicionado (BFS) - Rian
            case 8: {
            	int origem;
    			cout << "Cidade de origem: ";
    			cin >> origem;

    			bfs(g.getAdj(), g.getVertices(), origem);

    			break;
			}
 
            // Adicionado (DFS) - Pedro
            case 9: {
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
