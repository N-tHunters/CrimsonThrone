#include "questgoal.hpp"


QuestGoal::QuestGoal(std::string description) {
    this->description = description;
}


void QuestGoal::complete() {
    this->is_completed = true;
}
