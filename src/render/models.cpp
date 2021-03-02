#include <render/models.hpp>

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
		models[model_names[i]] = new Model("resources/models/" + model_names[i] + ".obj");
	}
}