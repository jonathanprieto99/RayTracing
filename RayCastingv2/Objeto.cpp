//
// Created by hgallegos on 1/04/2022.
//

#include <iostream>
using namespace std;
#include "Objeto.h"

bool Esfera::interseccion(Rayo &rayo, float &t, vec3 &normal) {
    vec3 d = rayo.dir;
    vec3 o = rayo.ori;
    float a = d.prod_punto( d );
    vec3 oc = o - cen;
    float b = d.prod_punto( oc ) * 2;
    float c = oc.prod_punto( oc ) - rad*rad;

    float det = b*b - 4 * a * c;
    if (det > 0) {
        float t1 = (-b - sqrt(det)) / (2*a);
        float t2 = (-b + sqrt(det)) / (2*a);
        t = min(t1, t2);
        if(t <= 0) {return false;}
        //color = this->color;
        vec3 pi = o + d * t;
        normal = pi-cen;
        normal.normalize();
        return true;
    }
    return false;
}