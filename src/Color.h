#ifndef __COLOR_H__
#define __COLOR_H__

#include "Tetrom.h"


struct Color {

  Color(unsigned char red, unsigned char green, unsigned char blue)
      : blue(blue), green(green), red(red) {}
  
  //Get the color of a Teatrom
  static Color GetTetromColor(TetromType T)
  {
    switch(T){
        case TetromType::I:{return Color(255,   0,   0);}
        case TetromType::S:{return Color(  0,   0, 255);}
        case TetromType::L:{return Color(255, 255,   0);}
        case TetromType::O:{return Color(  0, 255,   0);}
        case TetromType::T:{return Color(255,   0, 255);}
    }
    return Color(255, 255, 255);;
  } 

  unsigned char red;
  unsigned char blue;
  unsigned char green;
};



#endif // __COLOR_H__