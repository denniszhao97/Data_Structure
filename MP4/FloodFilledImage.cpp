#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;
using namespace std;
/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */

//copy constructor
  image = new PNG(png);

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
//          cout<<(*((traversal).begin())).x<<endl;
  ImageTraversal* IT = NULL;
  IT = &traversal;
//  *IT = traversal;
//          cout<<(*((*IT).begin())).x<<endl;
  ColorPicker* CP = NULL;
  CP = &colorPicker;
  ITV_.push_back(IT);
  CPV_.push_back(CP);
  //    cout<<(*((ITV_[0])begin())).x<<endl;
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
Animation FloodFilledImage::animate(unsigned frameInterval) const {

  Animation animation;
  unsigned size = 0;
  while(size < ITV_.size()){
      ImageTraversal::Iterator itbegin = ITV_[size]->begin();
      ImageTraversal::Iterator itend = ITV_[size]->end();
      animation.addFrame(*image);
      unsigned count = 0;
      for (ImageTraversal::Iterator it = itbegin; it != itend; ++it){
        HSLAPixel pixel = (*CPV_[size]).getColor((*it).x,(*it).y);
        HSLAPixel& newpixel = image->getPixel((*it).x,(*it).y);
        newpixel.h = pixel.h;
        newpixel.s = pixel.s;
        newpixel.l = pixel.l;
        newpixel.a = pixel.a;
        count++;
        if (count % frameInterval==0){
          animation.addFrame(*image);
        }
    }
    size++;
    animation.addFrame(*image);
  }
  return animation;
  //diff i-rainbow-bfs.png tests/i-rainbow-bfs.png
}

FloodFilledImage::~FloodFilledImage(){
  delete image;
}
