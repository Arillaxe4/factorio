#include "inventory.h"

Inventory createInventory(Texture *panelTexture, Texture *slotTexture)
{
  Inventory inventory;

  inventory.panelTexture = panelTexture;
  inventory.slotTexture = slotTexture;
  inventory.isOpen = false;

  return inventory;
}

void handleInventoryInput(Inventory *inventory)
{
  if (IsKeyPressed(KEY_E))
  {
    inventory->isOpen = !inventory->isOpen;
  }
}

void drawInventory(Inventory *inventory, Item **items)
{
  if (!inventory->isOpen)
    return;

  DrawTexturePro(
      *inventory->panelTexture,
      (Rectangle){0, 0, inventory->panelTexture->width, inventory->panelTexture->height},
      (Rectangle){400, 225, inventory->panelTexture->width, inventory->panelTexture->height},
      (Vector2){inventory->panelTexture->width / 2, inventory->panelTexture->height / 2},
      0,
      WHITE);

  for (int i = 0; i < INVENTORY_GRID_WIDTH; i++)
  {
    for (int j = 0; j < INVENTORY_GRID_HEIGHT; j++)
    {
      DrawTexturePro(
          *inventory->slotTexture,
          (Rectangle){0, 0, inventory->slotTexture->width, inventory->slotTexture->height},
          (Rectangle){400 - inventory->panelTexture->width / 2 + inventory->slotTexture->width * i + 15 + 2 * i, 222 - inventory->panelTexture->height / 2 + inventory->slotTexture->height * j + 13 + 2 * j, inventory->slotTexture->width, inventory->slotTexture->height},
          (Vector2){0, 0},
          0,
          WHITE);
    }
  }

  // TODO: render items in inventory
}
