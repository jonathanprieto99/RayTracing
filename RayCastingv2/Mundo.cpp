//
// Created by hgallegos on 1/04/2022.
//

#include "Mundo.h"
void Mundo::escenario2() {
    cam.init(60, 10, 600, 400,
             vec3(20, 40, 120),
             vec3(0, 0, 0),
             vec3(0, 1, 0));
    cam.calcular_vectores();

    luz.set(vec3(35, 35, 50), vec3(1, 1, 1));
    float pos = 20;
    for (int f = -5; f < 5; f++) {
        for (int c = -5; c < 5; c++) {
            Esfera *esf1 = new Esfera;
            esf1->cen = vec3(f*pos, 0, c*pos);
            esf1->rad = 7;
            esf1->color = vec3(1, 0, 0);
            esf1->kd = 0.8;
            esf1->ke = 0.9;
            esf1->kr = 0.8;
            //esf1->ior = 1.5;
            esf1->n = 8;
            vec_objetos.emplace_back(esf1);
        }
    }
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

void Mundo::escenario1() {
    cam.init(60,10, 600, 400,
             vec3(20,40, 80),
             vec3(0,0,0),
             vec3(0,1,0));
    cam.calcular_vectores();

    luz.set(vec3(35,35,50), vec3(1,1,1));
    Esfera *esf1 = new Esfera;
    esf1->cen = vec3(0,0,0);
    esf1->rad = 20;
    esf1->color = vec3(1,0,0);
    esf1->kd = 0.8;
    esf1->ke = 0.9;
    esf1->n = 4;
    vec_objetos.emplace_back(esf1);

    Plano *plano = new Plano;
    plano->n = vec3(1,10,1);
    plano->n.normalize();
    plano->d = 0;
    plano->color = vec3(0,1,0);
    plano->kd = 0.9;
    plano->ke = 0;
    vec_objetos.emplace_back(plano);

    Cilindro *cil1 = new Cilindro;
    cil1->color = vec3(0,1,1);
    cil1->pa = vec3(5,30,20);
    cil1->pb = vec3(-5,10,20);
    cil1->ra = 10;
    cil1->ke = 0;
    cil1->ior = 1.5;
    //vec_objetos.emplace_back(cil1);

    Esfera *esf4 = new Esfera;
    esf4->cen = vec3(5,20,20);
    esf4->rad = 2;
    esf4->color = vec3(1,1,1);
    esf4->kd = 0.9;
    esf4->ke = 0.9;
    //esf4->kr = 0.9;
    esf4->n = 16;
    vec_objetos.emplace_back(esf4);

    cam.Renderizar( luz, vec_objetos );
}