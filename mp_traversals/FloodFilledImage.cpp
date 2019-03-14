#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = png;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  traversal_.push_back(&traversal);
  picker_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {//QUESTION: Why animate can call the function in class FloodFillImage?
  Animation animation;
  /** @todo [Part 2] */
  //why I need to go through alll kind of traversals?
  animation.addFrame(png_);
  // vector<ColorPicker*>::iterator itPicker = picker_.begin();
  //error: no viable conversion from
  //error:  '__wrap_iter<const_pointer>' to ' __wrap_iter<pointer>'

  // for (vector<ImageTraversal*>::iterator itTraversal = traversal_.begin(); itTraversal != traversal_.end(); ++itTraversal) {
  //   ImageTraversal* t = *itTraversal;
  //   ColorPicker* p = *itPicker;
  // }
  for (size_t i = 0; i < traversal_.size(); i++) {
    ImageTraversal* t = traversal_[i];
    ColorPicker* pr = picker_[i];
    unsigned countFrame = 0;
    // for (const Point & p :*t) {
    //   countFrame ++;
    //   HSLAPixel& pixel1 = png_.getPixel(p.x, p.y);// **iterator is not pointor so can not use -> but iterator can use *
    //   HSLAPixel pixel2 = pr->getColor(p.x, p.y);
    //   HSLAPixel& pixel2 = pr->getColor(p.x, p.y);
    //error:  non-const lvalue reference to type
    //error:  'cs225::HSLAPixel' cannot bind to a temporary of type 'cs225::HSLAPixel'

    //another low efficient method:
    for (ImageTraversal::Iterator it = t->begin(); it != t->end(); ++it) {
      countFrame ++;
      HSLAPixel& pixel1 = png_.getPixel(it->x, (*it).y);// ***iterator is not pointor so can not use -> but iterator can use *
      HSLAPixel pixel2 = pr->getColor((*it).x, (*it).y);
      pixel1 = pixel2;
      if (countFrame == frameInterval) {
        animation.addFrame(png_);
        countFrame = 0;
      }
    }
    // ++itPicker;
  }
  animation.addFrame(png_);
  return animation;
}
