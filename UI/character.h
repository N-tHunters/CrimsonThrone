struct Character {
	GLuint     TextureID; // ID текстуры глифа
	glm::ivec2 Size;      // Размеры глифа
	glm::ivec2 Bearing;   // Смещение верхней левой точки глифа
	GLuint     Advance;   // Горизонтальное смещение до начала следующего глифа
};