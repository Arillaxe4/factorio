#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include "sprite.h"
#include "swingable.h"

typedef enum
{
  ITEM_TYPE_SWINGABLE,
  ITEM_TYPE_FOOD,
} ItemType;

typedef union
{
  Swingable swingable;
} ItemDetails;

typedef struct
{
  Sprite sprite;
  char name[50];
  ItemType type;
  float x;
  float y;
  ItemDetails details;
} Item;

Item createItem(Sprite sprite, const char *name, ItemType type, float x, float y, ItemDetails details);

void renderItem(Item *item);

void updateItem(Item *item);

#endif // ITEM_H
