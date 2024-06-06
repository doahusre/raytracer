#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>

class Color {
public:
    Color() : color(glm::vec3(0)) {}
    Color(glm::vec3 color) : color(color) {}
    ~Color() {}

    glm::vec3 getColor() const {
        return color;
    }

    void setColor(glm::vec3 color) {
        this->color = color;
    }

private:
    glm::vec3 color;
};

#endif // COLOR_H

