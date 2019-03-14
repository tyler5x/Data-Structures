/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "cs225/PNG.h" //pending
#include "Image.h"

namespace cs225 {
  class StickerSheet :public PNG {
  public:
    StickerSheet (const Image &picture, unsigned max);
    ~StickerSheet ();
    StickerSheet (const StickerSheet &other);
    const StickerSheet & operator= (const StickerSheet &other);
    void changeMaxStickers (unsigned max);
    int addSticker (Image &sticker, unsigned x, unsigned y);
    bool translate (unsigned index, unsigned x, unsigned y);
    void removeSticker (unsigned index);
    Image *getSticker (unsigned index);
    Image render () const;

  private:// ba ()nei de dou she cheng variabls
    int *x_;//array store the x location of left and top of Image
    int *y_;
    Image **stickers;//array store all the stickers
    // unsigned count_;//count the number of stickers
    Image *picture;//the background image
    unsigned index_;//the array index
    unsigned max_;//max number of array
    int *count;
    void _copy(StickerSheet const & other);
    void _clear();
  };
}
