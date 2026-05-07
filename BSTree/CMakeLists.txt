cmake_minimum_required(VERSION 3.10)
project(BSTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем директорию с заголовочными файлами
include_directories(include)

# Создаём исполняемый файл из всех cpp файлов в папке src
file(GLOB SOURCES "src/*.cpp")
add_executable(BSTree ${SOURCES}
        src/main.cpp)