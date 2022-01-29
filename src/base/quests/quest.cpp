#include "quest.hpp"


Quest::Quest(std::string name, std::vector<QuestGoal *> goals) {
    this->name = name;
    this->goals = goals;
}
