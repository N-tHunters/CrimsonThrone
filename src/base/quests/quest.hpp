#ifndef QUEST_H_
#define QUEST_H_

#include <vector>
#include "questgoal.hpp"

class Quest {
    public:
        int goals_num;
        std::string name;
        std::vector<QuestGoal *> goals;

        Quest(std::string name, std::vector<QuestGoal *> goals);
};

#endif // QUEST_H_
