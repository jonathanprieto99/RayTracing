//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_CAMARA_H
#define RAYCASTINGV2_CAMARA_H

#include "CImg.h"
#include "vec3.h"

using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
public:
    float fov, f, a, b;
    float w, h;
    vec3 eye, center, up;
    vec3 xe, ye, ze;
    CImg<BYTE> *pImg;

    void init(float angulo, float near, int ancho, int alto,
              vec3 pos, vec3 cen, vec3 _up);
    void calcular_vectores();

    void Renderizar();
};


#endif //RAYCASTINGV2_CAMARA_H
