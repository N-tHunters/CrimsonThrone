#ifndef DIALOG_H_
#define DIALOG_H_


#include <string>
#include <vector>


class Dialog {
    private:
        std::vector<std::string> lines;
        std::vector<std::vector<std::pair<int, std::string>>> player_lines;
        int current_line_index;
    public:
        Dialog();
        std::string getLine();
        std::vector<std::pair<int, std::string>> getPlayerLines();
        void startDialog();
        void endDialog();
        void nextLine(int line);
};


#endif // DIALOG_H_
