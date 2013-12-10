//
//  EndGame.h
//  WordEngine
//
//  Created by Adam Gressen on 12/6/13.
//
//

#ifndef EndGame_h
#define EndGame_h

using namespace std;
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainMenu.h"
#include "Game.h"

class EndGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(float s, vector<string> w);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // padding for listview
    static const int LV_PAD = 100;
    
    // callback that starts the game
    void restartGameCallback(Object* pSender);
    
    // callback that exits the app
    void menuCallback(Object* pSender);
    
    // the score
    static float score;
    
    // the words
    static vector<string> words;
    
    // implement the "static create()" method manually
    CREATE_FUNC(EndGame);
};

#endif
