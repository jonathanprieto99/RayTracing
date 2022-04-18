//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_CAMARA_H
#define RAYCASTINGV2_CAMARA_H

#include <vector>
#include "Luz.h"
#include "Objeto.h"
#include "CImg.h"
#include "vec3.h"

using namespace std;

using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
public:
    Camara () {
        prof_max = 4;
    }
    float fov, f, a, b;
    float w, h;
    vec3 eye, center, up;
    vec3 xe, ye, ze;
    int prof_max;
    CImg<BYTE> *pImg;

    void init(float angulo, float near, int ancho, int alto,
              vec3 pos, vec3 cen, vec3 _up);
    void calcular_vectores();

    void Renderizar();
    void Renderizar(Luz luz, vector<Objeto*> &vec_objetos);
    bool calcular_color(Rayo rayo, Luz &luz, vector<Objeto*> &vec_objetos, vec3 &color, int prof);

    void fresnel(vec3 I, vec3 N, float ior, float &kr );
    vec3 refract(vec3 I, vec3 N, float ior);
    float clamp(float n, float lower, float upper) {
        return max(lower, min(n, upper));
    }
};


#endif //RAYCASTINGV2_CAMARA_H
