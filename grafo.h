#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <utility>

using namespace std;

class Grafo {

private:
    int vertices;
    vector<vector<pair<int, int> > > adj;

public:
    Grafo(int v);

    void inserirVertice();

    void inserirAresta(int u, int v, int peso);

    void removerAresta(int u, int v);

    void removerVertice(int v);

    void mostrar();
};

#endif
