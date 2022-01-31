#include "questgoal.hpp"


QuestGoal::QuestGoal(std::string description) {
    this->description = description;
}


void QuestGoal::complete() {
    this->is_completed = true;
}

std::pair<int, int> QuestGoal::getProgress() {
    return std::make_pair(this->is_completed, 1);
}

void QuestGoal::check(Actor *) {

}
