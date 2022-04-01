//
// Created by hgallegos on 25/03/2022.
//

#ifndef RAYCASTING_CAMARA_H
#define RAYCASTING_CAMARA_H

#include <iostream>
#include "CImg.h"

using namespace std;

using namespace cimg_library;
typedef unsigned char BYTE;

class vec3 {
public:
    float x, y, z;
    vec3(){}
    vec3(float _x, float _y, float _z) { x=_x; y=_y; z=_z; }
    float prod_punto(vec3 &v) {
        return x*v.x + y*v.y + z*v.z;
    }
    vec3 operator*(float s) { return vec3(x*s, y*s, z*s); }
    vec3 operator-(vec3 &v) { return vec3( x - v.x, y-v.y, z-v.z); }
};

class Rayo {
public:
    vec3 ori, dir;
};

class Esfera{
public:
    vec3 cen;
    float rad;
    vec3 color;
    bool interseccion(Rayo &rayo, float &t, vec3 &color, vec3 &normal) {
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
            color = this->color;
            return true;
        }
        return false;
    }
};

class Camara {
public:
    int tampixel, reshor, resver;
    vec3 vx, vy;

    CImg<BYTE> *pImg;

    void Renderizar();

};

void Camara::Renderizar() {
    reshor = 600; resver = 400;

    pImg = new CImg<BYTE>(reshor, resver, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayCasting en Perspectiva Ortogonal basica ");



    vx = vec3(1,0,0);
    vy = vec3(0,1,0);
    tampixel = 2;
    Rayo rayo;
    rayo.dir = vec3(0,0,-1);
    vec3 ori(0,0,5);

    Esfera esf1;
    esf1.cen = vec3(200,200,0);
    esf1.rad = 100;
    esf1.color = vec3(1,0,0);
    float t, t_min;
    vec3 color, color_min(1,1,1);

    for (int x = 0; x < reshor; x++) {
        ori.x = vx.x * (x+0.5) * tampixel;
        for (int y = 0; y < resver; y++) {
            ori.y = vy.y * (y+0.5) * tampixel;
            rayo.ori = ori;
            color_min = vec3(1,1,1); // color por defecto
            if (esf1.interseccion(rayo, t, color) ) {
                // pintar el pixel con el color de la esfera
                color_min = color;
            }
            //cout << ori.x << " " << ori.y <<  " " << ori.z;
            (*pImg)(x,resver-1-y,0) = (BYTE)(color_min.x * 255);
            (*pImg)(x,resver-1-y,1) = (BYTE)(color_min.y * 255);
            (*pImg)(x,resver-1-y,2) = (BYTE)(color_min.z * 255);
        }
    }

    dis_img.render((*pImg));
    dis_img.paint();

    while (!dis_img.is_closed()) {
        dis_img.wait();
    }
}

#endif //RAYCASTING_CAMARA_H
