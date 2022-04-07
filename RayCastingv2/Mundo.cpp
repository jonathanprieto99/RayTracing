//
// Created by hgallegos on 1/04/2022.
//

#include "Mundo.h"
void Mundo::escenario1() {
    cam.init(60,10, 600, 400,
             vec3(20,40, 80),
             vec3(0,0,0),
             vec3(0,1,0));
    cam.calcular_vectores();

    luz.set(vec3(35,35,30), vec3(1,1,1));
    Esfera *esf1 = new Esfera;
    esf1->cen = vec3(0,0,0);
    esf1->rad = 20;
    esf1->color = vec3(1,0,0);
    esf1->kd = 0.8;
    esf1->ke = 0.9;
    vec_objetos.emplace_back(esf1);

    Esfera *esf2 = new Esfera;
    esf2->cen = vec3(30,30,0);
    esf2->rad = 15;
    esf2->color = vec3(1,1,0);
    esf2->kd = 0.8;
    esf2->ke = 0.4;
    vec_objetos.emplace_back(esf2);

    Plano *plano = new Plano;
    plano->n = vec3(1,10,1);
    plano->n.normalize();
    plano->d = 0;
    plano->color = vec3(0,1,0);
    plano->kd = 0.9;
    plano->ke = 0;
    vec_objetos.emplace_back(plano);

    cam.Renderizar( luz, vec_objetos );
}