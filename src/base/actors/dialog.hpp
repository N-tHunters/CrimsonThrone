#ifndef DIALOG_H_
#define DIALOG_H_


#include <string>
#include <vector>
#include <map>
#include "../quests/quest.hpp"
#include "../actors/player.hpp"


class Dialog {
        private:
                std::vector<std::string> lines;
                std::vector<std::vector<std::pair<int, std::string>>> player_lines;
                std::map<int, Quest*> quests;
                int current_line_index;
                Player *talker;
        public:
                Dialog();
                std::string getLine();
                std::vector<std::pair<int, std::string>> getPlayerLines();
                void startDialog(Player *talker);
                void endDialog();
                void nextLine(int line);
                void setQuest(int line, Quest* quest);
                bool isQuest();
};


#endif // DIALOG_H_
