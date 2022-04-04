//
// Created by hgallegos on 1/04/2022.
//

#include "Camara.h"
#include "Rayo.h"
#include "Objeto.h"
#include <iostream>
#include <math.h>
#include "Luz.h"
using namespace std;

void Camara::init(float angulo, float _near, int ancho, int alto,
                  vec3 pos, vec3 cen, vec3 _up) {
    fov = angulo;
    eye = pos;
    center = cen;
    up = _up;
    f = _near;
    w = ancho;
    h = alto;

    a = 2*f*tan(fov * 3.14159/360);
    b = a * w / h;
}
void Camara::calcular_vectores() {
    ze = eye - center;
    ze.normalize();
    xe = up.prod_cruz(ze);
    xe.normalize();
    ye = ze.prod_cruz(xe);
}
void Camara::Renderizar(Luz luz, vector<Objeto*> &vec_objetos) {
    pImg = new CImg<BYTE>(w, h, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayCasting en Perspectiva ");
    Rayo rayo;
    rayo.ori = eye;
    float t, t_min;
    vec3 color, color_min(1,1,1);
    vec3 normal, normal_min;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            rayo.dir = ze*(-f) + ye*a*(y/h -0.5) + xe*b*(x/w-0.5);
            rayo.dir.normalize();
            //color_min = vec3(1,1,1);
            bool interse = calcular_color(rayo, luz, vec_objetos, color, 1);

            (*pImg)(x,h-1-y,0) = (BYTE)(color.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color.z * 255);
        }
    }

    dis_img.render((*pImg));
    dis_img.paint();

    while (!dis_img.is_closed()) {
        dis_img.wait();
    }
}

bool Camara::calcular_color(Rayo rayo, Luz &luz, vector<Objeto*> &vec_objetos, vec3 &color, int prof) {
    if (prof >= prof_max){
        color = vec3(1,1,1);
        return false;
    }
    float t_calculado, t = 1000000;
    vec3 color_min(1,1,1);
    vec3 normal, N;
    bool hay_interseccion = false;
    Objeto *pObj;

    for (auto pObjTmp : vec_objetos) {
        if (pObjTmp->interseccion(rayo, t_calculado, normal)) {
            hay_interseccion = true;
            if ( t_calculado < t ) {
                t = t_calculado;
                N = normal;
                pObj = pObjTmp;
            }
        }
    }
    if (hay_interseccion) {
        vec3 luz_ambiente = luz.color * 0.1;
        // pintar el pixel con el color de la esfera
        color_min = pObj->color;
        vec3 L = luz.pos - (rayo.ori + rayo.dir * t);
        L.normalize();
        float factor_difuso = L.prod_punto(N);
        vec3 luz_difusa(0, 0, 0);
        if (factor_difuso > 0) {
            luz_difusa = luz.color * pObj->kd * factor_difuso;
        }
        color_min = color_min * (luz_ambiente + luz_difusa);

        if (pObj->ke > 0) {
            Rayo rayo_ref;

            vec3 R = N * (N.prod_punto(-rayo.dir)) * 2 + rayo.dir;
            R.normalize();
            rayo_ref.dir = R;
            rayo_ref.ori = (rayo.ori + rayo.dir * t) + R * 0.1;
            vec3 color_reflejado;
            // lanzar rayo secundario
            bool interse = calcular_color(rayo_ref, luz, vec_objetos, color_reflejado, prof+1);
            // calcular intersecciones
            color_min = (color_min + color_reflejado)*0.5;
        }
        color_min.max_to_one();
        color = color_min;
        return true;
    }
    color = color_min;
    return false;
}


void Camara::Renderizar() {
    pImg = new CImg<BYTE>(w, h, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayCasting en Perspectiva ");

    Rayo rayo;
    rayo.ori = eye;
    float t, t_min;
    vec3 color, color_min(1,1,1);
    vec3 normal, normal_min;

    Esfera esf1;
    esf1.cen = vec3(0,0,0);
    esf1.rad = 20;
    esf1.color = vec3(1,0,0);
    esf1.kd = 0.8;
    Luz luz(vec3(30,30,30), vec3(1,1,1));

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            rayo.dir = ze*(-f) + ye*a*(y/h -0.5) + xe*b*(x/w-0.5);
            rayo.dir.normalize();
            color_min = vec3(1,1,1);

            if (esf1.interseccion(rayo, t, normal) ) {
                vec3 luz_ambiente = luz.color * 0.1;
                // pintar el pixel con el color de la esfera
                color_min = esf1.color;
                vec3 L = luz.pos - (rayo.ori + rayo.dir * t);
                L.normalize();
                float factor_difuso = L.prod_punto( normal );
                vec3 luz_difusa(0,0,0);
                if ( factor_difuso > 0 ) {
                    luz_difusa = luz.color * esf1.kd * factor_difuso;
                }
                color_min = color_min * (luz_ambiente + luz_difusa);

                if ( esf1.ke > 0) {
                    // lanzar rayo secundario
                    // calcular intersecciones
                }

                color_min.max_to_one();
            }
            //cout << ori.x << " " << ori.y <<  " " << ori.z;
            (*pImg)(x,h-1-y,0) = (BYTE)(color_min.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color_min.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color_min.z * 255);
        }
    }

    dis_img.render((*pImg));
    dis_img.paint();

    while (!dis_img.is_closed()) {
        dis_img.wait();
    }
}