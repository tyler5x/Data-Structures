#include "Image.h"
#include "StickerSheet.h"
using cs225:: Image;
using cs225:: StickerSheet;

int main() {
  Image picture;
  Image sticker1;
  Image sticker2;
  Image sticker3;

  picture.readFromFile("alma.png");
  sticker1.readFromFile("dishang.png");
  sticker2.readFromFile("tianshang.png");
  sticker3.readFromFile("caishen.png");

  StickerSheet sheet(picture,8);
  sheet.addSticker(sticker1, 500, 100);
  sheet.addSticker(sticker2, 600, 500);
  sheet.addSticker(sticker3, 200, 500);

  Image out = sheet.render();
  out.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
