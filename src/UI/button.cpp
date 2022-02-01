#include <UI/button.hpp>
#include <base/configuration.hpp>


Button::Button(glm::vec2 size, glm::vec2 pos, func function, std::string text, float scale, glm::vec3 color, int orientation) {
	this->rect = new Rect(pos.x, pos.y, size.x, size.y);
	this->function = function;
	this->text = new Text(text, scale, color);
	glm::vec2 text_size = glm::vec2(this->text->getRect().z, this->text->getRect().w);

	glm::vec2 textPosition;

	if (orientation == 0) {
		glm::vec2 center = glm::vec2(rect->x, rect->y);

		textPosition = glm::vec2(center.x - this->text->getRect().z * 0.5f, center.y - this->text->getRect().w * 0.5f);
	} else if (orientation == 1) {
		textPosition = glm::vec2(rect->x + 20, rect->y + rect->h * 0.5f - this->text->getRect().w);
	}

	this->text->update(text, glm::vec4(textPosition,
	                   glm::vec2(this->text->getRect().z, this->text->getRect().w)));

	if (orientation == 0) {
		this->rect->setPosition(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f);
	}

	printf("%d %d\n", this->rect->x, this->rect->y);

	int width, height;

	width = (int)(rect->w);
	height = (int)(rect->h);

	int channels = 4;

	unsigned char* image = (unsigned char *)malloc(width * height * channels);

	for (int i = 0; i < height; i ++) {
		for (int j = 0; j < width; j ++) {
		  if (j < 10) {
				image[(i * width + j) * channels] = 255;
				image[(i * width + j) * channels + 1] = 255;
				image[(i * width + j) * channels + 2] = 255;
				image[(i * width + j) * channels + 3] = 100;
			} else if (j < 15 || i < 10 || i > height - 10) {
				image[(i * width + j) * channels] = 255;
				image[(i * width + j) * channels + 1] = 255;
				image[(i * width + j) * channels + 2] = 255;
				image[(i * width + j) * channels + 3] = 0;
			} else {
				image[(i * width + j) * channels] = 0;
				image[(i * width + j) * channels + 1] = 0;
				image[(i * width + j) * channels + 2] = 0;
				image[(i * width + j) * channels + 3] = 255 * (width - j) / width / 4;
			}
		}
	}

	GLuint texture = createTexture(std::vector<unsigned char>(image, image + width * height * channels), width, channels);
	this->rect->setTexture(texture);
}

Button::Button(int x, int y, int w, int h, func function, std::string text, float scale, glm::vec3 color, int orientation): Button(glm::vec2(w, h), glm::vec2(x, y), function, text, scale, color, orientation) {}

void Button::update(glm::vec3 color) {
}

void Button::draw() {
	glClear(GL_DEPTH_BUFFER_BIT);
	this->rect->draw();
	glClear(GL_DEPTH_BUFFER_BIT);
	this->text->draw();
}

bool Button::check(glm::vec2 position) {
	return rect->checkPoint(position);
}

void Button::click(glm::vec2 position) {
	if (check(position)) {
		function();
	}
}
