#include <stdio.h> 
#include <stdlib.h> 
#include <vector> // For vector class
#include <string.h>
#include <math.h> // For sqrt function
#include <glm/glm.hpp> // Linear algebra Library
#include "ray.h"
#include "light.h"
#include "color.h"
#include "sphere.h"
#include "scene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> // For matrix transformations
#include <glm/gtx/compatibility.hpp> // For clamp function
#include <chrono>

// P3 for PPM Output
void save_imageP3(std::ostream &file, glm::vec3 color) {
	
    int r = (int) (color.r * 255);
    int g = (int) (color.g * 255);
    int b = (int) (color.b * 255);
    
    file << r << " " << g << " " << b << "\n";
}

// HitRecord for tracking information on relevant intersections
struct HitRecord {
    float t;;
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    float ambient;
    float diffuse;
    float specular;
    float roughness;
    int specularExponent;
    bool inside = false;
    Sphere sphere;
    Ray ray;
};

// function for tracing ray checking for intersection for each sphere
HitRecord traceRay(Ray ray, Scene scene) {
    HitRecord hitRecord;
    hitRecord.t = 1000; // set t to a larger value as needed
    float nearPlaneZ = -scene.getNear(); // Near plane Z value
    //loop through all the spheres
    for (int i = 0; i < scene.getSpheres().size(); i++) {
        Sphere sphere = scene.getSpheres()[i];
        glm::vec3 center = sphere.getCenter();
        glm::vec3 scale = sphere.getScale();

        // calculate transformation of the sphere
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);
        glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);
        glm::mat4 transformation = translation * scaling;
        glm::mat4 inverseTransformation = glm::inverse(transformation);
        // transform the ray
        glm::vec4 origin(ray.getOrigin(), 1);
        glm::vec4 direction(ray.getDirection(), 0);
        origin = inverseTransformation * origin;
        direction = inverseTransformation * direction;
        glm::vec3 origin3(origin.x, origin.y, origin.z);
        glm::vec3 direction3(direction.x, direction.y, direction.z);
        Ray transformedRay(origin3, direction3);
        
        // calculate the discriminant
        float a = glm::dot(transformedRay.getDirection(), transformedRay.getDirection());
        float b = 2 * glm::dot(transformedRay.getDirection(), transformedRay.getOrigin());
        float c = glm::dot(transformedRay.getOrigin(), transformedRay.getOrigin()) - 1;
        float discriminant = (b * b) - (4 * a * c);
        if (discriminant < 0) {
            continue;
        }

        // get the sphere information
        glm::vec3 color = sphere.getColor();
        float ambient = sphere.getAmbient();
        float diffuse = sphere.getDiffuse();
        float specular = sphere.getSpecular();
        float roughness = sphere.getRoughness();
        int specularExponent = sphere.getSpecularExponent();
        // calculate the t values
        float t1 = (-b + sqrt(discriminant)) / (2 * a);
        float t2 = (-b - sqrt(discriminant)) / (2 * a);
        // Check if intersection points are in front of the near plane
        glm::vec3 intersectionPoint1 = transformedRay.getOrigin() + t1 * transformedRay.getDirection();
        glm::vec4 intersectionPoint1_4(intersectionPoint1, 1);
        glm::vec4 transformedIntersectionPoint1 = transformation * intersectionPoint1_4;
        intersectionPoint1 = glm::vec3(transformedIntersectionPoint1.x, transformedIntersectionPoint1.y, transformedIntersectionPoint1.z);

        glm::vec3 intersectionPoint2 = transformedRay.getOrigin() + t2 * transformedRay.getDirection();
        glm::vec4 intersectionPoint2_4(intersectionPoint2, 1);
        glm::vec4 transformedIntersectionPoint2 = transformation * intersectionPoint2_4;
        intersectionPoint2 = glm::vec3(transformedIntersectionPoint2.x, transformedIntersectionPoint2.y, transformedIntersectionPoint2.z);

        if (t1 < hitRecord.t && t1 > 0.00001 && intersectionPoint1.z < nearPlaneZ) {
            hitRecord.t = t1;
            glm::vec3 localPosition = transformedRay.getOrigin() + (t1 * transformedRay.getDirection());
            glm::vec4 position4(localPosition, 1);
            glm::vec4 transformedPosition = transformation * position4;
            hitRecord.position = glm::vec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
            glm::vec3 localNormal = glm::normalize(localPosition - glm::vec3(0, 0, 0));
            glm::vec3 worldNormal = glm::normalize(glm::vec3(glm::transpose(glm::inverse(transformation)) * glm::vec4(localNormal, 0)));

            
            // Use the world space normal and the original (world space) ray direction to set the inside flag
            if (glm::dot(worldNormal, ray.getDirection()) > 0) {
                hitRecord.inside = true; // We're inside if the world normal points in the same direction as the ray
            } else {
                hitRecord.inside = false; // We're outside if the world normal points against the ray direction
            }
            hitRecord.normal = worldNormal;
            hitRecord.color = color;
            hitRecord.ambient = ambient;
            hitRecord.diffuse = diffuse;
            hitRecord.specular = specular;
            hitRecord.roughness = roughness;
            hitRecord.specularExponent = specularExponent;
            hitRecord.sphere = sphere;
        }
        if (t2 < hitRecord.t && t2 > 0.00001 && intersectionPoint2.z < nearPlaneZ) {
            hitRecord.t = t2;
            glm::vec3 localPosition = transformedRay.getOrigin() + (t2 * transformedRay.getDirection());
            glm::vec4 position4(localPosition, 1);
            glm::vec4 transformedPosition = transformation * position4;
            hitRecord.position = glm::vec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
            glm::vec3 localNormal = glm::normalize(localPosition - glm::vec3(0, 0, 0));
            glm::vec3 worldNormal = glm::normalize(glm::vec3(glm::transpose(glm::inverse(transformation)) * glm::vec4(localNormal, 0)));

            
            // Use the world space normal and the original (world space) ray direction to set the inside flag
            if (glm::dot(worldNormal, ray.getDirection()) > 0) {
                hitRecord.inside = true; // We're inside if the world normal points in the same direction as the ray
            } else {
                hitRecord.inside = false; // We're outside if the world normal points against the ray direction
            }
            hitRecord.normal = worldNormal;
            hitRecord.color = color;
            hitRecord.ambient = ambient;
            hitRecord.diffuse = diffuse;
            hitRecord.specular = specular;
            hitRecord.roughness = roughness;
            hitRecord.specularExponent = specularExponent;
            hitRecord.sphere = sphere;
        }
        hitRecord.ray = ray;
    }
    return hitRecord;
}

