#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

struct Vertice {
    int id;
    std::string nome;
    std::string tipo; // "deposito", "cliente", "ponto_intermediario"
    
    Vertice(int id, const std::string& nome, const std::string& tipo)
        : id(id), nome(nome), tipo(tipo) {}
};

struct Aresta {
    int origem;
    int destino;
    float peso; // distancia, tempo, custo, etc
    std::string descricao;
    
    Aresta(int origem, int destino, float peso, const std::string& descricao = "")
        : origem(origem), destino(destino), peso(peso), descricao(descricao) {}
};

class Grafo {
private:
    std::unordered_map<int, Vertice> vertices;
    std::vector<Aresta> arestas;
    bool direcionado;
    
public:
    // Construtor
    Grafo(bool direcionado = true);
    
    // Operações com vértices
    void inserirVertice(int id, const std::string& nome, const std::string& tipo);
    void removerVertice(int id);
    bool existeVertice(int id) const;
    Vertice* obterVertice(int id);
    
    // Operações com arestas
    void inserirAresta(int origem, int destino, float peso, const std::string& descricao = "");
    void removerAresta(int origem, int destino);
    bool existeAresta(int origem, int destino) const;
    
    // Exibição
    void exibirListaAdjacencia() const;
    void exibirGrafo() const;
    
    // Getters
    int obterQuantidadeVertices() const;
    int obterQuantidadeArestas() const;
    std::vector<std::pair<int, float>> obterAdjacentes(int id) const;
};

#endif // GRAFO_H
