#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include <utility>

// Representa um grafo ponderado e direcionado usando lista de adjacência
// Vértices = centros de distribuição / cidades
// Arestas  = rotas de entrega
// Pesos    = distância em km entre os pontos

class Grafo {
public:
    // Construtor: inicializa o grafo com 'n' vértices
    explicit Grafo(int n);

    // ---------- Vértices ----------
    // Adiciona um novo vértice com nome (ex.: "São Paulo")
    void inserirVertice(const std::string& nome);

    // Remove vértice pelo índice e todas as arestas associadas
    void removerVertice(int idx);

    // ---------- Arestas ----------
    // Insere aresta direcionada de 'origem' para 'destino' com peso
    // Retorna false se os índices forem inválidos
    bool inserirAresta(int origem, int destino, int peso);

    // Remove aresta direcionada de 'origem' para 'destino'
    // Retorna false se não existir
    bool removerAresta(int origem, int destino);

    // ---------- Consultas ----------
    int  totalVertices()  const;
    int  totalArestas()   const;
    bool existeAresta(int origem, int destino) const;

    // Retorna o nome do vértice pelo índice
    std::string nomeVertice(int idx) const;

    // ---------- Exibição ----------
    void exibirListaAdjacencia() const;

    // Exibe estatísticas resumidas do grafo
    void exibirEstatisticas() const;

private:
    int numVertices;
    int numArestas;

    // Lista de adjacência: adj[v] = lista de (vizinho, peso)
    std::vector<std::vector<std::pair<int, int>>> adj;

    // Nomes dos vértices
    std::vector<std::string> nomes;

    // Verifica se índice está dentro do intervalo válido
    bool indiceValido(int idx) const;
};

#endif // GRAFO_H
