#include <stdio.h>
#include <cassert>

#include "base/item.h"
#include "base/weapon.h"
#include "base/armor.h"
#include "base/helmet.h"
#include "base/gloves.h"
#include "base/boots.h"
#include "base/chestplate.h"
#include "base/leggins.h"
#include "base/actor.h"
#include "base/stackableitem.h"
#include "base/saver.h"
#include "base/loader.h"

int main() {
  printf("Test starting...\n");
  
  printf("Testing Item...\n");
  Item item;
  item.SetName("item");
  assert(item.GetName() == "item");

  printf("Testing Weapon...\n");
  Weapon weapon = Weapon("weapon", 10, 100);
  assert(weapon.GetName() == "weapon");
  assert(weapon.GetDamage() == 10);
  assert(weapon.GetRange() == 100);

  printf("Testing Armor...\n");
  Armor armor = Armor("armor", 50);
  assert(armor.GetName() == "armor");
  assert(armor.GetDefence() == 50);

  Helmet helmet = Helmet("helmet", 123);
  Gloves gloves = Gloves("gloves", 321);
  Boots boots = Boots("boots", 111);
  Chestplate chestplate = Chestplate("chestplate", 1000);
  Leggins leggins("leggins", 696);

  printf("Testing Actor...\n");
  Actor actor;
  actor.SetName("Test Actor");
  assert(actor.GetName() == "Test Actor");
  actor.SetHealth(10000);
  assert(actor.GetHealth() == 10000);
  actor.SetWeapon(&weapon);
  assert(actor.GetWeapon()->GetDamage() == weapon.GetDamage());
  actor.SetHelmet(&helmet);
  assert(actor.GetHelmet()->GetDefence() == helmet.GetDefence());
  actor.SetGloves(&gloves);
  assert(actor.GetGloves()->GetDefence() == gloves.GetDefence());
  actor.SetBoots(&boots);
  assert(actor.GetBoots()->GetDefence() == boots.GetDefence());
  actor.SetChestplate(&chestplate);
  assert(actor.GetChestplate()->GetDefence() == chestplate.GetDefence());
  actor.SetLeggins(&leggins);
  assert(actor.GetLeggins()->GetDefence() == leggins.GetDefence());
  assert(actor.GetDefence() == (helmet.GetDefence() + gloves.GetDefence() + boots.GetDefence() + chestplate.GetDefence() + leggins.GetDefence()));
  actor.SetMaxHealth(313);
  assert(actor.GetMaxHealth() == 313);
  actor.SetHealth(0);
  actor.Heal(10);
  assert(actor.GetHealth() == 10);
  actor.SetHealth(100);
  actor.DealDamage(10);
  assert(actor.GetHealth() == 90);

  printf("Testing health...\n");
  // Check that health cannot healed be over max_health
  actor.SetHealth(100);
  actor.SetMaxHealth(150);
  actor.Heal(150);
  assert(actor.GetHealth() == 150);

  printf("Testing inventory...\n");
  // Chesk inventory
  actor.SetItemAt(0, &weapon);
  assert(actor.GetItemAt(0) == &weapon);

  int empty_cell = actor.GetEmptyCell();
  assert(actor.GetItemAt(empty_cell) == nullptr);
  actor.PickupItem(&leggins);
  assert(actor.GetItemAt(empty_cell) == &leggins);

  // Test stacking
  printf("Testing stacking...\n");
  StackableItem sitem1;
  sitem1.SetName("sitem");
  sitem1.SetCount(100);
  actor.PickupItem((Item *)&sitem1);
  sitem1.Use(&actor);
  assert(sitem1.GetCount() == 99);
  
  int sitem_index = actor.GetItemIndex((Item *) &sitem1);
  assert(actor.GetItemAt(sitem_index) == &sitem1);


  sitem1.SetCount(1);
  sitem1.Use(&actor);

  sitem_index = actor.GetItemIndex((Item *) &sitem1);
  assert(sitem_index == -1);

  sitem1.SetCount(100);
  actor.PickupItem((Item *)&sitem1);

  StackableItem sitem2;
  sitem2.SetName("sitem");
  sitem2.SetCount(123);

  actor.PickupItem(&sitem2);
  assert(sitem1.GetCount() == 223);

  printf("Testing Saver...\n");
  // Test Saver and Loader

  // Prepare save data
  std::vector<Item*>items;
  std::vector<Actor*>actors;

  items.push_back(new Weapon("weapon 1", 100, 100));
  items.push_back(new Helmet("helmet", 1000));
  items.push_back(new Chestplate("chestplate", 100));
  items.push_back(new Gloves("gloves", 10));
  items.push_back(new Leggins("leggins", 50));
  items.push_back(new Boots("Tapoki", 221));

  Actor * actorp = new Actor();
  actorp->SetName("Lol");
  actorp->PickupItem(items[0]);
  actorp->PickupItem(items[1]);
  actorp->SetWeapon((Weapon *)items[0]);

  actors.push_back(actorp);

  // Save
  Saver saver("test.save", &actors, &items);
  saver.Save();

  items.clear();
  actors.clear();

  // Load
  Loader loader("test.save", &actors, &items);
  loader.Load();

  for(unsigned int i = 0; i < items.size(); i++) {
    if(items[i])
      printf("[Loaded %s]\n", items[i]->GetName().c_str());
    else
      printf("[Nothing loaded]\n");
  }
  
  printf("OK\n");
  return 0;
}
