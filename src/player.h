#ifndef PLADYER_H
#define PLADYER_H

#include "raylib.h"
#include "sprite.h"

#define WALKING_SPEED 500.f
#define WEAPON_SPEED .13f
#define WEAPON_ANGLE_MAX 120

typedef enum
{
  PLAYER_STATE_IDLE,
  PLAYER_STATE_WALKING,
} PlayerState;

typedef struct
{
  Sprite sprite;
  Vector2 position;
  Vector2 velocity;
  bool isLookingRight;
  PlayerState state;
  PlayerState previousState;
} Player;

Player createPlayer(Sprite sprite, Vector2 position);
void updatePlayer(Player *player);
void handlePlayerInputs(Player *player);
void drawPlayer(Player *player);

#endif // PLADYER_H
