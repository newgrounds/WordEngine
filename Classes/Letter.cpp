//
//  Letter.cpp
//  HelloCpp
//
//  Created by Adam Gressen on 11/18/13.
//
//

#include "Letter.h"

Letter::Letter() {}

Letter::Letter(int r, int c) {
    row = r;
    col = c;
    randomizeLetter();
}

cocos2d::Point Letter::positionLetter(int r, int c) {
    return cocos2d::Point((r+6)*(cocos2d::Director::getInstance()->getVisibleSize().width/18),
                          (c+3)*(cocos2d::Director::getInstance()->getVisibleSize().height/12));
}

void Letter::randomizeLetter() {
    // grab a random int between 0-25
    int n = rand() % 26;
    // convert to a lowercase letter
    letter = (char)('a' + n);
    cocos2d::log("%c", letter);
    
    // create the label
    char l[1] = {letter};
    label = cocos2d::LabelTTF::create(l, "Arial", 35);
    posn = positionLetter(row,  col);
    label->setPosition(posn);
    label->setColor(cocos2d::Color3B(255, 255, 255));
}

