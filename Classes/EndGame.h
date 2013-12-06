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
#include "MainMenu.h"
#include "Game.h"

class EndGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // callback that starts the game
    void restartGameCallback(Object* pSender);
    
    // callback that exits the app
    void menuCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EndGame);
};

#endif
