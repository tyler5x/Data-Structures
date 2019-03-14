/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */

#include <cstdlib>
#include <cmath>
#include <iostream>//added
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image; //why don't we use delete?
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
HSLAPixel* myFavoriteColor() {
    HSLAPixel*p = new HSLAPixel(280, 0.8, 0.5);
    return p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG(); //ediedBUG@@@@@
    // std::cout << "Reached line " << __LINE__ << std::endl;//added
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
    // std::cout << "Reached line " << __LINE__ << std::endl;//added
    // Create out.png
    PNG* output = setupOutput(width, height); //BUG@@@@@@ ??????????????
    // output = original; //
    // setupOutput(width, height);
    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    // std::cout << "Reached line " << __LINE__ << std::endl; //added
    for (unsigned y = 1; y < height; y++) {
        for (unsigned x = 1; x < width; x++) {//BUG@@@ 0<x<100; worry
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);
            // std::cout << "Reached line " << __LINE__ << std::endl;
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel &currOutPixel = (*output).getPixel(x, y); //BUG@@@@@@@???????????????reference
     // std::cout << "Reached line " << __LINE__ << std::endl;
            if (diff > 20) {
                currOutPixel = *myPixel;
            }
            // std::cout << "line " << __LINE__ << ": x = " << x << std::endl;
            // std::cout << "line " << __LINE__ << ": y = " << y << std::endl;
            // break;
        }
    
        //how to test 2,3;
    }
    // std::cout << "Reached line " << __LINE__ << std::endl; //added
    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
    // std::cout << "Reached line " << __LINE__ << std::endl;
}
