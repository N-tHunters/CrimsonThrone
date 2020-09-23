class Terrain {
	int size;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::vector<float>> height;
public:
	Terrain(int);
}