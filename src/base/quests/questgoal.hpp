#ifndef QUESTGOAL_H_
#define QUESTGOAL_H_

#include <string>

class QuestGoal {
    public:
        std::string description;
        bool is_completed = false;

        QuestGoal(std::string description);
        void complete();
};

#endif // QUESTGOAL_H_
