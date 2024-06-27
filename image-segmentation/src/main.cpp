#include <opencv2/opencv.hpp>
#include "mst_segmentation.h"
#include "ift_segmentation.h"

int main() {
    std::string imagePath = "data/example.png";
    cv::Mat inputImage = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    if (inputImage.empty()) {
        std::cerr << "Erro ao carregar a imagem!" << std::endl;
        return -1;
    }

    cv::Mat outputImageMST;
    segmentImageMST(inputImage, outputImageMST);
    cv::imshow("Segmented Image (MST)", outputImageMST);

    cv::Mat outputImageIFT;
    segmentImageIFT(inputImage, outputImageIFT);
    cv::imshow("Segmented Image (IFT)", outputImageIFT);

    cv::waitKey(0);
    return 0;
}