#include <math.h>

#ifndef LOG
#ifndef DEBUG
#define LOG
#endif
#endif

void etoile(float cx, float cy, float r, float par = -1);

// Étoile à 5 branches
//
// https://en.wikipedia.org/wiki/Hypotrochoid
void etoile(float cx, float cy, float r, float par) // étoile à 5 branches
{
  float x, y;
  float r1 = r, r2 = r * 3 / 5, d = r;
  if (par <= 0) {
    par = M_PI / 180;
  }
  for (float t = 0; t < 6 * M_PI; t += par) {
    x = cx + (r1 - r2) * cos(t) + d * cos((r1 - r2) / r2 * t);
    y = cy + (r1 - r2) * sin(t) - d * sin((r1 - r2) / r2 * t);
    toAngle(x, y);
    moveServos();
    LOG("HYPO", t, x, y);
  }
}
