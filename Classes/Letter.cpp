//
//  Letter.cpp
//  HelloCpp
//
//  Created by Adam Gressen on 11/18/13.
//
//

#include "Letter.h"

Letter::Letter(int row, int col) {
    randomizeLetter(row, col);
}

void Letter::randomizeLetter(int row, int col) {
    // grab a random int between 0-25
    int n = rand() % 26;
    // convert to a lowercase letter
    letter = (char)('a' + n);
    cocos2d::log("%c", letter);
    
    // create the label
    char l[1] = {letter};
    label = cocos2d::LabelTTF::create(l, "Arial", 24);
    posn = cocos2d::Point(240+(row*PADDING), 240+(col*PADDING));
    label->setPosition(posn);
    label->setColor(cocos2d::Color3B(255, 255, 255));
}

