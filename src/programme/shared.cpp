#include "shared.h"

// Étoile à 5 branches
//
// https://en.wikipedia.org/wiki/Hypotrochoid
bool _etoile(float& x, float& y, float cx, float cy, float r, float position=0)
{
  // Division par zéro
  if (r <= 0) {
    return false;
  }

  // Position va de 0 à 1
  if (position < 0 || position > 1) {
    return false;
  }

  // Rayon interne
  float r2 = r * 3/5.;

  // t va de 0 à 6 pi
  float t = position * 6 * M_PI;

  x = cx + (r - r2) * cos(t) + r * cos((r - r2) / r2 * t);
  y = cy + (r - r2) * sin(t) - r * sin((r - r2) / r2 * t);
}
