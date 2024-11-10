#ifndef INVENTORY_H
#define INVENTORY_H

#include "raylib.h"
#include "item.h"

#define INVENTORY_GRID_WIDTH 6
#define INVENTORY_GRID_HEIGHT 3

typedef struct
{
  Texture *panelTexture;
  Texture *slotTexture;
  bool isOpen;
} Inventory;

Inventory createInventory(Texture *panelTexture, Texture *slotTexture);

void handleInventoryInput(Inventory *inventory);

void drawInventory(Inventory *inventory, Item **items);

#endif // INVENTORY_H
