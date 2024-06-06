#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include "ray.h"
#include "light.h"
#include "color.h"

class Sphere {
public:
    Sphere() : center(glm::vec3(0)), scale(glm::vec3(1)), color(glm::vec3(1)), ambient(0.1f), diffuse(0.7f), specular(0.5f), roughness(0.5f), specularExponent(32) {}
    Sphere(glm::vec3 center, glm::vec3 scale, glm::vec3 color, float ambient, float diffuse, float specular, float roughness, int specularExponent)
        : center(center), scale(scale), color(color), ambient(ambient), diffuse(diffuse), specular(specular), roughness(roughness), specularExponent(specularExponent) {}
    ~Sphere() {}

    glm::vec3 getCenter() const {
        return center;
    }

    glm::vec3 getScale() const {
        return scale;
    }

    glm::vec3 getColor() const {
        return color;
    }

    float getAmbient() const {
        return ambient;
    }

    float getDiffuse() const {
        return diffuse;
    }

    float getSpecular() const {
        return specular;
    }

    float getRoughness() const {
        return roughness;
    }

    int getSpecularExponent() const {
        return specularExponent;
    }

    void setCenter(glm::vec3 center) {
        this->center = center;
    }

    void setScale(glm::vec3 scale) {
        this->scale = scale;
    }

    void setColor(glm::vec3 color) {
        this->color = color;
    }

    void setAmbient(float ambient) {
        this->ambient = ambient;
    }

    void setDiffuse(float diffuse) {
        this->diffuse = diffuse;
    }

    void setSpecular(float specular) {
        this->specular = specular;
    }

    void setRoughness(float roughness) {
        this->roughness = roughness;
    }

    void setSpecularExponent(int specularExponent) {
        this->specularExponent = specularExponent;
    }


private:
    glm::vec3 center;
    glm::vec3 scale;
    glm::vec3 color;
    float ambient;
    float diffuse;
    float specular;
    float roughness;
    int specularExponent;
};

#endif // SPHERE_H

