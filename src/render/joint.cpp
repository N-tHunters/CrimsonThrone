#include <render/joint.hpp>

Joint::Joint(int index, std::string name, glm::mat4 local_bind_transform) {
	this->index = index;
	this->name = name;
	this->local_bind_transform = local_bind_transform;
}

void Joint::addChild(Joint* joint) {
	this->children.push_back(joint);
}

void Joint::calcInverseBindTransform(glm::mat4 parent_bind_transform) {
	glm::mat4 bind_transform = parent_bind_transform * local_bind_transform;
	this->inverse_bind_transform = glm::inverse(bind_transform);

	for (int i = 0; i < this->children.size(); i ++) {
		this->childer[i]->calcInverseBindTransform(bind_transform);
	}
}