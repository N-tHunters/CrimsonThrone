#include "quest.hpp"


Quest::Quest(std::string name, std::string description, std::vector<QuestGoal *> goals) {
    this->name = name;
    this->goals = goals;
    this->description = description;
}
