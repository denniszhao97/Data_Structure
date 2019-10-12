#include "StickerSheet.h"
#include <iostream>

using namespace cs225;

void StickerSheet:: clear(){
  for(int i = 0; i < maxN; i++){
      delete sheet[i];
      sheet[i] = NULL;
  }
  delete[] xl;
  xl = NULL;
  delete[] yl;
  yl = NULL;
  delete[] sheet;
  sheet = NULL;
  delete base;
  base = NULL;
}
void StickerSheet:: create(int max){
  xl = new int[max];
  yl = new int[max];
	sheet = new Image*[max];
	for (int i = 0; i < max; i++){
		sheet[i] = NULL;
	}
}

StickerSheet::StickerSheet(const Image & picture, unsigned max){
  base = new Image(picture);
  maxN = (int)max;
  create(maxN);
}

StickerSheet::~StickerSheet(){
  clear();
}


StickerSheet::StickerSheet(const StickerSheet & other){
	maxN = other.maxN;
  base = new Image(*other.base);
	create(maxN);
	for(int i = 0; i < maxN; i++){
		xl[i] = other.xl[i];
		yl[i] = other.yl[i];
		if(other.sheet[i] != NULL){
    		sheet[i] = new Image(*other.sheet[i]);
    } else{
      sheet[i] = NULL;
    }
	}
}


const StickerSheet& StickerSheet::operator= (const StickerSheet &other){
	clear();
	maxN = other.maxN;
  base = new Image(*other.base);
  create(maxN);
	for(int i = 0; i<maxN; i++){
		xl[i] = other.xl[i];
		yl[i] = other.yl[i];
		if(other.sheet[i] != NULL){
			sheet[i] = new Image(*other.sheet[i]);
		}
		else sheet[i] = NULL;
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
	int newmax = (int) max;
	if (newmax < 0){
    return;
  }

  if(newmax < maxN){
    for(int i = newmax; i < maxN; i++){
      delete sheet[i];
    }
  }

	int* nt = new int[newmax];
  int* ny = new int[newmax];
	Image** ns = new Image*[newmax];
	for(int i = 0; i < newmax; i++){
     ns[i] = NULL;
  }
	for(int i = 0; i < maxN; i++){
		if(sheet[i] != NULL && i < newmax){
			nt[i] = xl[i];
			ny[i] = yl[i];
			ns[i] = sheet[i];
		}
	}

	delete[] xl;
	delete[] yl;
	delete[] sheet;
	xl = nt;
	yl = ny;
	sheet = ns;
	maxN = newmax;
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
	int l = 0;
	for (int i = 0; i < maxN; i++){
		if (sheet[i] == NULL){
      delete sheet[i];
			l = i;
      sheet[l] = new Image(sticker);
  		xl[l] = (int)x;
  		yl[l] = (int)y;
      return l;
		}
	}
    return -1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
	int l = (int) index;
	int nx = (int) x;
	int ny = (int) y;
  if (sheet[l] == NULL || l < 0 || l >= maxN) {
		return false;
}
	xl[l] = nx;
	yl[l] = ny;
	return true;
}

void StickerSheet::removeSticker(unsigned index){
	int l = (int) index;

	if (sheet[l] != NULL){
		delete sheet[l];
		sheet[l] = NULL;
	}

}

Image * StickerSheet::getSticker(unsigned index) const{
	return sheet[(int) index];
}

Image StickerSheet::render() const{

    for(int l = 0; l < maxN; l++){
      if (sheet[l] != NULL){
          for(int x = 0; x < (int)sheet[l]->width(); x++){
              for(int y = 0; y < (int)sheet[l]->height();y++){
                  HSLAPixel &cur = sheet[l] -> getPixel(x,y);
                  if (cur.a != 0){
            			HSLAPixel &newOne = base-> getPixel(xl[l]+x,yl[l]+y);
            			newOne.h = cur.h;
            			newOne.s = cur.s;
            			newOne.l = cur.l;
            			newOne.a = cur.a;

            		}
              }
            }
        }
    }
    Image stickImage (*base);
    return stickImage;

}
