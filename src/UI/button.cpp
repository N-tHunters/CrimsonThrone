#include <UI/button.hpp>
#include <base/configuration.hpp>


Button::Button(glm::vec2 size, glm::vec2 pos, func function, std::string text, float scale, glm::vec3 color) {
	this->rect = new Rect(pos.x, pos.y, size.x, size.y);
	this->function = function;
	this->text = new Text(text, scale, color);

	glm::vec2 center = glm::vec2(rect->x, rect->y);

	glm::vec2 text_size = glm::vec2(this->text->getRect().z, this->text->getRect().w);

	glm::vec2 textPosition = glm::vec2(center.x - this->text->getRect().z / 2.0f, center.y - this->text->getRect().w / 2.0f);

	this->text->update(text, glm::vec4(textPosition,
	                   glm::vec2(this->text->getRect().z, this->text->getRect().w)));

	// glGenTextures(1, &texture);
	// glBindTexture(GL_TEXTURE_2D, texture);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;

	width = (int)(rect->w);
	height = (int)(rect->h);

	unsigned char* image = (unsigned char *)malloc(width * height * 3);

	for (int i = 0; i < height; i ++) {
		for (int j = 0; j < width; j ++) {
		  if (i <= GetBorderWidth() || j <= GetBorderWidth() || i >= height - 1 - GetBorderWidth() || j >= width - 1 - GetBorderWidth()) {
				image[(i * width + j) * 3] = 255;
				image[(i * width + j) * 3 + 1] = 255;
				image[(i * width + j) * 3 + 2] = 255;
			} else {
				image[(i * width + j) * 3] = 0;
				image[(i * width + j) * 3 + 1] = 0;
				image[(i * width + j) * 3 + 2] = 0;
			}
		}
	}

	GLuint texture = createTexture(std::vector<unsigned char>(image, image + width * height * 3), width, 3);

	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// glGenerateMipmap(GL_TEXTURE_2D);
	// freeImage(image);
	// glBindTexture(GL_TEXTURE_2D, 0);
	this->rect->setTexture(texture);
}

Button::Button(int x, int y, int w, int h, func function, std::string text, float scale, glm::vec3 color): Button(glm::vec2(w, h), glm::vec2(x, y), function, text, scale, color) {}

void Button::update(glm::vec3 color) {
	// glGenTextures(1, &texture);
	// glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// // Set our texture parameters
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// // Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// // Load, create texture and generate mipmaps
	// int width, height;

	// width = (int)(rect->w);
	// height = (int)(rect->h);

	// unsigned char* image = (unsigned char *)malloc(width * height * 3 * sizeof(GL_FLOAT));
	// // image[0] = 0.0f;
	// // image[1] = 255.0f;
	// // image[2] = 0.0f;


	// for (int i = 0; i < height; i ++) {
	// 	for (int j = 0; j < width; j ++) {
	// 	  if (i <= GetBorderWidth() ||
	// 	      j <= GetBorderWidth() ||
	// 	      i >= height - 1 - GetBorderWidth() ||
	// 	      j >= width - 1 - GetBorderWidth())
	// 	    {
	// 			image[(i * width + j) * 3] = 255.0f;
	// 			image[(i * width + j) * 3 + 1] = 255.0f;
	// 			image[(i * width + j) * 3 + 2] = 255.0f;
	// 		} else {
	// 			image[(i * width + j) * 3] = color.x;	
	// 			image[(i * width + j) * 3 + 1] = color.y;
	// 			image[(i * width + j) * 3 + 2] = color.z;
	// 		}
	// 	}
	// }

	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// glGenerateMipmap(GL_TEXTURE_2D);
	// freeImage(image);
	// glBindTexture(GL_TEXTURE_2D, 0);

	// this->rect->setTexture(texture);
}

void Button::draw() {
	glClear(GL_DEPTH_BUFFER_BIT);

	this->rect->draw();
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
