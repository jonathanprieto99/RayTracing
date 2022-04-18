//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_OBJETO_H
#define RAYCASTINGV2_OBJETO_H

#include "vec3.h"
#include "Rayo.h"

class Objeto {
public:
    Objeto(){ kd = 0.5; ke = 0; n = 1; kr=0; ior = 0; }
    vec3 color;
    float kd, ke, n;
    float kr, ior;
    virtual bool interseccion(Rayo &rayo, float &t, vec3 &normal)=0;
};

class Esfera : public Objeto {
public:
    vec3 cen;
    float rad;
    bool interseccion(Rayo &rayo, float &t, vec3 &normal);
};

class Plano : public Objeto {
public:
    vec3 n;
    float d;
    bool interseccion(Rayo &rayo, float &t, vec3 &normal);
};


class Cilindro : public Objeto {
public:
    vec3 pa, pb;
    float ra;
    bool interseccion(Rayo &rayo, float &t, vec3 &normal);
};
#endif //RAYCASTINGV2_OBJETO_H
