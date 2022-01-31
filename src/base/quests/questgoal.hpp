#ifndef QUESTGOAL_H_
#define QUESTGOAL_H_

#include <string>
#include <algorithm>
#include <base/actors/actor.hpp>

class QuestGoal {
    public:
        std::string description;
        bool is_completed = false;

        QuestGoal(std::string description);
        void complete();
        virtual std::pair<int, int> getProgress();
        virtual void check(Actor *);
};

#endif // QUESTGOAL_H_
