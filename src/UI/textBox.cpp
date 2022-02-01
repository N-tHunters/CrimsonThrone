#include <UI/textBox.hpp>


const int BORDER_WIDTH = 1;


TextBox::TextBox(glm::vec4 rect, float scale, glm::vec3 color) : Frame(rect) {
  this->rect = rect;
  // this->text = new Text(text, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), Characters, scale / 24.0f, color);

  this->rect.x = (rect.x + 1.0f) / 2.0f * screen_resolution.x;
  this->rect.y = (rect.y + 1.0f) / 2.0f * screen_resolution.y;
  this->rect.z = rect.z / 2.0f * screen_resolution.x;
  this->rect.w = rect.w / 2.0f * screen_resolution.y;

  rect = this->rect;

  vertices = {rect.x,     	 rect.y + rect.w, 0.0f, 0.0f, 1.0f,
    rect.x,     	 rect.y,     	  0.0f, 0.0f, 0.0f,
    rect.x + rect.z, rect.y + rect.w, 0.0f, 1.0f, 1.0f,
    rect.x + rect.z, rect.y,     	  0.0f, 1.0f, 0.0f
  };

  indices = {0, 1, 2,
    1, 2, 3
  };

  glm::vec2 center = glm::vec2(rect.x + rect.z / 2.0f, rect.y + rect.w / 2.0f);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
  // Set our texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // Load, create texture and generate mipmaps
  int width, height;

  width = (int)(rect.z);
  height = (int)(rect.w);

  unsigned char* image = (unsigned char *)malloc(width * height * 4 * sizeof(GL_FLOAT));

  for (int i = 0; i < height; i ++) {
    for (int j = 0; j < width; j ++) {
      if (i <= BORDER_WIDTH - 1 || j <= BORDER_WIDTH - 1 || i >= height - BORDER_WIDTH || j >= width - BORDER_WIDTH) {
	for (int k = 0; k < 4; k++) {
	  image[(i * width + j) * 4 + k] = 255.0f;
	}
      } else {
	for (int k = 0; k < 3; k++) {
	  image[(i * width + j) * 4 + k] = 0.0f;
	}
	image[(i * width + j) * 4 + 3] = 127.0f;
      }
    }
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  freeImage(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &(indices[0]), GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  m_scale = scale;

  this->max_lines = std::floor(this->rect.w / (m_scale + 10.0f));
  this->index = 0;

  m_position = glm::vec2(rect.x, rect.y);
}

void TextBox::draw() {
  glClear(GL_DEPTH_BUFFER_BIT);

  shaderGUI.Use();

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(shaderGUI.Program, "Texture"), 0);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  for (int i = index; i < this->lines.size(); i ++) {
    this->lines[i]->draw();
  }
}

void TextBox::addLine(const std::string& line) {
  Text* text = new Text(line, m_scale / 24.0f, glm::vec3(255, 255, 255), m_position);
  text->changePosition(glm::vec2(10.0f + text->getRect().z / 2.0f, this->rect.w - 10.0f - m_scale * 0.5f - (10.0f + m_scale) * this->lines.size()));

  this->lines.push_back(text);

  if (this->lines.size() > max_lines) {
    this->index += 1;
    for (int i = 0; i < this->lines.size(); i ++) {
      this->lines[i]->setPosition(m_position.x, m_position.y + index * (m_scale + 10.0f));
      this->lines[i]->changePosition(glm::vec2(10.0f + this->lines[i]->getRect().z / 2.0f, this->rect.w - 10.0f - m_scale * 0.5f - (10.0f + m_scale) * i));
    }
  }
}
