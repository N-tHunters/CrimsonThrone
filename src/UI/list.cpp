#include "list.hpp"

List::List(glm::vec4 rect, std::vector<AbstractListElement*>* list, const std::string& texturePath, int maxCount, std::map<GLchar, Character> Characters, std::vector<std::string>* headers, std::vector<float> column_ratio): Frame(rect) {
	this->rect = rect;
	this->maxCount = maxCount;
	this->index = 0;
	this->columns = new std::vector<Column*>;

	int cell_height = rect.w / maxCount;

	int x = rect.x;

	for (size_t i = 0; i < headers->size(); i ++) {
		int cell_width = rect.z * column_ratio[i];
		this->columns->push_back(new Column(glm::vec4(x, rect.y, cell_width, rect.w),
			list,
			texturePath,
			maxCount,
			Characters,
			headers->at(i),
			cell_width,
			cell_height,
			i));
		x += cell_width;
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