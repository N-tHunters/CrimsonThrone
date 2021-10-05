#include <render/animatedModel.hpp>

AnimatedModel::AnimatedModel(GLuint model, GLuint texture, Joint* root_joint, int joint_count) {
	this->model = model;
	this->texture = texture;
	this->root_joint = root_joint;
	this->joint_count = joint_count;
	// this->animator = Animator(this)
	root_joint->calcInverseBindTransform(glm::mat4());
}