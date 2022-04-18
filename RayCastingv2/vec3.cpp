//
// Created by hgallegos on 1/04/2022.
//

#include "vec3.h"

vec3 operator/(float f, vec3 &v) {
    if (v.x == 0 || v.y == 0 || v.z == 0) {
        std::cout << "Hay cero";
    }
    float tx = (v.x == 0) ? f/0.01 : f/v.x;
    float ty = (v.y == 0) ? f/0.01 : f/v.y;
    float tz = (v.z == 0) ? f/0.01: f/v.z;

    return vec3(tx, ty, tz);
}
vec3 operator*(float f, vec3 &v) {
    return vec3(f*v.x, f*v.y, f*v.z);
}

vec3 abs(vec3 &v) {
    return vec3( abs(v.x), abs(v.y), abs(v.z) );
}
vec3 sign(vec3 &v) {
    return vec3( sgn(v.x), sgn(v.y), abs(v.z) );
}
vec3 step(vec3 v1, vec3 v2) {
    return vec3(v2.x < v1.x ? 0 : 1,
                 v2.y < v1.y ? 0 : 1,
                 v2.z < v1.z ? 0 : 1);
}