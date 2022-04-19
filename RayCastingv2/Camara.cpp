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
            if (y == h/2 && x == w/2) {
                cout << "1";
            }
            rayo.dir = ze*(-f) + ye*a*(y/h -0.5) + xe*b*(x/w-0.5);
            rayo.dir.normalize();
            //color_min = vec3(1,1,1);
            bool interse = calcular_color(rayo, luz, vec_objetos, color, 0);

            (*pImg)(x,h-1-y,0) = (BYTE)(color.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color.z * 255);
        }
        dis_img.render((*pImg));
        dis_img.paint();
    }
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
            if ( t_calculado < t ) {
                hay_interseccion = true;
                t = t_calculado;
                N = normal;
                pObj = pObjTmp;
            }
        }
    }
    if (hay_interseccion) {
        vec3 luz_ambiente = luz.color * 0.3;
        color_min = pObj->color;
        // pi punto de interseccion
        vec3 pi = (rayo.ori + rayo.dir * t);
        // L vector hacia la luz
        vec3 L = luz.pos - pi;
        L.normalize();

        // calculando sombra
        Rayo rayo_sombra;
        rayo_sombra.dir = L;
        rayo_sombra.ori = pi + L * 0.1;
        vec3 color_tmp;
        bool interse = calcular_color(rayo_sombra, luz, vec_objetos, color_tmp, prof+1);
        if ( !interse ) {
            float factor_difuso = L.prod_punto(N);
            vec3 luz_difusa(0, 0, 0);
            if (factor_difuso > 0) {
                luz_difusa = luz.color * pObj->kd * factor_difuso;
            }
            // iluminacion especular
            vec3 r = N * N.prod_punto(L) * 2 - L;
            vec3 v = -rayo.dir;
            r.normalize();
            vec3 luz_especular(0,0,0);
            if (pObj->ke > 0) {
                float factor_especular = pow(r.prod_punto(v), pObj->n);
                if (factor_especular > 0) {
                    luz_especular = luz.color *  pObj->ke * factor_especular;
                }
            }
            color_min = color_min * (luz_ambiente + luz_difusa + luz_especular);
        } else {
            color_min = color_min * luz_ambiente;
        }
        // Rayos refractados
        vec3 color_refractado;
        float kr = pObj->kr;
        bool outside = rayo.dir.prod_punto(N) < 0;
        vec3 bias = 0.001 * N;
        if (pObj->ior > 0) {
            fresnel(rayo.dir, N, pObj->ior, kr);
            if ( kr < 1 ) {
                vec3 refDir = refract(rayo.dir, N, pObj->ior);
                refDir.normalize();
                vec3 refOri = outside ? pi - bias : pi + bias;
                Rayo rayo_refractado(refOri, refDir);
                calcular_color(rayo_refractado, luz, vec_objetos, color_refractado, prof+1);
            }
        }
        // Rayos reflejados
        vec3 color_reflejado;
        if (kr > 0) {
            Rayo rayo_ref;
            vec3 vec_rayo = -rayo.dir;

            vec3 R = N * (vec_rayo.prod_punto(N)) * 2 - vec_rayo;
            R.normalize();
            rayo_ref.dir = R;
            rayo_ref.ori = outside ? pi - bias : pi + bias;

            // lanzar rayo secundario
            bool interse = calcular_color(rayo_ref, luz, vec_objetos, color_reflejado, prof+1);
            // calcular intersecciones
            if (!interse) {
                color_reflejado = vec3(0);
                //color_min = color_min + color_reflejado*0.8;
            }
        }
        color_min = color_min + color_reflejado*kr + color_refractado*(1-kr);
        color_min.max_to_one();
        color = color_min;
        return true;
    }
    color = color_min;
    return false;
}

void Camara::fresnel(vec3 I, vec3 N, float ior, float &kr ) {
    float cosi = clamp(-1, 1, I.prod_punto(N));
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
}
vec3 Camara::refract(vec3 I, vec3 N, float ior) {
    float cosi = clamp(-1, 1, I.prod_punto(N));
    float etai = 1, etat = ior;
    vec3 n = N;
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n;
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