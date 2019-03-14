#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

 bool ImageTraversal::Iterator:: _avaliable (Point p) { //IMPORTANT bool ImageTraversal::Iterator:: _avaliable (Point p)
  if(p.x >= png_.width() || p.y >= png_.height()) //***begin from 0 so >=
  return false;
  HSLAPixel & p1 = png_.getPixel(p.x, p.y);
  HSLAPixel & p2 = png_.getPixel(start_.x, start_.y);
  double diff = calculateDelta(p1, p2);
  if (diff > tolerance_)
  return false;
  else
  return true;
 }


/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
}

ImageTraversal::Iterator::~Iterator() {
  // delete traversal_;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, const PNG & png, const Point & start, double tolerance) {
  // cout << "here in iterator constructor" << endl;

  traversal_ =  traversal;
  png_ = png;
  start_ = start;
  cur_ = start;
  tolerance_ =tolerance;
  for (unsigned i = 0; i < png_.width()*png_.height(); i++) {//****Initialize the vector, If not it will cause segfault when you use index to visite it;
    done_.push_back(false);
  }
  done_[cur_.x*png_.height() + cur_.y] = true;// set the current point visited
}
// ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start) {
//   traversal_ = traversal;
//   start_ = start;
//   cur_ = traversal->peek();
// }

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  // cout << "here in ++" << endl;
  unsigned x_ = cur_.x;
  unsigned y_ = cur_.y;
  Point p1 = Point(x_+1, y_);
  Point p2 = Point(x_, y_+1);
  Point p3 = Point(x_-1, y_);
  Point p4 = Point(x_, y_-1);

  // Point pp = Point(4,0);

  if (_avaliable(p1))
   traversal_->add(p1);
  if (_avaliable(p2))
   traversal_->add(p2);
  if (_avaliable(p3))
   traversal_->add(p3);
  if (_avaliable(p4))
   traversal_->add(p4);

  if (traversal_->empty())
   return *this;

  cur_ = traversal_->pop();
  while (done_[cur_.x*png_.height() + cur_.y] ) {
      if (traversal_->empty())
        break;
      else
        cur_ = traversal_->pop();
    }
  done_[cur_.x*png_.height() + cur_.y] = true;

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return cur_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal_ == NULL) { thisEmpty = true; }
  if (other.traversal_ == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal_->empty(); } //if thisEmpty != NULL, equal to the traversal's empty();
  if (!otherEmpty) { otherEmpty = other.traversal_->empty(); }

  if (thisEmpty && otherEmpty) return false;// both equal ro NULL, these two are equal
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal_ != other.traversal_);
  else return true;
  return false;
}
