#include <render/models.hpp>

std::unordered_map<std::string, Model*> models;

void init_models() {
	models.clear();
}

void load_models(std::vector<std::string> model_names) {
	for (int i = 0; i < model_names.size(); i ++) {
		if (models.find(model_names[i]) == models.end()) {
			models[model_names[i]] = new Model("resources/models/" + model_names[i] + ".obj");
		}
	}
}

Model* get_model(std::string model_name) {
	if (models.find(model_name) == models.end()) {
		//("Model \"%s\" not found, loading...\n", model_name.c_str());
		models.insert({model_name, new Model("resources/models/" + model_name + ".obj")});
	}
	Model* model = models[model_name];
	return model;
}
