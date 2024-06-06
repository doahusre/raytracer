#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    Light() : position(glm::vec3(0)), color(glm::vec3(1)) {}
    Light(glm::vec3 position, glm::vec3 color) : position(position), color(color) {}
    ~Light() {}

    glm::vec3 getPosition() const {
        return position;
    }

    glm::vec3 getColor() const {
        return color;
    }

    void setPosition(glm::vec3 position) {
        this->position = position;
    }

    void setColor(glm::vec3 color) {
        this->color = color;
    }

private:
    glm::vec3 position;
    glm::vec3 color;
};

#endif // LIGHT_H

