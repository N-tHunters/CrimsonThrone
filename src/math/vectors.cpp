#include "vectors.hpp"
#include "../debug.hpp"

glm::vec2 normalize(glm::vec2 vec) {
	float d = sqrt(vec.x * vec.x + vec.y * vec.y);
	vec.x /= d;
	vec.y /= d;
	return vec;
}

glm::vec3 normalize(glm::vec3 vec) {
	float d = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= d;
	vec.y /= d;
	vec.z /= d;
	return vec;
}

glm::vec3 get_normal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3) {
	
/*	glm::vec3 vec1 = point2 - point1;
	glm::vec3 vec2 = point3 - point1;
	printf("%s\n", "I will print points!");
	print_vector(point1);
	print_vector(point2);
	print_vector(point3);
	glm::vec3 result = normalize(glm::vec3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z));
	glm::vec3 u = point2 - point1;
	glm::vec3 v = point3 - point1;
	glm::vec3 result;
	result.x = (u.y * v.z) - (u.z * v.y);
	result.y = (u.z * v.x) - (u.x * v.z);
	result.z = (u.x * v.y) - (u.y * v.x);*/

	glm::vec3 a = point2 - point1;
	glm::vec3 b = point3 - point1;

	glm::vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	return normalize(result);
}