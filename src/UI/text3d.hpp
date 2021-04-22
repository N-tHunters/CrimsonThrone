#pragma once

// #include <UI/image.hpp>
#include <render/mesh.hpp>

#include <UI/character.hpp>
#include <UI/image3d.hpp>

#include <map>

class Text3D {
	std::string m_string;
	glm::vec3 m_position;
	glm::vec4 m_rect;
	std::vector<Image3D*> m_letters;

public:
	Text3D(const std::string& string, glm::vec3 position, std::map<GLchar, Character> characters, float scale);

	void setString(const std::string& string);
	std::string getString();

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

	void draw(ShaderHolder* shaders, Camera* camera, GLuint width, GLuint height);
};