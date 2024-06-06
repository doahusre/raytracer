#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "ray.h"
#include "light.h"
#include "color.h"
#include "sphere.h"

class Scene {
public:
    Scene() : near(0), left(0), right(0), bottom(0), top(0), resolutionX(0), resolutionY(0), output("") {}
    Scene(std::string filename) : Scene() {
        parseScene(filename);
    }
    ~Scene() {}

    void parseScene(std::string filename) {
        std::ifstream sceneFile(filename.c_str());
        std::string line;
        while (std::getline(sceneFile, line)) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;

            if (token == "NEAR") {
                iss >> near;
            } else if (token == "LEFT") {
                iss >> left;
            } else if (token == "RIGHT") {
                iss >> right;
            } else if (token == "BOTTOM") {
                iss >> bottom;
            } else if (token == "TOP") {
                iss >> top;
            } else if (token == "RES") {
                iss >> resolutionX >> resolutionY;
            } else if (token == "SPHERE") {
                std::string sphereId;
                glm::vec3 position, scale, color;
                float ka, kd, ks, kr, n;
                iss >> sphereId; // Read and discard the sphere ID
                iss >> position.x >> position.y >> position.z >> scale.x >> scale.y >> scale.z >> color.x >> color.y >> color.z >> ka >> kd >> ks >> kr >> n;
                Sphere sphere(position, scale, color, ka, kd, ks, kr, n);
                spheres.push_back(sphere);
            } else if (token == "LIGHT") {
            std::string lightId;
            glm::vec3 position, color;
            iss >> lightId; // Read and discard the light ID
            iss >> position.x >> position.y >> position.z >> color.x >> color.y >> color.z;
            Light light(position, color);
            lights.push_back(light);
            } else if (token == "BACK") {
                glm::vec3 color;
                iss >> color.x >> color.y >> color.z;
                background.setColor(color);
            } else if (token == "AMBIENT") {
                glm::vec3 color;
                iss >> color.x >> color.y >> color.z;
                ambient.setColor(color);
            } else if (token == "OUTPUT") {
                iss >> output;
            } else {
                // std::cout << "Unsupported Scene Data: " << token << std::endl;
            }
        }
    }

    void printScene() {
        std::cout << "NEAR: " << near << std::endl;
        std::cout << "LEFT: " << left << std::endl;
        std::cout << "RIGHT: " << right << std::endl;
        std::cout << "BOTTOM: " << bottom << std::endl;
        std::cout << "TOP: " << top << std::endl;
        std::cout << "RES: " << resolutionX << " " << resolutionY << std::endl;
        for (size_t i = 0; i < spheres.size(); i++) {
            std::cout << "SPHERE: " << spheres[i].getCenter().x << " " << spheres[i].getCenter().y << " " << spheres[i].getCenter().z << " "
                      << spheres[i].getScale().x << " " << spheres[i].getScale().y << " " << spheres[i].getScale().z << " "
                      << spheres[i].getColor().x << " " << spheres[i].getColor().y << " " << spheres[i].getColor().z << " "
                      << spheres[i].getAmbient() << " " << spheres[i].getDiffuse() << " " << spheres[i].getSpecular() << " "
                      << spheres[i].getRoughness() << " " << spheres[i].getSpecularExponent() << std::endl;
        }
        for (size_t i = 0; i < lights.size(); i++) {
            std::cout << "LIGHT: " << lights[i].getPosition().x << " " << lights[i].getPosition().y << " " << lights[i].getPosition().z << " "
                      << lights[i].getColor().x << " " << lights[i].getColor().y << " " << lights[i].getColor().z << std::endl;
        }
        std::cout << "BACK: " << background.getColor().x << " " << background.getColor().y << " " << background.getColor().z << std::endl;
        std::cout << "AMBIENT: " << ambient.getColor().x << " " << ambient.getColor().y << " " << ambient.getColor().z << std::endl;
        std::cout << "OUTPUT: " << output << std::endl;
    }

    void setSpheres(const std::vector<Sphere>& spheres) {
        this->spheres = spheres;
    }

    void setLights(const std::vector<Light>& lights) {
        this->lights = lights;
    }

    void setBackground(const Color& background) {
        this->background = background;
    }

    void setAmbient(const Color& ambient) {
        this->ambient = ambient;
    }

    void setResolution(int x, int y) {
        resolutionX = x;
        resolutionY = y;
    }

    void setNear(float near) {
        this->near = near;
    }

    void setLeft(float left) {
        this->left = left;
    }

    void setRight(float right) {
        this->right = right;
    }

    void setBottom(float bottom) {
        this->bottom = bottom;
    }

    void setTop(float top) {
        this->top = top;
    }

    void setOutput(const std::string& output) {
        this->output = output;
    }

    std::vector<Sphere> getSpheres() const {
        return spheres;
    }

    Sphere getSphere(int index) const {
        return spheres[index];
    }

    std::vector<Light> getLights() const {
        return lights;
    }

    Light getLight(int index) const {
        return lights[index];
    }

    Color getBackground() const {
        return background;
    }

    Color getAmbient() const {
        return ambient;
    }

    int getResolutionX() const {
        return resolutionX;
    }

    int getResolutionY() const {
        return resolutionY;
    }

    float getNear() const {
        return near;
    }

    float getLeft() const {
        return left;
    }

    float getRight() const {
        return right;
    }

    float getBottom() const {
        return bottom;
    }

    float getTop() const {
        return top;
    }

    std::string getOutput() const {
        return output;
    }

private:
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
    Color background;
    Color ambient;
    int resolutionX;
    int resolutionY;
    float near;
    float left;
    float right;
    float bottom;
    float top;
    std::string output;
};

#endif // SCENE_H

