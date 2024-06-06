#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray {
public:
    Ray() : origin(glm::vec3(0)), direction(glm::vec3(0, 0, 1)) {}
    Ray(glm::vec3 origin, glm::vec3 direction) : origin(origin), direction(direction) {}
    ~Ray() {}

    glm::vec3 getOrigin() const {
        return origin;
    }

    glm::vec3 getDirection() const {
        return direction;
    }

    void setOrigin(glm::vec3 origin) {
        this->origin = origin;
    }

    void setDirection(glm::vec3 direction) {
        this->direction = direction;
    }

private:
    glm::vec3 origin;
    glm::vec3 direction;
};

#endif // RAY_H

