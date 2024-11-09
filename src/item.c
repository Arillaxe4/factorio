#include "item.h"
#include "swingable.h"
#include <string.h>

Item createItem(Sprite sprite, const char *name, ItemType type, float x, float y, ItemDetails details)
{
  Item item;

  item.sprite = sprite;
  strncpy(item.name, name, sizeof(item.name) - 1);
  item.name[sizeof(item.name) - 1] = '\0';
  item.type = type;
  item.x = x;
  item.y = y;
  item.details = details;

  return item;
}

void renderItem(Item *item)
{
  drawSprite(&item->sprite);
}

void updateItem(Item *item)
{
  if (item->type == ITEM_TYPE_SWINGABLE)
  {
    updateSwingable(&item->details.swingable);
    item->sprite.angle = item->details.swingable.animationAngle;
    item->sprite.dstRect.x = item->x;
    item->sprite.dstRect.y = item->y;
  }
}