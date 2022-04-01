//
// Created by hgallegos on 1/04/2022.
//

#ifndef RAYCASTINGV2_VEC3_H
#define RAYCASTINGV2_VEC3_H

#include <iostream>

class vec3 {
public:
    float x, y, z;
    vec3(){}
    vec3(float _x, float _y, float _z) { x=_x; y=_y; z=_z; }
    float prod_punto(vec3 v) {
        return x*v.x + y*v.y + z*v.z;
    }
    vec3 prod_cruz(vec3 v) {
        return vec3(y*v.z - v.y*z, v.x*z - x*v.z, x*v.y - v.x*y);
    }
    vec3 operator*(float s) { return vec3(x*s, y*s, z*s); }
    vec3 operator*(vec3 v) { return vec3( x*v.x, y*v.y, z*v.z); }
    vec3 operator+(vec3 v) { return vec3( x+v.x, y+v.y, z+v.z); }
    vec3 operator-(vec3 v) { return vec3( x-v.x, y-v.y, z-v.z); }
    void normalize() {
        double m = modulo();
        x = x/m;
        y = y/m;
        z = z/m;
    }
    double modulo() {
        return sqrt(x*x + y*y + z*z);
    }
    void max_to_one() {
        float max_value = std::max(x, std::max(y,z));
        if (max_value > 1.0){
            x = x / max_value;
            y = y / max_value;
            z = z / max_value;
        }
    }
};


#endif //RAYCASTINGV2_VEC3_H
