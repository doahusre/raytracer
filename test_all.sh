#!/usr/bin/env bash

make

echo "*** Running tests ***"
echo "Testing Ambient"
./RayTracer tests-and-keys/testAmbient.txt
echo "****************"
echo "Testing Background"
./RayTracer tests-and-keys/testBackground.txt
echo "****************"
echo "Testing Behind"
./RayTracer tests-and-keys/testBehind.txt
echo "****************"
echo "Testing Diffuse"
./RayTracer tests-and-keys/testDiffuse.txt
echo "****************"
echo "Testing Illum"
./RayTracer tests-and-keys/testIllum.txt
echo "****************"
echo "Testing ImgPlane"
./RayTracer tests-and-keys/testImgPlane.txt
echo "****************"
echo "Testing Intersection"
./RayTracer tests-and-keys/testIntersection.txt
echo "****************"
echo "Testing Parsing"
./RayTracer tests-and-keys/testParsing.txt
echo "****************"
echo "Testing Reflection"
./RayTracer tests-and-keys/testReflection.txt
echo "****************"
echo "Testing Sample"
./RayTracer tests-and-keys/testSample.txt
echo "****************"
echo "Testing Shadow"
./RayTracer tests-and-keys/testShadow.txt
echo "****************"
echo "Testing Specular"
./RayTracer tests-and-keys/testSpecular.txt
echo "****************"

rm -rf results
mkdir results
mv *.ppm results/
