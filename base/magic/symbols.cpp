#include "symbols.h"

std::map<SYMBOL, char> sym2pseudo;
std::map<char, SYMBOL> pseudo2sym;

void init_translators() {
  sym2pseudo[INCREASE_CURRENT_CELL] = 'i';
  sym2pseudo[DECREASE_CURRENT_CELL] = 'd';
  sym2pseudo[ZERO_CURRENT_CELL] = '0';
  sym2pseudo[MOVE_NEXT_CELL] = 'n';
  sym2pseudo[MOVE_PREVIOUS_CELL] = 'p';
  sym2pseudo[MOVE_ZERO_CELL] = '@';
  sym2pseudo[PUT_CELL_TO_STACK] = '^';
  sym2pseudo[GET_CELL_FROM_STACK] = 'v';
  sym2pseudo[ADD_STACK] = '+';
  sym2pseudo[SUB_STACK] = '-';
  sym2pseudo[MUL_STACK] = '*';
  sym2pseudo[DIV_STACK] = '/';
  sym2pseudo[CYCLE_BEGIN] = '{';
  sym2pseudo[CYCLE_END] = '}';
  sym2pseudo[CHECK_EQUAL] = '=';
  sym2pseudo[CHECK_LESS] = '<';
  sym2pseudo[CHECK_GREATER] = '>';
  sym2pseudo[JMP] = 'j';
  sym2pseudo[JMP_IF] = '?';
  sym2pseudo[MARK] = '!';
  sym2pseudo[TRAMPLINE] = '#';
  sym2pseudo[HALT] = '%';
  sym2pseudo[MOVE_LAST_CELL] = '~';
  sym2pseudo[DUP] = 'u';
  sym2pseudo[DUP2] = 'U';
  sym2pseudo[SWAP] = 's';
  sym2pseudo[INCREASE_STACK_TOP] = 'I';
  sym2pseudo[DECREASE_STACK_TOP] = 'D';
  sym2pseudo[SWITCH_STACK] = '_';
  sym2pseudo[INTERRACT] = ';';

  for(auto &x: sym2pseudo) {
    pseudo2sym[x.second] = x.first;
  }
}

std::string prog_to_pseudo(SYMBOL * prog, int len) {
  std::string res = "";
  for(int i = 0; i < len; i++) {
    res += sym2pseudo[prog[i]];
  }

  return res;
}

void pseudo_to_prog(std::string pseudo, SYMBOL * prog) {
  for(int i = 0; i < pseudo.size(); i++) {
    prog[i] = pseudo2sym[pseudo[i]];
  }
}
