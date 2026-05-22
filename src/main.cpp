#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <sstream>

class LogisticaEntregas {
private:
    Grafo grafo;
    
    void carregarDados(const std::string& arquivo) {
        std::ifstream file(arquivo);
        if (!file.is_open()) {
            std::cout << "⚠️  Arquivo não encontrado. Criando dados padrão...\n\n";
            criarDadosPadroes();
            return;
        }
        
        std::string linha;
        int secao = 0; // 0: vértices, 1: arestas
        
        while (std::getline(file, linha)) {
            if (linha.empty() || linha[0] == '#') continue;
            
            if (linha.find("VERTICES") != std::string::npos) {
                secao = 0;
                continue;
            }
            if (linha.find("ARESTAS") != std::string::npos) {
                secao = 1;
                continue;
            }
            
            std::istringstream iss(linha);
            
            if (secao == 0) {
                int id;
                std::string nome, tipo;
                if (iss >> id >> nome >> tipo) {
                    grafo.inserirVertice(id, nome, tipo);
                }
            } else if (secao == 1) {
                int origem, destino;
                float peso;
                if (iss >> origem >> destino >> peso) {
                    grafo.inserirAresta(origem, destino, peso);
                }
            }
        }
        file.close();
        std::cout << "✅ Dados carregados com sucesso!\n\n";
    }
    
    void criarDadosPadroes() {
        // Vértices: 1 depósito, 4 clientes, 2 pontos intermediários
        grafo.inserirVertice(0, "Deposito_Central", "deposito");
        grafo.inserirVertice(1, "Cliente_A", "cliente");
        grafo.inserirVertice(2, "Cliente_B", "cliente");
        grafo.inserirVertice(3, "Cliente_C", "cliente");
        grafo.inserirVertice(4, "Cliente_D", "cliente");
        grafo.inserirVertice(5, "Ponto_Intermediario_1", "ponto_intermediario");
        grafo.inserirVertice(6, "Ponto_Intermediario_2", "ponto_intermediario");
        
        // Arestas: 10 rotas com distâncias
        grafo.inserirAresta(0, 5, 12.5);  // Depósito → Ponto 1
        grafo.inserirAresta(0, 6, 15.0);  // Depósito → Ponto 2
        grafo.inserirAresta(5, 1, 8.3);   // Ponto 1 → Cliente A
        grafo.inserirAresta(5, 2, 6.7);   // Ponto 1 → Cliente B
        grafo.inserirAresta(6, 3, 9.2);   // Ponto 2 → Cliente C
        grafo.inserirAresta(6, 4, 11.5);  // Ponto 2 → Cliente D
        grafo.inserirAresta(1, 2, 5.0);   // Cliente A → Cliente B
        grafo.inserirAresta(2, 3, 7.3);   // Cliente B → Cliente C
        grafo.inserirAresta(3, 4, 8.9);   // Cliente C → Cliente D
        grafo.inserirAresta(5, 6, 18.0);  // Ponto 1 → Ponto 2
        
        std::cout << "✅ Dados padrão criados com sucesso!\n\n";
    }
    
    void exibirMenu() {
        std::cout << "\n🚚 SISTEMA DE LOGÍSTICA DE ENTREGAS - GRAFOS\n";
        std::cout << "==========================================\n";
        std::cout << "1. Exibir lista de adjacência\n";
        std::cout << "2. Inserir vértice\n";
        std::cout << "3. Inserir aresta\n";
        std::cout << "4. Remover vértice\n";
        std::cout << "5. Remover aresta\n";
        std::cout << "6. Exibir informações do grafo\n";
        std::cout << "0. Sair\n";
        std::cout << "==========================================\n";
        std::cout << "Escolha uma opção: ";
    }
    
    void inserirVertice() {
        int id;
        std::string nome, tipo;
        std::cout << "\nDigite o ID do vértice: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Digite o nome do vértice: ";
        std::getline(std::cin, nome);
        std::cout << "Digite o tipo (deposito/cliente/ponto_intermediario): ";
        std::getline(std::cin, tipo);
        
        grafo.inserirVertice(id, nome, tipo);
    }
    
    void inserirAresta() {
        int origem, destino;
        float peso;
        std::cout << "\nDigite o ID do vértice de origem: ";
        std::cin >> origem;
        std::cout << "Digite o ID do vértice de destino: ";
        std::cin >> destino;
        std::cout << "Digite o peso (distância em km): ";
        std::cin >> peso;
        
        grafo.inserirAresta(origem, destino, peso);
    }
    
    void removerVertice() {
        int id;
        std::cout << "\nDigite o ID do vértice a remover: ";
        std::cin >> id;
        
        grafo.removerVertice(id);
    }
    
    void removerAresta() {
        int origem, destino;
        std::cout << "\nDigite o ID do vértice de origem: ";
        std::cin >> origem;
        std::cout << "Digite o ID do vértice de destino: ";
        std::cin >> destino;
        
        grafo.removerAresta(origem, destino);
    }
    
public:
    LogisticaEntregas() : grafo(true) {
        carregarDados("dados.txt");
    }
    
    void executar() {
        int opcao;
        
        while (true) {
            exibirMenu();
            std::cin >> opcao;
            
            switch (opcao) {
                case 1:
                    grafo.exibirListaAdjacencia();
                    break;
                case 2:
                    inserirVertice();
                    break;
                case 3:
                    inserirAresta();
                    break;
                case 4:
                    removerVertice();
                    break;
                case 5:
                    removerAresta();
                    break;
                case 6:
                    grafo.exibirGrafo();
                    break;
                case 0:
                    std::cout << "\n👋 Encerrando o programa. Até logo!\n";
                    return;
                default:
                    std::cout << "⚠️  Opção inválida!\n";
            }
        }
    }
};

int main() {
    std::cout << "Inicializando Sistema...\n";
    LogisticaEntregas sistema;
    sistema.executar();
    return 0;
}
