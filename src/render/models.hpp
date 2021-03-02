#ifndef MODELS_H
#define MODELS_H

#include <unordered_map>
#include <vector>
#include <string>

#include <render/model.hpp>

std::unordered_map<std::string, Model*> models;

void load_models(std::vector<std::string> model_names);

#endif