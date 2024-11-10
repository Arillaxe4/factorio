#ifndef SWINGABLE_H
#define SWINGABLE_H

#define SWINGABLE_ANGE_MAX 60

typedef struct
{
  float animationFrameDelay;

  float animationTimer;
  float animationAngle;
} Swingable;

Swingable createSwingable(float animationFrameDelay);

void updateSwingable(Swingable *swingable);

void swingSwingable(Swingable *swingable);

#endif // SWINGABLE_H
