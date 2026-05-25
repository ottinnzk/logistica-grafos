#ifndef DFS_H
#define DFS_H

#include <vector>
#include <utility>
using namespace std;

// Funcao para auxiliar DFS
void dfsRecursivo(vector<vector<pair<int, int> > >& adj, int vertice, vector<bool>& visitado);

// Executa DFS a partir de um vertice de origem e exibe a ordem de visita
void dfs(vector<vector<pair<int, int> > >& adj, int vertices, int origem);

// Verifica o grafo e conexo
bool verificarConectividade(vector<vector<pair<int, int> > >& adj, int vertices);

#endif