// function to check if a shadow ray is blocked by a sphere 
bool shadowRay(Ray ray, Scene scene) {

    for (int i = 0; i < scene.getSpheres().size(); i++) {
        Sphere sphere = scene.getSpheres()[i];
        glm::vec3 center = sphere.getCenter();
        glm::vec3 scale = sphere.getScale();

        // calculate transformation of the sphere
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), center);
        glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);
        glm::mat4 transformation = translation * scaling;
        glm::mat4 inverseTransformation = glm::inverse(transformation);
        // transform the ray
        glm::vec4 origin(ray.getOrigin(), 1);
        glm::vec4 direction(ray.getDirection(), 0);
        origin = inverseTransformation * origin;
        direction = inverseTransformation * direction;
        
        glm::vec3 origin3(origin.x, origin.y, origin.z);
        glm::vec3 direction3(direction.x, direction.y, direction.z);
        Ray transformedRay(origin3, direction3);
        
        // calculate the discriminant
        float a = glm::dot(transformedRay.getDirection(), transformedRay.getDirection());
        float b = 2 * glm::dot(transformedRay.getDirection(), transformedRay.getOrigin());
        float c = glm::dot(transformedRay.getOrigin(), transformedRay.getOrigin()) - 1;
        float discriminant = (b * b) - (4 * a * c);
        if (discriminant < 0) {
            continue;
        }
        // calculate the t values
        float t1 = (-b + sqrt(discriminant)) / (2 * a);
        float t2 = (-b - sqrt(discriminant)) / (2 * a);
        // if the t values are greater than 0.001, then the shadow ray is blocked
        if (t1 > 0.001 || t2 > 0.001) {
            return true;
        }

    }
    return false;
}

