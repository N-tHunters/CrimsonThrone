#include "dialog.hpp"


Dialog::Dialog(Actor *me) {
    this->me = me;
    this->current_line_index = 0;

    this->lines = {
    "Hello, stanger!",
    "I have one big problem.",
    "Go fuck yourself",
    "Nope",
    "Crabs are different",
    "Bye"
};


    this->player_lines = {
    {
    {1, "You look sad. What happened?"},
    {-1, "Bye"},
},
    {
    {2, "You are an idiot"},
    {3, "Can you give me money?"},
    {4, "Who are you?"}
},
    {
    {0, "Sorry"}
},
    {
    {0, "Ok."}
},
    {
    {0, "I will help you"}
},
    {
    {-1, "Bye"}
}
};

    setQuest(4, new Quest("WHOAMI?", {
                new QuestGoal("get a sword")
            }));
    talker = nullptr;
}


std::string Dialog::getLine() {
    return this->lines[this->current_line_index];
}

std::vector<std::pair<int, std::string>> Dialog::getPlayerLines() {
    return this->player_lines[this->current_line_index];
}

void Dialog::startDialog(Player* talker) {
    this->current_line_index = 0;
    this->talker = talker;

    glm::vec3 position = this->me->GetPhysicalObj()->getPosition();

    glm::vec3 rel_vec = this->talker->GetPhysicalObj()->getPosition() - position;
    rel_vec.y = 0;
    float degree = atan(rel_vec.x / rel_vec.z) * 180 / 3.1415 + 90;
    glm::vec3 newRotation = this->me->GetPhysicalObj()->getRotation();
    newRotation.y = degree;
    this->me->GetPhysicalObj()->setRotation(newRotation);

}

void Dialog::nextLine(int line) {
    if(line == -1)
        return;
    this->current_line_index = line;
    if(isQuest()) {
        talker->addQuest(this->quests[current_line_index]);
    }
}


void Dialog::setQuest(int line, Quest* quest) {
    this->quests[line] = quest;
}

bool Dialog::isQuest() {
    return (this->quests[this->current_line_index] != nullptr);
}
