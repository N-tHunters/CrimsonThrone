#include "core.h"

MagicCore::MagicCore() : AbstractCore() {
  this->state = STOPPED_OK;
  this->error = ERROR_OK;
  this->debug = true;
  this->flag = false;
}

int MagicCore::FindMark(int n) {
  int c = 0;
  for(int i = 0; i < 1024; i++) {
    if(this->cell_tape[i] == MARK) {
      c++;
      if(n == c)
	return i;
    }
  }
  return 0;
}

int MagicCore::GetCycleBegin(int ip) {
  int bal = 0;
  while(ip >= 0) {
    if(this->cell_tape[ip] == CYCLE_BEGIN) bal--;
    if(this->cell_tape[ip] == CYCLE_END) bal++;

    if(bal == 0) return ip;

    ip--;
  }
  return 0;
}

char MagicCore::GetCell(int index) {
  return this->cell_tape[index];
}

char MagicCore::PopStack() {
  if(this->core_stack[this->sp].empty())
    return 0;
  char top = this->core_stack[this->sp].top();
  this->core_stack[this->sp].pop();
  return top;
}

void MagicCore::PushStack(char val) {
  this->core_stack[this->sp].push(val);
}

void MagicCore::LoadProgram(SYMBOL * prog, int len) {
  for(int i = 0; i < len; i ++)
    this->cell_tape[i] = prog[i];
  this->ip = 0;
  this->cp = 0;
  this->sp = 0;
  this->state = RUNNING;
}

CORE_STATE MagicCore::GetState() {
  return this->state;
}

void MagicCore::Step() {
  if(this->state != RUNNING) return;

  if(this->debug) {
    printf("[ip:%4x cp:%4x] ", this->ip, this->cp);
    if(this->core_stack[this->sp].size())
      printf("%2x", this->core_stack[this->sp].top());
    puts("");
  }
  
  SYMBOL cmd = static_cast<SYMBOL>(this->cell_tape[this->ip]);
  char a, b, c;
  int i1, i2;

  switch(cmd) {
    
  case INCREASE_CURRENT_CELL:
    this->cell_tape[this->cp]++;
    break;

  case DECREASE_CURRENT_CELL:
    this->cell_tape[this->cp]--;
    break;

  case ZERO_CURRENT_CELL:
    this->cell_tape[this->cp] = 0;
    break;

  case MOVE_NEXT_CELL:
    this->cp++;
    break;

  case MOVE_PREVIOUS_CELL:
    this->cp--;
    break;

  case MOVE_ZERO_CELL:
    this->cp = 0;
    break;

  case PUT_CELL_TO_STACK:
    this->PushStack(this->cell_tape[this->cp]);
    break;

  case GET_CELL_FROM_STACK:
    this->cell_tape[this->cp] = this->PopStack();
    break;

  case ADD_STACK:
    a = this->PopStack();
    b = this->PopStack();
    this->PushStack(a + b);
    break;
    
  case SUB_STACK:
    a = this->PopStack();
    b = this->PopStack();
    this->PushStack(a - b);
    break;
    
  case MUL_STACK:
    a = this->PopStack();
    b = this->PopStack();
    this->PushStack(a * b);
    break;
    
  case DIV_STACK:
    a = this->PopStack();
    b = this->PopStack();
    if(b == 0) {
      this->state = STOPPED_ERROR;
      this->error = ERROR_DIV_ZERO;
      return;
    }
    this->PushStack(a / b);
    break;

  case CYCLE_END:
    this->ip = this->GetCycleBegin(ip);
    break;

  case CHECK_EQUAL:
    a = this->PopStack();
    b = this->PopStack();
    this->flag = a == b;
    break;
    
  case CHECK_LESS:
    a = this->PopStack();
    b = this->PopStack();
    this->flag = a < b;
    break;
    
  case CHECK_GREATER:
    a = this->PopStack();
    b = this->PopStack();
    this->flag = a > b;
    break;

  case JMP:
    a = this->PopStack();
    this->ip = this->FindMark(a) - 1;
    break;
    
  case JMP_IF:
    if(this->flag) {
      a = this->PopStack();
      this->ip = this->FindMark(a) - 1;
    }
    break;

  case TRAMPLINE:
    if(this->flag) {
      this->ip ++;
    }
    break;

  case HALT:
    this->state = STOPPED_OK;
    return;

  case MOVE_LAST_CELL:
    this->cp = 1023;
    break;

  case DUP:
    a = this->PopStack();
    this->PushStack(a);
    this->PushStack(a);
    break;

  case DUP2:
    a = this->PopStack();
    b = this->PopStack();
    this->PushStack(b);
    this->PushStack(a);
    this->PushStack(b);
    this->PushStack(a);
    break;

  case SWAP:
    a = this->PopStack();
    b = this->PopStack();
    this->PushStack(a);
    this->PushStack(b);
    break;

  case INCREASE_STACK_TOP:
    a = this->PopStack();
    this->PushStack(a + 1);
    break;

  case DECREASE_STACK_TOP:
    a = this->PopStack();
    this->PushStack(a - 1);
    break;
    
  case SWITCH_STACK:
    this->sp = !this->sp;
    break;

  case INTERRACT:
    a = this->PopStack();
    b = this->PopStack();
    c = this->PopStack();
    this->PushStack(proto_call(a, b, c, this));
    break;

  case INTERRACT_CHILD:
    a = this->PopStack();
    b = this->PopStack();
    c = this->PopStack();

    printf("Child call %d %d %d\n", a, b, c);

    ProtoMagicCore * child_core = (ProtoMagicCore*) this->GetChildCore(a);

    if(child_core == nullptr) {
      printf("error: Child core not exists\n");
      this->PushStack(-1);
    } else 
      this->PushStack(child_core->Call(b, c, this));
    break;
  }
  
  this->ip ++;

  JustifyStack();
}

void MagicCore::JustifyStack() {
  if(this->core_stack[this->sp].size() > 64)
    while(!this->core_stack[this->sp].empty())
      this->core_stack[this->sp].pop();
}
