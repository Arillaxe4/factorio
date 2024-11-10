#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "sprite.h"
#include "item.h"

#define LEVEL_TILE_WIDTH 12
#define LEVEL_TILE_HEIGHT 12

typedef enum
{
  TILE_FLOOR,
  TILE_WALL,
} TileType;

typedef enum
{
  TILE_FLOOR_VARIANT_CENTER,
  TILE_FLOOR_VARIANT_LEFT,
  TILE_FLOOR_VARIANT_RIGHT,
  TILE_FLOOR_VARIANT_TOP,
  TILE_FLOOR_VARIANT_BOTTOM,
  TILE_FLOOR_VARIANT_LEFT_TOP,
  TILE_FLOOR_VARIANT_LEFT_BOTTOM,
  TILE_FLOOR_VARIANT_RIGHT_TOP,
  TILE_FLOOR_VARIANT_RIGHT_BOTTOM,
} TileFloorVariant;

typedef union
{
  TileFloorVariant floor;
} TileVariant;

typedef struct
{
  Sprite sprite;
  TileType type;
  TileVariant variant;
  Vector2 position;
} Tile;

typedef struct
{
  Tile **tiles;
  Item **items;
  int itemsCount;
} Level;

Level createDefaultLevel(Texture *levelTexture);

void drawLevel(Level *level);

void addItemToLevel(Level *level, Item *item);

void updateLevel(Level *level);

#endif // LEVEL_H
