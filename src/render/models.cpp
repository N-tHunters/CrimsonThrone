#include <render/models.hpp>

std::unordered_map<std::string, Model*> models;

void load_models(std::vector<std::string> model_names) {
	for (auto model: models) {
		bool isLoaded = false;
		for (int j = 0; j < model_names.size(); j ++) {
			if (model_names[j] == model.first) {
				isLoaded = true;
				model_names.erase(model_names.begin() + j);
				break;
			}
		}
		if (!isLoaded) {
			models.erase(model.first);
		}
	}

	for (int i = 0; i < model_names.size(); i ++) {
		models.insert({model_names[i], new Model("resources/models/" + model_names[i] + ".obj")});
	}
}

Model* get_model(std::string model_name) {
	if (models.find(model_name) == models.end()) {
		printf("Model \"%s\" not found, loading...\n", model_name.c_str());
		models.insert({model_name, new Model("resources/models/" + model_name + ".obj")});
	}
	Model* model = models[model_name];
	return model;
}