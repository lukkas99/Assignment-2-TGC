cmake_minimum_required(VERSION 3.10)
project(image_segmentation)



# Encontre o pacote OpenCV
find_package(OpenCV REQUIRED)

# Inclui diretórios de cabeçalho do projeto
include_directories(${OpenCV_INCLUDE_DIRS})

# Arquivos fonte do projeto
set(SOURCES 
    src/main.cpp
    src/mst_segmentation.cpp
    src/ift_segmentation.cpp
)

# Executável de saída
add_executable(image_segmentation ${SOURCES})

# Liga o OpenCV ao executável
target_link_libraries(image_segmentation ${OpenCV_LIBS})
