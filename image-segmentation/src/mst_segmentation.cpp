#include "mst_segmentation.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

// Estrutura para representar uma aresta
struct Edge {
    int src, dest, weight;
};

// Estrutura para representar um grafo
struct Graph {
    int V, E;
    std::vector<Edge> edges;
};

// Função para encontrar o conjunto de um elemento 'i'
int find(std::vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// Função para unir dois subconjuntos em um único subconjunto
void unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Função para segmentar a imagem usando MST
void segmentImageMST(const cv::Mat& inputImage, cv::Mat& outputImage) {
    int rows = inputImage.rows;
    int cols = inputImage.cols;
    int V = rows * cols;
    int E = 2 * rows * cols - rows - cols; // número máximo de arestas

    Graph graph = {V, E, {}};

    // Construir o grafo a partir da imagem
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (x < cols - 1) {
                int weight = std::abs(inputImage.at<uchar>(y, x) - inputImage.at<uchar>(y, x + 1));
                graph.edges.push_back({y * cols + x, y * cols + (x + 1), weight});
            }
            if (y < rows - 1) {
                int weight = std::abs(inputImage.at<uchar>(y, x) - inputImage.at<uchar>(y + 1, x));
                graph.edges.push_back({y * cols + x, (y + 1) * cols + x, weight});
            }
        }
    }

    // Ordenar as arestas por peso
    std::sort(graph.edges.begin(), graph.edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    // Estruturas auxiliares para a união e busca
    std::vector<int> parent(V);
    std::vector<int> rank(V, 0);

    for (int i = 0; i < V; ++i)
        parent[i] = i;

    std::vector<Edge> mst; // MST resultante

    // Aplicar o algoritmo de Kruskal
    for (const auto& edge : graph.edges) {
        int srcSet = find(parent, edge.src);
        int destSet = find(parent, edge.dest);

        if (srcSet != destSet) {
            mst.push_back(edge);
            unionSets(parent, rank, srcSet, destSet);
        }
    }

    // Criar a imagem segmentada (neste ponto você deve aplicar a segmentação conforme necessário)
    outputImage = inputImage.clone();
    // Implementar a segmentação de acordo com os critérios desejados usando a MST
}
