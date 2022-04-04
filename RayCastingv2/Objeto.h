//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_OBJETO_H
#define RAYCASTINGV2_OBJETO_H

#include "vec3.h"
#include "Rayo.h"

class Objeto {
public:
    Objeto(){ kd = 0.5; ke = 0; }
    vec3 color;
    float kd, ke;
    virtual bool interseccion(Rayo &rayo, float &t, vec3 &normal)=0;
};

class Esfera : public Objeto {
public:
    vec3 cen;
    float rad;
    bool interseccion(Rayo &rayo, float &t, vec3 &normal);
};



#endif //RAYCASTINGV2_OBJETO_H
