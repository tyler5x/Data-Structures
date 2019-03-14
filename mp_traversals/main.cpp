
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG png;
  png.readFromFile("tests/paidaxing.png");
  FloodFilledImage image(png);
  DFS dfs(png, Point(500,400), 0.07);
  BFS bfs(png, Point(500,800), 0.07);
 
  // RainbowColorPicker rainbow(0.02);
  MyColorPicker my(20,5,20,20,200);
  image.addFloodFill( dfs,my );
  // HSLAPixel color1(131, 100, 27);
  HSLAPixel color(11, 73, 1);
  SolidColorPicker solid(color);
  // SolidColorPicker solid1(color1);
  image.addFloodFill( bfs, solid );
  // image.addFloodFill(bfs1, rainbow);

  Animation animation = image.animate(5000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");




  return 0;
}
