//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_RAYO_H
#define RAYCASTINGV2_RAYO_H

#include "vec3.h"

class Rayo {
public:
    vec3 ori, dir;

    Rayo(){}
    Rayo(vec3 _ori, vec3 _dir) {
        ori = _ori;
        dir = _dir;
    }
};


#endif //RAYCASTINGV2_RAYO_H
