#include "ift_segmentation.h"
#include <queue>
#include <vector>
#include <limits>
#include <iostream>

// Estrutura para representar um pixel com seu custo
struct Pixel {
    int x, y;
    int cost;
    bool operator>(const Pixel& other) const {
        return cost > other.cost;
    }
};

// Função para segmentar a imagem usando IFT
void segmentImageIFT(const cv::Mat& inputImage, cv::Mat& outputImage) {
    int rows = inputImage.rows;
    int cols = inputImage.cols;

    // Inicializar as estruturas de dados
    std::vector<std::vector<int>> cost(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    std::priority_queue<Pixel, std::vector<Pixel>, std::greater<Pixel>> pq;

    // Inicializar os custos iniciais e a fila de prioridade
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            cost[y][x] = inputImage.at<uchar>(y, x);
            pq.push({x, y, cost[y][x]});
        }
    }

    // Implementar o algoritmo IFT
    while (!pq.empty()) {
        Pixel current = pq.top();
        pq.pop();

        // Verificar os vizinhos
        std::vector<std::pair<int, int>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto& neighbor : neighbors) {
            int nx = current.x + neighbor.first;
            int ny = current.y + neighbor.second;

            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows) {
                int newCost = current.cost + std::abs(inputImage.at<uchar>(current.y, current.x) - inputImage.at<uchar>(ny, nx));
                if (newCost < cost[ny][nx]) {
                    cost[ny][nx] = newCost;
                    pq.push({nx, ny, newCost});
                }
            }
        }
    }

    // Criar a imagem segmentada
    outputImage = inputImage.clone();
    // Implementar a segmentação de acordo com os critérios desejados usando o IFT
}
