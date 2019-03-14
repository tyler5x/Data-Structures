#include <iostream> 
#include <cmath>
#include <cstdlib>


#include "cs225/HSLAPixel.h"// is this one nessary and needed to be included in .h? or .cpp?
#include "Image.h"

using cs225::HSLAPixel;
using cs225::Image;

void Image::darken() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
     if (pixel.l >= 0.1)
      pixel.l = pixel.l - 0.1;
     else
      pixel.l = 0;
  }
 }
}

void Image::darken(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
     if (pixel.l >= amount)
      pixel.l = pixel.l - amount;
     else
      pixel.l = 0;
  }
 }
}

void Image::lighten() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
     if (pixel.l <= 0.9)
      pixel.l = pixel.l + 0.1;
     else
      pixel.l = 1.0;
  }
 }
}

void Image::lighten(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      double limit = 1 - amount;
     if (pixel.l <= limit)
      pixel.l = pixel.l + amount;
     else
      pixel.l = 1.0;
  }
 }
}

void Image::desaturate() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
     if (pixel.s >= 0.1)
      pixel.s = pixel.s - 0.1;
     else
      pixel.s = 0;
  }
 }
}

void Image::desaturate(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
     if (pixel.s >= amount)
      pixel.s = pixel.s - amount;
     else
      pixel.s = 0;
  }
 }
}

void Image::saturate() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
     if (pixel.s <= 0.9)
      pixel.s = pixel.s + 0.1;
     else
      pixel.s = 1.0;
  }
 }
}

void Image::saturate(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      double limit = 1 - amount;
     if (pixel.s <= limit)
      pixel.s = pixel.s + amount;
     else
      pixel.s = 1.0;
  }
 }
}

void Image::grayscale() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
  }
 }
}

void Image::illinify() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
     if (pixel.h > 113.5 && pixel.h < 293.5)
     pixel.h = 216;
     else
     pixel.h = 11;
    }
  }
}

void Image::rotateColor (double degrees) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.h = pixel.h + degrees;
     if (pixel.h > 360)
      pixel.h = pixel.h - 360;
     if (pixel.h  < 0)
      pixel.h = pixel.h + 360;
  }
 }
}


void Image::scale (unsigned int w, unsigned int h) {// is int necessary????
  //Why without copy pixel?
  Image mapll = *this;
  double h1 = ((double) h/height());
  double w1 = ((double) w/width());
  double factor = (h1 < w1) ? h1: w1;

  unsigned w2 = (int)(factor * this->width());
  unsigned h2 = (int)(factor * this->height());
  this->resize(w2, h2);
  if (factor >= 1) {
  for (unsigned x = 0; x < w2; x++) {
    for (unsigned y = 0; y < h2; y++) {
      if (x < mapll.width() && y < mapll.height()) {
        for(int i=0; i<factor; i++) {
          for(int j=0; j<factor; j++) {
            HSLAPixel & oldPixel = mapll.getPixel(x, y);
            HSLAPixel & newPixel = this->getPixel((x*factor + i),(y*factor + j));
            newPixel = oldPixel;
        }
      }
    }
  }
 }
}
if (factor < 1) {
  for (unsigned x = 0; x < w2; x++) {
    for (unsigned y = 0; y < h2; y++) {

            HSLAPixel & oldPixel = mapll.getPixel(x/factor, y/factor);
            HSLAPixel & newPixel = this->getPixel(x,y);
            newPixel = oldPixel;
          }
        }
      }
}

void Image::scale (double factor) {

  unsigned w = factor * this->width();
  unsigned h = factor * this->height();
  Image mapll = *this;
  this->resize(w, h);

  if (factor >= 1) {
    for (unsigned x = 0; x < mapll.width(); x++) {
      for (unsigned y = 0; y < mapll.height(); y++) {
          for(int i=0; i<factor; i++) {
            for(int j=0; j<factor; j++) {
              HSLAPixel & oldPixel = mapll.getPixel(x, y);
              HSLAPixel & newPixel = this->getPixel((x*factor + i),(y*factor + j));
              newPixel = oldPixel;
    // unsigned int w = factor * this->width();
    // unsigned int h = factor * this->height();
    // Image mapll = *this;
    // this->resize(w, h);
    // HSLAPixel * newImageData = new HSLAPixel[w * h];
    // for (unsigned x = 0; x < w; x++) {
    //   for (unsigned y = 0; y < h; y++) {
    //     if (x < width() && y < height()) {
    //       for(int i=0; i<factor; i++) {
    //         for(int j=0; j<factor; j++) {
    //           HSLAPixel & oldPixel = mapll.getPixel(x, y);
    //           HSLAPixel & newPixel = newImageData[(x + ((y+i) * w) + j)];
    //           newPixel = oldPixel;
    //           this->getPixel() = newPixel;
            }
          }
        }
    }
  }
  if (factor < 1) {
    for (unsigned x = 0; x < w; x++) {
      for (unsigned y = 0; y < h; y++) {

              HSLAPixel & oldPixel = mapll.getPixel(x/factor, y/factor);
              HSLAPixel & newPixel = this->getPixel(x,y);
              newPixel = oldPixel;

        }
      }
    }
}
