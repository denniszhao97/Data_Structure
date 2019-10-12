#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"

using namespace cs225;

int main() {
  Image meme;     meme.readFromFile("tests/meme.png");
  Image sticker1;        sticker1.readFromFile("tests/sticker1.png");
  Image sticker2; sticker2.readFromFile("tests/sticker2.png");
  Image sticker3; sticker3.readFromFile("tests/sticker3.png");
  Image word1; word1.readFromFile("tests/word1.png");
  Image word2; word2.readFromFile("tests/word2.png");
  Image word3; word3.readFromFile("tests/word3.png");
  Image word4; word4.readFromFile("tests/word4.png");
  sticker1.scale(0.55);
  sticker2.scale(0.5);
  sticker3.scale(0.45);
  word1.scale(0.5);
  word2.scale(0.5);
  word3.scale(0.5);
  word4.scale(0.5);
  StickerSheet sheet(meme, 10);
  sheet.addSticker(sticker1, 190,55);
  sheet.addSticker(sticker2, 715,0);
  sheet.addSticker(sticker3, 700,310);
  sheet.addSticker(word1, 300,20);
  sheet.addSticker(word2, 300,80);
  sheet.addSticker(word3, 300,140);
  sheet.addSticker(word4, 300,200);

  sheet.render().writeToFile("myImage.png");
  return 0;
}
