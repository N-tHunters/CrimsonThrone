#include <UI/inventory.hpp>
#include <physics/physicalObj.hpp>


Inventory::Inventory(Actor& actor):
  actor(actor) {

}

void Inventory::draw(ShaderHolder* shaderHolder) {
  if(actor.GetInventorySize() > 0) {
    PhysicalObj *po = actor.GetItemAt(0)->GetPhysicalObj();
    po->getMesh()->draw(shaderHolder);
  }
}

void Inventory::update() {

}
