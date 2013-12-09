#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

using namespace std;
#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // create label
    static cocos2d::MenuItemLabel* createLabel(string name);
    
    // create button
    static cocos2d::MenuItemLabel* createButton(string name, const cocos2d::ccMenuCallback &callback);
    
    // callback that starts the game
    void startGameCallback(Object* pSender);
    
    // callback that exits the app
    void exitCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif
