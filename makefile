# Makefile for RayTracer project

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11

# Target settings
TARGET := RayTracer
SOURCE := ppm.cpp

# Phony targets for non-file targets
.PHONY: all clean

# Main target
all: $(TARGET)

# Build the target
$(TARGET): $(SOURCE)
	@echo "Compiling $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean up
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
