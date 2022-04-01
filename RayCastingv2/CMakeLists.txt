cmake_minimum_required(VERSION 3.19)
project(RayCastingv2)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayCastingv2 main.cpp Mundo.cpp Mundo.h Camara.cpp Camara.h Luz.cpp Luz.h Rayo.cpp Rayo.h Objeto.cpp Objeto.h vec3.cpp vec3.h cImg.h)