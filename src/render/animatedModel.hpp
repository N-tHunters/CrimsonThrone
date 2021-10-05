#pragma once

#include <render/joint.hpp>
#include <render/Animator.hpp>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

class AnimatedModel {
public:
	GLuint model;
	GLuint texture;

	Joint* root_joint;
	int joint_count;

	// Animator animator;

	AnimatedModel(GLuint model, GLuint texture, Joint* root_joint, int joint_count);
};