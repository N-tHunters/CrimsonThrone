#include "text.hpp"



std::map<GLchar, Character> font_characters;


Text::Text(std::string text,
		   float scale,
		   glm::vec3 color,
		   glm::vec2 position
		): Frame(glm::vec4(0.0f)) {
	m_text = text;
	this->scale = scale;
	this->color = color;
	this->letters = new std::vector<Image*>;
	m_position = position;

	float width = 0.0f;
	int height = 0;

	for (size_t c = 0; c < text.size(); c ++) {
		Character ch = font_characters[text[c]];

		width += ch.Bearing.x * scale + (ch.Advance >> 6) * scale;
		height = std::max(int(ch.Bearing.y / 2 * scale), height);
	}

	float x = - width / 2.0f;
	float y = - height / 2.0f;

	this->rect.x = m_position.x + x;
	this->rect.y = m_position.y + y;

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = font_characters[text[c]];

		xpos = x + ch.Bearing.x * scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		x += (ch.Advance >> 6) * scale;
	}
	this->rect.z = width;
	this->rect.w = height;
}

Text::Text(std::string text,
		   float scale,
		   glm::vec3 color,
		   glm::vec2 position,
		   float start): Frame(glm::vec4(0.0f)) {
	m_text = text;
	this->scale = scale;
	this->color = color;
	this->letters = new std::vector<Image*>;
	m_position = position;

	float width = 0.0f;
	int height = 0;

	for (size_t c = 0; c < text.size(); c ++) {
		Character ch = font_characters[text[c]];

		width += ch.Bearing.x * scale + (ch.Advance >> 6) * scale;
		height = std::max(int(ch.Bearing.y / 2 * scale), height);
	}

	float x = 0.0f + start;
	float y = - height / 2.0f;

	this->rect.x = m_position.x + x;
	this->rect.y = m_position.y + y;

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = font_characters[text[c]];

		xpos = x + ch.Bearing.x * scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		x += (ch.Advance >> 6) * scale;
	}
	this->rect.z = width;
	this->rect.w = height;
}


Text::Text(std::string text,
		   float scale,
		   glm::vec3 color) : Text(text, scale, color, glm::vec2(0.0f)) {}

void Text::update(std::string text, glm::vec4 rect) {
	m_text = text;
	this->rect = rect;

	float x = this->rect.x;
	float y = this->rect.y;

	this->letters->clear();

	float width, height;
	width = 0.0f;
	height = 0.0f;

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = font_characters[m_text[c]];

		xpos = x + ch.Bearing.x * this->scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * this->scale;

		width += ch.Bearing.x * this->scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * this->scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		x += (ch.Advance >> 6) * scale;
	}

	this->rect.z = width;
	this->rect.w = height;
}

void Text::update(std::string text) {
	m_text = text;

	float x = this->rect.x;
	float y = this->rect.y;

	this->letters->clear();

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = font_characters[text[c]];

		xpos = x + ch.Bearing.x * this->scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * this->scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		x += (ch.Advance >> 6) * scale;
	}
}

void Text::draw() {
	for (size_t i = 0; i < this->letters->size(); i ++)
		this->letters->at(i)->draw(this->color);
}

glm::vec4 Text::getRect() {
	return this->rect;
}

void Text::setPosition(float x, float y) {
	for (int i = 0; i < this->letters->size(); i ++) {
		this->letters->at(i)->setPosition(x, y);
	}

	m_position = glm::vec2(x, y);
}

void Text::changePosition(glm::vec2 delta) {
	this->m_position += delta;

	for (int i = 0; i < this->letters->size(); i ++) {
		this->letters->at(i)->setPosition(m_position.x, m_position.y);
	}
}

glm::vec2 Text::getPosition() {
	return m_position;
}

std::string Text::getText() {
	return m_text;
}

void Text::setColor(glm::vec3 _color) {
  color = _color;
}


void load_characters() {
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    printf("ERROR::FREETYPE: Could not init FreeType Library\n");
  FT_Face face;
  if (FT_New_Face(ft, "resources/fonts/Ubuntu-Medium.ttf", 0, &face))
    printf("ERROR::FREETYPE: Failed to load font\n");


  FT_Set_Pixel_Sizes(face, 0, 128);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (GLubyte c = 0; c < 128; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      printf("ERROR::FREETYTPE: Failed to load Glyph\n");
      continue;
    }
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character = {
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      (GLuint)face->glyph->advance.x
    };
	font_characters.insert(std::pair<GLchar, Character>(c, character));
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}
