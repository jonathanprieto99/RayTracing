//
// Created by hgallegos on 25/03/2022.
//

#ifndef RAYCASTING_CAMARA_H
#define RAYCASTING_CAMARA_H

#include <iostream>

using namespace std;

class vec3 {
public:
    float x, y, z;
    vec3(){}
    vec3(float _x, float _y, float _z) { x=_x; y=_y; z=_z; }
    float prod_punto(vec3 &v) {

    }
    vec3 operator*(float s) { return vec3(x*s, y*s, z*s); }
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
    bool interseccion(Rayo &rayo, float &t, vec3 &color) {
        float a = rayo.dir.prod_punto( rayo.dir );
    }
};

class Camara {
public:
    int tampixel, reshor, resver;
    vec3 vx, vy;

    void Renderizar();

};

void Camara::Renderizar() {
    reshor = 6; resver = 4;
    vx = vec3(1,0,0);
    vy = vec3(0,1,0);
    tampixel = 1;
    Rayo rayo;
    rayo.dir = vec3(0,0,-1);
    vec3 ori(0,0,5);

    Esfera esf1;
    esf1.cen = vec3(2,2,0);
    esf1.rad = 1;
    esf1.color = vec3(1,0,0);
    float t, t_min;
    vec3 color;

    for (int x = -reshor/2; x < reshor/2; x++) {
        ori.x = vx.x * (x-0.5) * tampixel;
        for (int y = -resver/2; y < resver/2; y++) {
            ori.y = vx.y * (y-0.5) * tampixel;
            rayo.ori = ori;
            /*if (esf1.interseccion(rayo, t, color) ) {
                // pintar el pixel con el color de la esfera

            }*/
            cout << ori.x << " " << ori.y <<  " " << ori.z;
        }
    }
}

#endif //RAYCASTING_CAMARA_H
