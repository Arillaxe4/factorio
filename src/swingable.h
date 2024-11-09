#ifndef SWINGABLE_H
#define SWINGABLE_H

#define SWINGABLE_ANGE_MAX 120

typedef struct
{
  float animationFrameDelay;

  float animationTimer;
  float animationAngle;
  float bobValue;
} Swingable;

Swingable createSwingable(float animationFrameDelay);

void updateSwingable(Swingable *swingable);

void swingSwingable(Swingable *swingable);

#endif // SWINGABLE_H
