#ifndef MAGIC_CORE_H
#define MAGIC_CORE_H

#include "symbols.h"
#include "abscore.h"
#include "protocore.h"

#include <stack>

enum CORE_STATE {
		 RUNNING,
		 STOPPED_OK,
		 STOPPED_ERROR,
		 DISABLED
};

enum CORE_ERROR {
		 ERROR_OK,
		 ERROR_NO_MANA,
		 ERROR_DIV_ZERO
};

class MagicCore : public AbstractCore{
  CORE_STATE state;
  CORE_ERROR error;
  std::stack<char> core_stack[2];
  char cell_tape[1024];
  int marks[256];
  int ip;
  int cp;
  int sp;
  bool debug;
  bool flag;

  char PopStack();
  void PushStack(char);
  int FindMark(int);
  int GetCycleBegin(int);
  void JustifyStack();
  
 public:
  MagicCore();
  void LoadProgram(SYMBOL * prog, int len);
  void Step();
  char GetCell(int);
  
  CORE_STATE GetState();
};

#endif
