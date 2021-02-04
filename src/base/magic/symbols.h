#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <map>
#include <string>

enum SYMBOL {
		    INCREASE_CURRENT_CELL,
		    DECREASE_CURRENT_CELL,
		    ZERO_CURRENT_CELL,

		    MOVE_NEXT_CELL,
		    MOVE_PREVIOUS_CELL,
		    MOVE_ZERO_CELL,
		    MOVE_LAST_CELL,

		    PUT_CELL_TO_STACK,
		    GET_CELL_FROM_STACK,

		    ADD_STACK,
		    SUB_STACK,
		    MUL_STACK,
		    DIV_STACK,

		    CYCLE_BEGIN,
		    CYCLE_END,

		    CHECK_EQUAL,
		    CHECK_LESS,
		    CHECK_GREATER,

		    JMP,
		    JMP_IF,

		    MARK,

		    TRAMPLINE,
		    HALT,

		    DUP,
		    DUP2,
		    SWAP,

		    INCREASE_STACK_TOP,
		    DECREASE_STACK_TOP,

		    SWITCH_STACK,

		    INTERRACT,
		    INTERRACT_CHILD
};

void init_translators();
std::string prog_to_pseudo(SYMBOL * prog, int len);
void pseudo_to_prog(std::string, SYMBOL *);
#endif
