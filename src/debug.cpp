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

void print_vector(std::vector<float> vec) {
	for (int i = 0; i < vec.size(); i ++) {
		printf("%f", vec[i]);
		if (i < vec.size() - 1) {
			printf(" ");
		}
	}
	printf("\n");
}

void print_vector(std::vector<std::vector<float>> vec) {
	for (int i = 0; i < vec.size(); i ++) {
		print_vector(vec[i]);
	}
}