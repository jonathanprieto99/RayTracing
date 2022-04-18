//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_MUNDO_H
#define RAYCASTINGV2_MUNDO_H

#include "Camara.h"
#include "Objeto.h"
#include "Luz.h"
#include <vector>
using namespace std;

class Mundo {
public:
    Camara cam;
    Luz luz;
    vector<Objeto*> vec_objetos;

    void Renderizar();
    void escenario1();
    void escenario2();
};


#endif //RAYCASTINGV2_MUNDO_H
