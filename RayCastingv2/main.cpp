#include <iostream>

#include "Camara.h"

int main() {
    Camara cam;
    cam.init(60,10, 600, 400,
             vec3(20,40, 80),
             vec3(0,0,0),
             vec3(0,1,0));
    cam.calcular_vectores();
    cam.Renderizar();
    return 0;
}
