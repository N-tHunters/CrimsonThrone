#include "protocore.h"
#include "worldcore.h"
#include "firecore.h"
#include "voidcore.h"

std::map<char, ProtoMagicCore *> protocores;

ProtoMagicCore::ProtoMagicCore() : AbstractCore() {}
ProtoMagicCore::ProtoMagicCore(PhysicalObj * obj) : AbstractCore(obj) {}

char ProtoMagicCore::Call(char id, char arg, AbstractCore *core) {
  return 0;
}

char proto_call(char proto_id, char call_id, char arg, AbstractCore *core) {
  ProtoMagicCore * protocore = protocores[proto_id];
  if(protocore == nullptr) {
    return 0;
  }
  return protocore->Call(call_id, arg, core);
}


void init_protocores() {
  protocores[CORE_ID_WORLD] = new WorldMagicCore();
  protocores[CORE_ID_FIRE] = new FireMagicCore();
  protocores[CORE_ID_VOID] = new VoidMagicCore();
}

