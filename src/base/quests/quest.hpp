#ifndef QUEST_H_
#define QUEST_H_

#include <string>
#include <vector>

class QuestGoal;

class Quest {
    public:
        std::string name;
        std::string description;
        int goals_count;
        std::vector<QuestGoal*> goals;


        Quest(std::vector<QuestGoal *> goals);
};


#endif // QUEST_H_
