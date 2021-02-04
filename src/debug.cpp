#include "debug.hpp"
#include <physics/boundary.hpp>

void print_vector(glm::vec2 vec) {
	printf("x: %f \t y: %f\n", vec.x, vec.y);
}

void print_vector(glm::vec3 vec) {
	printf("x: %f \t y: %f \t z: %f\n", vec.x, vec.y, vec.z);
}

void print_vector(glm::vec4 vec) {
	printf("x: %f \t y: %f \t z: %f \t w: %f\n", vec.x, vec.y, vec.z, vec.w);
}
