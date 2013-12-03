//
//  Letter.h
//  HelloCpp
//
//  Created by Adam Gressen on 11/18/13.
//
//

#ifndef HelloCpp_Letter_h
#define HelloCpp_Letter_h

using namespace std;
#include "cocos2d.h"
#include <time.h>

class Letter
{
public:
    const static int PADDING = 50;
    
    // position on screen
    cocos2d::Point posn;
    
    // row and col on board
    int row, col;
    
    // the letter
    char letter;
    
    // the label
    cocos2d::LabelTTF* label;
    
    // constructor
    Letter(int r, int c);
    Letter();
    
    // pick a random letter and create the label
    void randomizeLetter();
};

#endif
