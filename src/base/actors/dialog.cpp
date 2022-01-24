#include "dialog.hpp"


Dialog::Dialog() {
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
    {1, "Sorry"}
},
    {
    {1, "Ok."}
},
    {
    {1, "Ok."}
},
    {
    {-1, "Bye"}
}
};
}


std::string Dialog::getLine() {
    return this->lines[this->current_line_index];
}

std::vector<std::pair<int, std::string>> Dialog::getPlayerLines() {
    return this->player_lines[this->current_line_index];
}

void Dialog::startDialog() {
    this->current_line_index = 0;
}

void Dialog::nextLine(int line) {
    if(line == -1)
        return;
    this->current_line_index = line;
}
