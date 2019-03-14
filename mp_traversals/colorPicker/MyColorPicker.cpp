#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;


  MyColorPicker::MyColorPicker(unsigned a, unsigned b, unsigned c, unsigned d, unsigned e)
    : a(20), b(20), c(1), d(1), e(20) { }
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if(a >= 360) {
    a -= 360;
  }
  if(e >= 360) {
    e -= 360;
  }
  HSLAPixel pixel(a, 1, 0.6);
  a+=b;
  if(a>c == 0 || a<d == 0) {
    pixel.h = e;
  }
  return pixel;
}
