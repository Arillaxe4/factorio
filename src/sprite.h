#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct
{
  Texture *texture;
  Rectangle srcRect;
  Rectangle dstRect;
  float angle;
  bool isAnimation;
  float animationTimer;
  float animationFrameDelay;
  int currentFrame;
  int maxFrames;
} Sprite;

Sprite createSprite(Texture *texture, Rectangle srcRect, float w, float h);

void setSpriteAnimation(Sprite *sprite, int maxFrames, float animationFrameDelay);

void updateSprite(Sprite *sprite);

void drawSprite(Sprite *sprite);

#endif // SPRITE_H
