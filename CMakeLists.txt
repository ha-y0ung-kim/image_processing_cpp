cmake_minimum_required(VERSION 3.1)
project(ImageProcessing VERSION 0.1.0 LANGUAGES CXX)
add_executable(main main.cpp src/classes/Filter.cpp src/classes/Image.cpp src/classes/filterset.cpp)
target_compile_features(main PUBLIC cxx_std_20)