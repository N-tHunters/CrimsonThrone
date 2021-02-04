#include "list.hpp"

List::List(glm::vec4 rect, std::vector<AbstractListElement*>* list, std::string texturePath, int maxCount, std::map<GLchar, Character> Characters, std::vector<std::string>* headers): Frame(rect) {
	this->rect = rect;
	this->maxCount = maxCount;
	this->index = 0;
	this->columns = new std::vector<Column*>;

	for (size_t i = 0; i < headers->size(); i ++) {
		this->columns->push_back(new Column(glm::vec4(rect.x + rect.z / (float)headers->size() * i,
		                                    rect.y, rect.z / (float)headers->size(), rect.w), list, texturePath, 10, Characters, headers->at(i)));
	}

}

void List::update() {
	for (int i = 0; i < this->columns->size(); i ++) {
		this->columns->at(i)->update();
	}
}

void List::draw(ShaderHolder* shaderHolder) {

	for (size_t i = 0; i < this->columns->size(); i ++) {
		this->columns->at(i)->draw(shaderHolder);
	}

}