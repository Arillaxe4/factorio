#include "sprite.h"
#include <stdio.h>

Sprite createSprite(Texture *texture, Rectangle srcRect, float w, float h, Vector2 origin)
{
  Sprite sprite;

  sprite.texture = texture;
  sprite.srcRect = srcRect;
  sprite.origin = origin;

  sprite.dstRect = (Rectangle){0, 0, w, h};

  return sprite;
}

void setSpriteAnimation(Sprite *sprite, int maxFrames, float animationFrameDelay)
{
  sprite->isAnimation = true;
  sprite->maxFrames = maxFrames;
  sprite->animationFrameDelay = animationFrameDelay;
  sprite->animationTimer = animationFrameDelay;
  sprite->currentFrame = 0;
}

void updateSprite(Sprite *sprite)
{
  if (sprite->isAnimation)
  {
    float frameTime = GetFrameTime();
    sprite->animationTimer -= frameTime;

    if (sprite->animationTimer <= 0)
    {
      sprite->animationTimer = sprite->animationFrameDelay;
      sprite->currentFrame++;
      sprite->currentFrame %= sprite->maxFrames;

      sprite->srcRect.x = sprite->srcRect.width * sprite->currentFrame;
    }
  }
}

void drawSprite(Sprite *sprite)
{
  DrawTexturePro(
      *sprite->texture,
      sprite->srcRect,
      sprite->dstRect,
      sprite->origin,
      sprite->angle,
      WHITE);
}
