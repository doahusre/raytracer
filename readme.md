# Ray Tracing Renderer
### Author: Dhowa Husrevoglu

## Introduction
This project is a ray tracing renderer implemented in C++. It utilizes the vector and matrix library GLM, along with standard C++ libraries like vector and string.

## Features
- **Ray Tracing:** The renderer is capable of ray tracing, supporting scaled spheres with comprehensive illumination, reflection, and shadows.
- **Advanced Lighting:** It can simulate lights positioned inside spheres and can also handle sphere truncation by the near plane.
- **Output Format:** The renderer outputs images in P3 format, which is readable and widely supported.

## Main Components
The core parts of the code are located in `ppm.cpp`, and include several key functions:
- `traceRay`: This function tests for intersections in the ray tracing process.
- `shadowRay`: Similar to `traceRay`, but returns a boolean to determine the `inShadow` status.
- `ads`: A function to calculate ambient, diffuse, and specular (ADS) lighting for each light source, including reflections.

## Usage
After compiling the RayTracer project using the provided Makefile, you can run the program with the following command: ./RayTracer /path/to/your/testfile.txt

If Possible, simply run the bash script: ./test_all.sh

And all result will be stored in results/
