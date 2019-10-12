#include <iostream>
#include "cs225/HSLAPixel.h"
#include "Image.h"
using namespace cs225;

//Lighten an Image by increasing the luminance of every pixel by 0.1.
//This function ensures that the luminance remains in the range [0, 1].
void Image::lighten(){
  int width = this->width();
	int height = this->height();
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			HSLAPixel & pixel  = this->getPixel(i,j);
			pixel.l = pixel.l + 0.1;
      if(pixel.l > 1.0){
        pixel.l = 1.0;
      }
	  }
  }
}

//Lighten an Image by increasing the luminance of every pixel by amount.
void Image::lighten(double amount){
	int width = this->width();
	int height = this->height();
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
			pixel.l = pixel.l + amount;
      if(pixel.l > 1.0){
        pixel.l = 1.0;
      }
	  }
  }
}

//Darken an Image by decreasing the luminance of every pixel by 0.1.
//This function ensures that the luminance remains in the range [0, 1].
void Image::darken(){
  int width = this->width();
  int height = this->height();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
      pixel.l = pixel.l - 1.0;
      if(pixel.l < 0){
        pixel.l = 0;
      }
    }
  }
}



//Darkens an Image by decreasing the luminance of every pixel by amount.
void Image::darken(double amount){
	int width = this->width();
	int height = this->height();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
      pixel.l = pixel.l - amount;
      if(pixel.l < 0){
        pixel.l = 0;
      }
    }
  }
}


//Saturates an Image by increasing the saturation of every pixel by 0.1.

void Image::saturate(){
  int width = this->width();
	int height = this->height();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
      pixel.s = pixel.s + 0.1;
      if(pixel.s > 1.0){
        pixel.s = 1.0;
      }
    }
  }
}



void Image::saturate(double amount){
  int width = this->width();
	int height = this->height();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
      pixel.s = pixel.s + amount;
      if(pixel.s > 1.0){
        pixel.s = 1.0;
      }
    }
  }
}


//Desaturates an Image by decreasing the saturation of every pixel by 0.1.
void Image::desaturate(){
  int width = this->width();
	int height = this->height();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
      pixel.s = pixel.s - 0.1;
      if(pixel.s < 0){
        pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount){
  int width = this->width();
  int height = this->height();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
      pixel.s = pixel.s - amount;
      if(pixel.s < 0){
        pixel.s = 0;
      }
    }
  }
}


//Turns the image grayscale.
void Image::grayscale(){
  int width = this->width();
  int height = this->height();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      HSLAPixel & pixel  = this->getPixel(i,j);
      pixel.s = 0;
    }
  }
}


//Rotates the color wheel by degrees.
//This function ensures that the hue remains in the range [0, 360].
void Image::rotateColor(double degrees){
	int width = this->width();
	int height = this->height();
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			HSLAPixel & pixel = this->getPixel(i,j);
         pixel.h = pixel.h + degrees;
			   if (pixel.h > 360){
			        pixel.h = pixel.h - 360;
            }
         if (pixel.h < 0){
			        pixel.h = pixel.h + 360;
            }
		}
	}

}



//Illinify the image.
void Image::illnify(){
	int width = this->width();
	int height = this->height();
	for (int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			HSLAPixel & pixel = this -> getPixel(i,j);
      double temp =  pixel.h;
      if(temp >= 0 && temp < 216.0){
        if((temp - 11.0)*(temp - 11.0) >= (temp - 216.0)*(temp - 216.0)){
          pixel.h = 216.0;
        } else{
          pixel.h = 11.0;
        }
      }
      else if(temp > 216.0){
        if((temp - 371.0)*(temp - 371.0) >= (temp - 216.0)*(temp - 216.0)){
          pixel.h = 216.0;
        } else{
          pixel.h = 11.0;
        }
      }
    }
  }
}

// A factor of 1.0 does not change the iamge.
// A factor of 0.5 results in an image with half the width and half the height.
// A factor of 2 results in an image with twice the width and twice the height.
// This function both resizes the Image and scales the contents.
void Image::scale(double factor){
	int newW = factor * (this->width());
  int newH = factor * (this->height());
  PNG* newOne= new PNG (newW,newH);
  for (int i = 0; i < newW;i++) {
    for (int j = 0; j < newH; j++) {
       HSLAPixel  &pixel = this->getPixel(i/factor,j/factor);
       HSLAPixel  &newPixel = newOne->getPixel(i,j);
       newPixel.h = pixel.h;
       newPixel.s = pixel.s;
       newPixel.l = pixel.l;
       newPixel.a = pixel.a;
    }
  }

  this->resize(newW,newH);
  for (int i = 0; i < newW;i++) {
    for (int j = 0; j < newH; j++) {
      cs225::HSLAPixel & pixel = this->getPixel(i,j);
      pixel.h = newOne->getPixel(i,j).h;
      pixel.s = newOne->getPixel(i,j).s;
      pixel.l = newOne->getPixel(i,j).l;
      pixel.a = newOne->getPixel(i,j).a;
    }
  }

  delete newOne;
}



//This function preserves the aspect ratio of the image, so the result will always be an image of width w or of height h (not necessarily both).
//This function both resizes the Image and scales the contents.
void Image::scale(unsigned w, unsigned h){
	PNG* newOne = new PNG (w,h);
	for (unsigned i = 0; i < w;i++) {
		for (unsigned j = 0; j < h; j++) {
			HSLAPixel  &pixel = this->getPixel(i*this->width()/(int)w , j*this->height()/(int)h);
			HSLAPixel  &newPixel = newOne->getPixel(i,j);
	    newPixel.h = pixel.h;
      newPixel.s = pixel.s;
      newPixel.l = pixel.l;
      newPixel.a = pixel.a;
		}
	}
  this->resize(w,h);
  for (unsigned i = 0; i < w; i++) {
    for (unsigned j = 0; j < h; j++) {
      cs225::HSLAPixel & pixel = this->getPixel(i,j);
      pixel.h = newOne->getPixel(i,j).h;
      pixel.s = newOne->getPixel(i,j).s;
      pixel.l = newOne->getPixel(i,j).l;
      pixel.a = newOne->getPixel(i,j).a;
    }
  }

    delete newOne;

}
