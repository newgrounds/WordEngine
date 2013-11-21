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
    
    char letter;
    
    cocos2d::LabelTTF* label;
    
    // constructor
    Letter(int row, int col);
    
    // pick a random letter and create the label
    void randomizeLetter(int row, int col);
};

#endif