glm::vec3 ads(HitRecord hitRecord, Scene scene, int depth) {
    glm::vec3 finalColor = hitRecord.ambient * scene.getAmbient().getColor() * hitRecord.color;

    for (int i = 0; i < scene.getLights().size(); i++) {
        Light light = scene.getLights()[i];
        glm::vec3 lightPosition = light.getPosition();
        glm::vec3 lightColor = light.getColor();        
        glm::vec3 lightVector = glm::normalize(lightPosition - hitRecord.position);
        glm::vec3 viewVector = glm::normalize(-hitRecord.position);
        glm::vec3 normal = hitRecord.normal;
        glm::vec3 reflectVector = glm::normalize(glm::reflect(-lightVector, normal)); 
        glm::vec3 sphereCenter = hitRecord.sphere.getCenter();
        glm::vec3 sphereScale = hitRecord.sphere.getScale();

        // Check if the light is inside the sphere
        // We skip the light if it is outside the sphere since it will be blocked by the sphere
        glm::vec3 transformedLightPos = lightPosition - sphereCenter;
        transformedLightPos.x /= sphereScale.x;
        transformedLightPos.y /= sphereScale.y;
        transformedLightPos.z /= sphereScale.z;

        // Check if the transformed light position is outside the unit sphere
        if (hitRecord.inside && glm::length(transformedLightPos) > 1.0f) {
            continue;  // Skip this light source as it is outside the ellipsoid
        }

        // Only check shadowRay if we're not inside the sphere
        if (!hitRecord.inside && shadowRay(Ray(hitRecord.position, lightVector), scene)) {
            continue;
        }

        float lightNormalAngle = std::max(glm::dot(lightVector, normal), 0.0f);
        if (hitRecord.inside) {
            lightNormalAngle = std::max(glm::dot(-lightVector, normal), 0.0f);
        }
        glm::vec3 diffuseColor = hitRecord.diffuse * hitRecord.color * lightColor * lightNormalAngle;

        float normalHalfAngle = std::max(glm::dot(viewVector, reflectVector), 0.0f);
        float specularStrength = std::pow(normalHalfAngle, static_cast<float>(hitRecord.specularExponent));
        glm::vec3 specularColor = specularStrength * hitRecord.specular * lightColor;

        // Add to final color
        finalColor += diffuseColor + specularColor;

        // Add reflection
        if (!hitRecord.inside && hitRecord.sphere.getRoughness() > 0 && depth < 3) {
            glm::vec3 rv = glm::normalize(glm::reflect(hitRecord.ray.getDirection(), normal));
            glm::vec3 offsetPosition = hitRecord.position + (0.0001f * hitRecord.normal);
            Ray refRay(offsetPosition, rv);
            HitRecord reflectHitRecord = traceRay(refRay, scene);
            if (!reflectHitRecord.inside && reflectHitRecord.t != 1000) {
                glm::vec3 reflectColor = ads(reflectHitRecord, scene, depth + 1);
                finalColor += hitRecord.roughness * reflectColor;
            }
        }
    }

    return finalColor;
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input scene file>" << std::endl;
        exit(1);
    }
    std::string filename = argv[1];
    Scene scene;
    // log the file name
    std::cout << "Reading file: " << filename << std::endl;
    scene.parseScene(filename);
    // scene.printScene();

    // SETUP VIEW PLANE
	int Width = scene.getResolutionX();
	int Height= scene.getResolutionY();
    float viewPlaneWidth = scene.getRight() - scene.getLeft();
    float viewPlaneHeight = scene.getTop() - scene.getBottom();
    float pixelWidth = viewPlaneWidth / Width;
    float pixelHeight = viewPlaneHeight / Height;

    glm::vec3 viewPlaneOrigin(scene.getLeft()+(pixelWidth/2), scene.getTop()-(pixelHeight/2), -scene.getNear()); // the origin of the view plane is at the bottom left corner
    glm::vec3 color(0, 0, 0);
    glm::vec3 eye(0, 0, 0);
    std::ofstream fname3(scene.getOutput());

    fname3 << "P3\n" << Width << " " << Height << "\n255\n";

	for(int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
            glm::vec3 currentPixel(viewPlaneOrigin.x + (j * pixelWidth), viewPlaneOrigin.y - (i * pixelHeight), viewPlaneOrigin.z);
            glm::vec3 direction = glm::normalize(currentPixel - eye);
            Ray ray(eye, direction);
            HitRecord intersection = traceRay(ray, scene);
            // std::clog << "\rscanning pixel " << i << " " << j << std::flush;

            // Change t value as needed for testing
            if (intersection.t >= 1000) {
                color = scene.getBackground().getColor();
            } else {
                color = ads(intersection, scene, 0);
                color = glm::clamp(color, 0.0f, 1.0f);
            }
            save_imageP3(fname3, color);
            
		}
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::clog << "\nRendering time: " << durationSeconds.count() << " seconds" << std::endl;
    std::clog << "Output file: " << scene.getOutput() << std::endl;
    std::clog << "Done!" << std::endl;
}

