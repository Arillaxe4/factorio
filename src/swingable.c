#include "swingable.h"
#include "stdio.h"
#include "raylib.h"

Swingable createSwingable(float animationFrameDelay)
{
  Swingable swingable;

  swingable.animationFrameDelay = animationFrameDelay;
  swingable.animationTimer = 0;
  swingable.animationAngle = 0;

  return swingable;
}

void updateSwingable(Swingable *swingable)
{
  if (swingable->animationTimer > 0)
  {
    float frameTime = GetFrameTime();

    swingable->animationTimer -= frameTime;
    float progress = (swingable->animationFrameDelay - swingable->animationTimer) / swingable->animationFrameDelay;
    swingable->animationAngle = progress * SWINGABLE_ANGE_MAX;
  }
  else
  {
    swingable->animationAngle = 0;
  }
}

void swingSwingable(Swingable *swingable)
{
  if (swingable->animationTimer <= 0)
  {
    swingable->animationTimer = swingable->animationFrameDelay;
  }
}
