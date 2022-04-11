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

bool Plano::interseccion(Rayo &rayo, float &t, vec3 &normal) {
    t = - (n.prod_punto(rayo.ori) + d) / (n.prod_punto(rayo.dir));
    if (t < 0) {
        return false;
    }
    // falta corregir la normal segun la direccion del rayo
    normal = n;
    return true;
}

bool Cilindro::interseccion(Rayo &rayo, float &t, vec3 &normal) {
    vec3 ro = rayo.ori;
    vec3 rd = rayo.dir;
    vec3 ca = pb-pa;
    vec3 oc = ro-pa;
    float caca = ca.prod_punto(ca);
    float card = ca.prod_punto(rd);
    float caoc = ca.prod_punto(oc);
    float a = caca - card*card;
    float b = caca * oc.prod_punto(rd) - caoc*card;
    float c = caca * oc.prod_punto(oc) - caoc*caoc - ra*ra*caca;
    float h = b*b - a*c;
    if( h<0.0 ) {
        return false; //no intersection
    }
    h = sqrt(h);
    t = (-b-h)/a;
    if (t <= 0) return false;
    // body
    float y = caoc + t*card;
    if( y>0.0 && y<caca ) {
        normal = (oc + rd * t - ca * y / caca)/ra;
        normal.normalize();
        return true;
    }
    // caps
    t = (((y<0.0)?0.0:caca) - caoc)/card;
    if (t <= 0) return false;
    if( abs(b + a * t)<h ) {
        normal = ca * sgn(y) /caca;
        normal.normalize();
        return true;
    }
    return false; //no intersection
}