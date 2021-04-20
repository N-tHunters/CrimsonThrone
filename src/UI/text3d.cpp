#include <UI/text3d.hpp>

Text3D::Text3D(const std::string& string, glm::vec3 position, std::map<GLchar, Character> characters, float scale) {
	m_string = string;
	m_position = position;
	m_rect = glm::vec4(0);

	float width = 0.0f;
	int height = 0;

	for (size_t c = 0; c < string.size(); c ++) {
		Character ch = characters[string[c]];

		width += ch.Bearing.x * scale + (ch.Advance >> 6) * scale;
		height = std::max(int(ch.Bearing.y / 2 * scale), height);
	}

	float x = - width / 2.0f;
	float y = - height / 2.0f;

	for (size_t c = 0; c < string.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = characters[string[c]];

		xpos = x + ch.Bearing.x * scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		// this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		Image3D* letter = new Image3D(glm::vec4(xpos, ypos, w, h), m_position, ch.TextureID);
		m_letters.push_back(letter);
		x += (ch.Advance >> 6) * scale;
	}
	this->m_rect.z = width;
	this->m_rect.w = height;
}

void Text3D::setString(const std::string& string) {
	m_string = string;
}

std::string Text3D::getString() {
	return m_string;
}

void Text3D::setPosition(glm::vec3 position) {
	m_position = position;
}

glm::vec3 Text3D::getPosition() {
	return m_position;
}

void Text3D::draw(ShaderHolder* shaders, Camera* camera, GLuint width, GLuint height) {
	for (int i = 0; i < m_letters.size(); i ++) {
		m_letters[i]->draw(shaders->getText3D(), camera, width, height);
	}
}