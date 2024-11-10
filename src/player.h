#ifndef PLADYER_H
#define PLADYER_H

#include "raylib.h"
#include "sprite.h"
#include "level.h"
#include "item.h"

#define WALKING_SPEED 500.f

typedef enum
{
  PLAYER_STATE_IDLE = 0,
  PLAYER_STATE_WALKING = 1,
} PlayerState;

typedef struct
{
  Sprite *sprite;
  Sprite *sprites;
  Vector2 position;
  Vector2 velocity;
  bool isLookingRight;
  PlayerState state;
  PlayerState previousState;
  Rectangle collider;
  Item **items;
  Item *activeItem;
  int itemsCount;
  int maxItems;
} Player;

Player createPlayer(Sprite *sprites, Vector2 position, float w, float h);
void setPlayerSprite(Player *player, Sprite sprite);
void updatePlayer(Player *player, Level *level);
void handlePlayerInputs(Player *player);
void drawPlayer(Player *player);

void addItemToPlayer(Player *player, Item *item);
void setActiveItem(Player *player, int slotId);

bool checkAABBCollision(Rectangle a, Rectangle b);

#endif // PLADYER_H
