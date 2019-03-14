#include <iostream> //where I use this function?

#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"

using cs225::StickerSheet;
using cs225::Image;

void StickerSheet::_copy(StickerSheet const &other) {
  // unsigned *count = new unsigned[max_];
  x_ = new int[other.max_];
  y_ = new int[other.max_];
  stickers = new Image*[other.max_];
   index_ = other.index_; // do I need to copy this variabls? the index is for the element in
   max_ = other.max_;
   count = new int[other.max_];
   picture = new Image(*(other.picture));
   for(unsigned i=0; i<other.max_; i++) {
     if (other.count[i] != 0){
      stickers[i] = new Image(*(other.stickers[i]));
      x_[i] = other.x_[i];
      y_[i] = other.y_[i];
      count[i] = other.count[i];
    }
    else{
      count[i] = 0;
      x_[i] = 0;
      y_[i] = 0;
      stickers[i] = NULL;
    }
  }
}

void StickerSheet::_clear() {
    // delete []count;
    for (unsigned i = 0; i < max_; i++) {
      if (count[i] != 0) {
        delete stickers[i];
        stickers[i] = NULL;
      }
    }
    delete[] stickers;
    delete[] x_;
    delete[] y_;
    delete[] count;
    delete picture;
    stickers = NULL;
    x_ = NULL;
    y_ = NULL;
    count = NULL;
    picture = NULL;
}



StickerSheet::StickerSheet (const Image &picture, unsigned max) {////
  index_ = 0;
  max_ = max;
  // unsigned *count = new unsigned[max_];
  x_ = new int[max_];
  y_ = new int[max_];
  count = new int[max_];
  stickers = new Image*[max_];
  for(unsigned i=0; i<max_; i++) {
    count[i] = 0;
    x_[i] = 0;
    y_[i] = 0;
    stickers[i] = NULL;
  }
    this->picture = new Image(picture);
}


StickerSheet::~StickerSheet (){
  _clear();
}


StickerSheet::StickerSheet (const StickerSheet &other) {
  _copy(other);
}


const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
  if (this == &other) {
    return *this;
  }
  else {
    _clear();
    _copy(other);
    return *this;
  }
}


void StickerSheet::changeMaxStickers (unsigned max) {

     Image **newStickers = new Image*[max];
     int* newX = new int[max];
     int* newY = new int[max];
     int* newC = new int[max];
     unsigned newindex_ = 0;
     Image* newPicture = new Image(*picture);

     if (max < max_) {
       for (unsigned j = max; j < max_; j++){
         if (count[j] != 0) {
           delete stickers[j];
           stickers[j] = NULL;
           count[j]--;
         }
       }
       max_ = max;
     }
     if (max > max_) {
      for (unsigned j = 0; j < max; j++){
          newStickers[j] = NULL;
          newC[j] = 0;
        }
      }
      for (unsigned i = 0; i < max_ ; i++) {
        if (count[i]!=0){
          newStickers[i] = new Image(*stickers[i]);
          newX[i] = x_[i];
          newY[i] = y_[i];
          newC[i] = count[i];
          newindex_++;
        }
        else{
          newC[i] = 0;
        }
      }
    _clear();
    max_ = max;
    stickers = newStickers;
    x_ = newX;
    y_ = newY;
    count = newC;
    index_ = newindex_;
    picture = newPicture;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
  if (index_ < max_) {
    for (unsigned i = 0; i < max_; i++){
       if (count[i] == 0) {
           stickers[i] = new Image(sticker);
           x_[i] = x;
           y_[i] = y;
           count[i]++;
           index_ ++;
           return i;
       }
     }
   }
return -1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
  if (index < max_ && count[index] != 0) {
     x_[index] = x;
     y_[index] = y;
     return true;
   }
    else
    return false;
}

void StickerSheet::removeSticker (unsigned index) {
  if (index < max_ && count[index] != 0){
	     delete stickers[index];
       stickers[index] = NULL;
	     x_[index] = 0;
	     y_[index] = 0;
       count[index]--;
       index_--;
     }
}

Image* StickerSheet::getSticker (unsigned index) { //the location of *???
  if (index >= max_ || count[index] == 0)
  return NULL;
  else
  return stickers[index];
}

Image StickerSheet::render () const {
  unsigned h = picture->height();
  unsigned w = picture->width();

  Image *output = new Image(*picture);// can I USE THIS to initialize the image?
  for (unsigned i = 0; i < max_; i++){
   if (count[i] != 0){
     unsigned x = x_[i] + stickers[i]->width();
     unsigned y = y_[i] + stickers[i]->height();
     if (w < x) w = x;
     if (h < y) h = y;
   }
}
   output->resize(w,h);

  for (unsigned j = 0; j < max_; j++) {
  if (count[j] != 0) {
  Image sticker = *stickers[j];
  for (unsigned m = x_[j]; m < x_[j] + sticker.width(); m++) {
    for (unsigned n = y_[j]; n < y_[j] + sticker.height(); n++) {
      HSLAPixel &stkPixel = sticker.getPixel(m-x_[j],n-y_[j]);
      HSLAPixel &currPixel = output->getPixel(m,n);
      if (stkPixel.a != 0) {
        currPixel = stkPixel;
     }
    }
  }
}
}
Image out = *output;
delete output;
output = NULL;
return out;
}
