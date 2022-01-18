#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include <render/model.hpp>

void init_models();
void load_models(std::vector<std::string> model_names);
Model* get_model(std::string model_name);
