#include "grafo.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

// ─────────────────────────────────────────────
// Construtor
// ─────────────────────────────────────────────
Grafo::Grafo(int n)
    : numVertices(n), numArestas(0),
      adj(n), nomes(n, "")
{
    if (n < 0)
        throw std::invalid_argument("Numero de vertices nao pode ser negativo.");
}

// ─────────────────────────────────────────────
// Auxiliar privado
// ─────────────────────────────────────────────
bool Grafo::indiceValido(int idx) const {
    return idx >= 0 && idx < numVertices;
}

// ─────────────────────────────────────────────
// Vértices
// ─────────────────────────────────────────────
void Grafo::inserirVertice(const std::string& nome) {
    nomes.push_back(nome);
    adj.emplace_back();          // nova lista de adjacência vazia
    ++numVertices;
}

void Grafo::removerVertice(int idx) {
    if (!indiceValido(idx)) {
        std::cerr << "[ERRO] Indice de vertice invalido: " << idx << "\n";
        return;
    }

    // 1. Conta e remove todas as arestas que saem deste vértice
    numArestas -= static_cast<int>(adj[idx].size());
    adj.erase(adj.begin() + idx);
    nomes.erase(nomes.begin() + idx);
    --numVertices;

    // 2. Remove arestas que chegam neste vértice e ajusta índices
    for (auto& lista : adj) {
        // Remove entradas que apontavam para 'idx'
        auto novo_fim = std::remove_if(lista.begin(), lista.end(),
            [idx, this](const std::pair<int,int>& par) {
                if (par.first == idx) {
                    --numArestas;
                    return true;
                }
                return false;
            });
        lista.erase(novo_fim, lista.end());

        // Ajusta índices maiores que 'idx' (shifted pelo erase)
        for (auto& par : lista) {
            if (par.first > idx)
                --par.first;
        }
    }
}

// ─────────────────────────────────────────────
// Arestas
// ─────────────────────────────────────────────
bool Grafo::inserirAresta(int origem, int destino, int peso) {
    if (!indiceValido(origem) || !indiceValido(destino)) {
        std::cerr << "[ERRO] Indices invalidos para aresta ("
                  << origem << " -> " << destino << ").\n";
        return false;
    }
    if (origem == destino) {
        std::cerr << "[ERRO] Laco (self-loop) nao permitido.\n";
        return false;
    }
    if (existeAresta(origem, destino)) {
        std::cerr << "[AVISO] Aresta " << origem << " -> " << destino
                  << " ja existe. Use remover antes de reinserir.\n";
        return false;
    }

    adj[origem].emplace_back(destino, peso);
    ++numArestas;
    return true;
}

bool Grafo::removerAresta(int origem, int destino) {
    if (!indiceValido(origem) || !indiceValido(destino)) {
        std::cerr << "[ERRO] Indices invalidos para remocao.\n";
        return false;
    }

    auto& lista = adj[origem];
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (it->first == destino) {
            lista.erase(it);
            --numArestas;
            return true;
        }
    }
    std::cerr << "[AVISO] Aresta " << origem << " -> " << destino
              << " nao encontrada.\n";
    return false;
}

// ─────────────────────────────────────────────
// Consultas
// ─────────────────────────────────────────────
int Grafo::totalVertices() const  { return numVertices; }
int Grafo::totalArestas()   const  { return numArestas;  }

bool Grafo::existeAresta(int origem, int destino) const {
    if (!indiceValido(origem) || !indiceValido(destino))
        return false;
    for (const auto& par : adj[origem])
        if (par.first == destino)
            return true;
    return false;
}

std::string Grafo::nomeVertice(int idx) const {
    if (!indiceValido(idx)) return "INVALIDO";
    return nomes[idx];
}

// ─────────────────────────────────────────────
// Exibição
// ─────────────────────────────────────────────
void Grafo::exibirListaAdjacencia() const {
    const int COL_ID   = 4;
    const int COL_NOME = 26;

    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║        GRAFO DE LOGISTICA — LISTA DE ADJACENCIA             ║\n";
    std::cout << "╠══════════════════════════════════════════════════════════════╣\n";
    std::cout << "║  Vertices: " << std::setw(3) << numVertices
              << "   |   Arestas: " << std::setw(3) << numArestas
              << "                                  ║\n";
    std::cout << "╠══════════════════════════════════════════════════════════════╣\n";

    for (int i = 0; i < numVertices; ++i) {
        // Cabeçalho do vértice
        std::cout << "║  [" << std::setw(COL_ID) << i << "]  "
                  << std::left << std::setw(COL_NOME) << nomes[i]
                  << std::right;

        if (adj[i].empty()) {
            std::cout << "  (sem saidas)         ║\n";
        } else {
            std::cout << "                       ║\n";
            for (const auto& [dest, peso] : adj[i]) {
                std::cout << "║         ├─── ["
                          << std::setw(2) << dest << "] "
                          << std::left << std::setw(22) << nomes[dest]
                          << std::right
                          << " | dist: "
                          << std::setw(4) << peso << " km  ║\n";
            }
        }
        std::cout << "╠══════════════════════════════════════════════════════════════╣\n";
    }
    std::cout << "╚══════════════════════════════════════════════════════════════╝\n";
}

void Grafo::exibirEstatisticas() const {
    std::cout << "\n──────────────────────────────────────\n";
    std::cout << "  Estatisticas do Grafo\n";
    std::cout << "──────────────────────────────────────\n";
    std::cout << "  Total de vertices : " << numVertices << "\n";
    std::cout << "  Total de arestas  : " << numArestas  << "\n";

    // Grau de saída de cada vértice
    std::cout << "\n  Grau de saida por vertice:\n";
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "    [" << i << "] " << std::left << std::setw(22)
                  << nomes[i] << " -> " << adj[i].size() << " rota(s)\n";
    }
    std::cout << "──────────────────────────────────────\n";
}
