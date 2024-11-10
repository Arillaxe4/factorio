#include "level.h"
#include "stdlib.h"

Level createDefaultLevel(Texture *levelTexture)
{
  Level level;

  level.tiles = malloc(LEVEL_TILE_WIDTH * sizeof(Tile *));
  level.items = malloc(20 * sizeof(Item *));
  level.itemsCount = 0;

  for (int i = 0; i < LEVEL_TILE_WIDTH; i++)
  {
    level.tiles[i] = malloc(LEVEL_TILE_HEIGHT * sizeof(Tile));
    for (int j = 0; j < LEVEL_TILE_HEIGHT; j++)
    {
      Tile tile;
      tile.type = TILE_WALL;
      tile.position = (Vector2){200 + i * 32, 100 + j * 32};
      tile.sprite = createSprite(levelTexture, (Rectangle){0, 0, 0, 0}, 32, 32, (Vector2){0, 0});

      if (i > 0 && i < LEVEL_TILE_WIDTH - 1 && j > 0 && j < LEVEL_TILE_HEIGHT - 1)
      {
        tile.type = TILE_FLOOR;

        if (i == 1 && j == 1)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_LEFT_TOP;
        }
        else if (i == 1 && j == LEVEL_TILE_HEIGHT - 2)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_LEFT_BOTTOM;
        }
        else if (i == LEVEL_TILE_WIDTH - 2 && j == 1)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_RIGHT_TOP;
        }
        else if (i == LEVEL_TILE_WIDTH - 2 && j == LEVEL_TILE_HEIGHT - 2)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_RIGHT_BOTTOM;
        }
        else if (i == 1)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_LEFT;
        }
        else if (i == LEVEL_TILE_WIDTH - 2)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_RIGHT;
        }
        else if (j == 1)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_TOP;
        }
        else if (j == LEVEL_TILE_HEIGHT - 2)
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_BOTTOM;
        }
        else
        {
          tile.variant.floor = TILE_FLOOR_VARIANT_CENTER;
        }

        Rectangle srcRect;
        srcRect.width = 16;
        srcRect.height = 16;

        switch (tile.variant.floor)
        {
        case TILE_FLOOR_VARIANT_LEFT_TOP:
          srcRect.x = 32 + 16 * 0;
          srcRect.y = 32 + 16 * 0;
          break;
        case TILE_FLOOR_VARIANT_LEFT_BOTTOM:
          srcRect.x = 32 + 16 * 0;
          srcRect.y = 32 + 16 * 4;
          break;
        case TILE_FLOOR_VARIANT_RIGHT_TOP:
          srcRect.x = 32 + 16 * 4;
          srcRect.y = 32 + 16 * 0;
          break;
        case TILE_FLOOR_VARIANT_RIGHT_BOTTOM:
          srcRect.x = 32 + 16 * 4;
          srcRect.y = 32 + 16 * 4;
          break;
        case TILE_FLOOR_VARIANT_LEFT:
          srcRect.x = 32 + 16 * 0;
          srcRect.y = 32 + 16 * 1;
          break;
        case TILE_FLOOR_VARIANT_RIGHT:
          srcRect.x = 32 + 16 * 4;
          srcRect.y = 32 + 16 * 1;
          break;
        case TILE_FLOOR_VARIANT_TOP:
          srcRect.x = 32 + 16 * 1;
          srcRect.y = 32 + 16 * 0;
          break;
        case TILE_FLOOR_VARIANT_BOTTOM:
          srcRect.x = 32 + 16 * 1;
          srcRect.y = 32 + 16 * 4;
          break;
        case TILE_FLOOR_VARIANT_CENTER:
          srcRect.x = 32 + 16 * 1;
          srcRect.y = 32 + 16 * 1;
          break;

        default:
          srcRect.x = 32;
          srcRect.y = 32;
          break;
        }

        tile.sprite.srcRect = srcRect;
      }

      tile.sprite.dstRect.x = tile.position.x;
      tile.sprite.dstRect.y = tile.position.y;

      level.tiles[i][j] = tile;
    }
  }

  return level;
}

void drawLevel(Level *level)
{
  for (int i = 0; i < LEVEL_TILE_WIDTH; i++)
  {

    for (int j = 0; j < LEVEL_TILE_HEIGHT; j++)
    {
      if (level->tiles[i][j].type != TILE_WALL)
      {
        drawSprite(&level->tiles[i][j].sprite);
        // DrawCircle(level->tiles[i][j].sprite.dstRect.x, level->tiles[i][j].sprite.dstRect.y, 2, RED);
      }
      else
      {
        // DrawRectangleLinesEx(level->tiles[i][j].sprite.dstRect, 3, GREEN);
      }
    }
  }

  for (int i = 0; i < level->itemsCount; i++)
  {
    drawItem(level->items[i]);
  }
}

void addItemToLevel(Level *level, Item *item)
{
  if (level->itemsCount < 20)
  {
    level->items[level->itemsCount++] = item;
  }
}

void updateLevel(Level *level)
{
  for (int i = 0; i < level->itemsCount; i++)
  {
    updateItem(level->items[i]);
  }
}
