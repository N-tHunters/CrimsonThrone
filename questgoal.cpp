#include "questgoal.h"


QuestGoal::QuestGoal(std::string description) {
    this->description = description;
}


void complete() {
    this->is_completed = true;
}
