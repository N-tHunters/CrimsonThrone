#include <magic/abscore.h>
#include <magic/protocore.h>
#include <base/location/location.hpp>

AbstractCore::AbstractCore() {
  for(int i = 0; i < 256; i++)
    this->child_cores[i] = nullptr;
  this->physical_obj = nullptr;
}

AbstractCore::AbstractCore(PhysicalObj * obj) : AbstractCore() {
  this->physical_obj = obj;
}

char AbstractCore::FindEmptyChildCell() {
  for(int i = 0; i < 256; i ++)
    if(this->child_cores[i] == nullptr)
      return i;
  return -1;
}

char AbstractCore::AddChildProtoCore(ProtoMagicCore * new_child_core) {
  char index = this->FindEmptyChildCell();
  if(index == -1)
    return -1;
  this->child_cores[index] = new_child_core;
  new_child_core->SetParent(this);
  return index;
}

void AbstractCore::SetParent(AbstractCore * parent_core) {
  this->parent_core = parent_core;
}

void AbstractCore::SetPhysicalObj(PhysicalObj * obj) {
  this->physical_obj = obj;
}

PhysicalObj * AbstractCore::GetPhysicalObj() {
  return this->physical_obj;
}

AbstractCore * AbstractCore::GetChildCore(int index) {
  return this->child_cores[index];
}
