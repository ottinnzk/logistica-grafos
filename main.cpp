/*
 * ============================================================
 *  Sistema de Logistica de Entregas — Grafo Ponderado
 * ============================================================
 *  Estrutura de dados:
 *    vector<vector<pair<int,int>>> — lista de adjacência ponderada
 *
 *  Vértices : centros de distribuição / cidades do Brasil
 *  Arestas  : rotas de entrega entre os pontos
 *  Pesos    : distância aproximada em km
 * ============================================================
 */

#include "grafo.h"
#include <iostream>

// ─────────────────────────────────────────────────────────────
// Separador visual
// ─────────────────────────────────────────────────────────────
static void secao(const std::string& titulo) {
    std::cout << "\n══════════════════════════════════════════\n";
    std::cout << "  " << titulo << "\n";
    std::cout << "══════════════════════════════════════════\n";
}

// ─────────────────────────────────────────────────────────────
// Constrói o grafo inicial com dados inseridos manualmente
// ─────────────────────────────────────────────────────────────
Grafo construirGrafoInicial() {
    /*
     *  Índice | Vértice
     *  -------+-------------------------
     *    0    | Sao Paulo (Hub Central)
     *    1    | Rio de Janeiro
     *    2    | Belo Horizonte
     *    3    | Curitiba
     *    4    | Porto Alegre
     *    5    | Brasilia
     *    6    | Salvador
     */
    Grafo g(7);

    // ── Nomes dos vértices ──────────────────────────────────
    // (o construtor criou 7 slots com nome ""; vamos redefinir
    //  usando inserirVertice para demonstrar a função,
    //  mas aqui fazemos via reinicialização limpa)

    // Recriamos com nomes desde o início usando inserirVertice
    // Para isso, partimos de um grafo vazio e inserimos 7 vértices.
    Grafo g2(0);  // grafo vazio

    g2.inserirVertice("Sao Paulo (Hub)");   // 0
    g2.inserirVertice("Rio de Janeiro");    // 1
    g2.inserirVertice("Belo Horizonte");    // 2
    g2.inserirVertice("Curitiba");          // 3
    g2.inserirVertice("Porto Alegre");      // 4
    g2.inserirVertice("Brasilia");          // 5
    g2.inserirVertice("Salvador");          // 6

    // ── Arestas (rotas de entrega) ──────────────────────────
    // formato: inserirAresta(origem, destino, peso_km)
    //
    // Rotas saindo de São Paulo (hub central)
    g2.inserirAresta(0, 1, 429);   // SP -> RJ
    g2.inserirAresta(0, 2, 586);   // SP -> BH
    g2.inserirAresta(0, 3, 408);   // SP -> Curitiba
    g2.inserirAresta(0, 5, 1015);  // SP -> Brasília

    // Rotas regionais / interligações
    g2.inserirAresta(1, 2, 434);   // RJ -> BH
    g2.inserirAresta(2, 5, 716);   // BH -> Brasília
    g2.inserirAresta(2, 6, 1373);  // BH -> Salvador
    g2.inserirAresta(3, 4, 476);   // Curitiba -> Porto Alegre
    g2.inserirAresta(4, 3, 476);   // Porto Alegre -> Curitiba (bidirecional)
    g2.inserirAresta(5, 6, 1441);  // Brasília -> Salvador
    g2.inserirAresta(6, 1, 1650);  // Salvador -> RJ

    // ── Rota extra: retorno de RJ para SP ───────────────────
    g2.inserirAresta(1, 0, 429);   // RJ -> SP

    return g2;
}

// ─────────────────────────────────────────────────────────────
// Demonstrações das operações de remoção
// ─────────────────────────────────────────────────────────────
void demonstrarRemocaoAresta(Grafo& g) {
    secao("DEMO: Remover Aresta (BH -> Salvador)");
    std::cout << "  Removendo rota: Belo Horizonte -> Salvador [2 -> 6]\n";

    if (g.removerAresta(2, 6))
        std::cout << "  [OK] Aresta removida com sucesso.\n";

    g.exibirListaAdjacencia();
}

void demonstrarInsercaoVertice(Grafo& g) {
    secao("DEMO: Inserir Novo Vertice (Recife)");
    std::cout << "  Adicionando: Recife como vertice 7\n";
    g.inserirVertice("Recife");

    // Liga Recife a Salvador e a Brasília
    g.inserirAresta(7, 6, 839);   // Recife -> Salvador
    g.inserirAresta(5, 7, 2126);  // Brasília -> Recife
    std::cout << "  [OK] Vertice e arestas inseridas.\n";

    g.exibirListaAdjacencia();
}

void demonstrarRemocaoVertice(Grafo& g) {
    secao("DEMO: Remover Vertice (Porto Alegre = idx 4)");
    std::cout << "  Removendo Porto Alegre e todas as suas rotas...\n";
    g.removerVertice(4);
    std::cout << "  [OK] Vertice removido. Indices reajustados.\n";

    g.exibirListaAdjacencia();
}

// ─────────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────────
int main() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║      SISTEMA DE LOGISTICA DE ENTREGAS — C++                 ║\n";
    std::cout << "║      Estrutura: vector<vector<pair<int,int>>>               ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════╝\n";

    // ── 1. Constrói o grafo base ────────────────────────────
    secao("1. CONSTRUINDO GRAFO INICIAL");
    Grafo grafo = construirGrafoInicial();
    std::cout << "  Grafo criado com " << grafo.totalVertices()
              << " vertices e "        << grafo.totalArestas()
              << " arestas.\n";

    // ── 2. Exibe lista de adjacência completa ───────────────
    secao("2. LISTA DE ADJACENCIA — ESTADO INICIAL");
    grafo.exibirListaAdjacencia();

    // ── 3. Estatísticas ─────────────────────────────────────
    secao("3. ESTATISTICAS DO GRAFO");
    grafo.exibirEstatisticas();

    // ── 4. Demonstrações de operações ───────────────────────
    demonstrarRemocaoAresta(grafo);
    demonstrarInsercaoVertice(grafo);
    demonstrarRemocaoVertice(grafo);

    // ── 5. Estado final ─────────────────────────────────────
    secao("5. ESTADO FINAL DO GRAFO");
    grafo.exibirListaAdjacencia();
    grafo.exibirEstatisticas();

    std::cout << "\n  Programa encerrado com sucesso.\n\n";
    return 0;
}
