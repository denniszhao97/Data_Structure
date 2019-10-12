#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;
MyColorPicker::MyColorPicker(double increment_){
  hue = 1000*increment_;
  l = 0;
  increment = increment_;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel pixel(hue, 1, l);
  l += increment;
  if (l >= 1) { l -= 1; }
  return pixel;
}
