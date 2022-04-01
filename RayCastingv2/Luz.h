//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_LUZ_H
#define RAYCASTINGV2_LUZ_H

#include "vec3.h"
class Luz {
public:
    vec3 pos, color;
    Luz() {}
    Luz(vec3 _pos, vec3 _color) {
        pos = _pos;
        color = _color;
    }
};


#endif //RAYCASTINGV2_LUZ_H
