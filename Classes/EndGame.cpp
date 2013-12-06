//
//  EndGame.cpp
//  WordEngine
//
//  Created by Adam Gressen on 12/6/13.
//
//

#include "EndGame.h"

USING_NS_CC;

Scene* EndGame::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndGame::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add a button to start the game
    MenuItemLabel* restartItem = MainMenu::createButton("New Game", CC_CALLBACK_1(EndGame::restartGameCallback, this));
    
    // add a button to exit the app
    MenuItemLabel* menuItem = MainMenu::createButton("Main Menu", CC_CALLBACK_1(EndGame::menuCallback, this));
    
    // position menu items
    restartItem->setPosition(Point(origin.x + (screenSize.width/2) - restartItem->getContentSize().width,
                                 origin.y + restartItem->getContentSize().height));
    menuItem->setPosition(Point(origin.x + (screenSize.width/2) + menuItem->getContentSize().width,
                                origin.y + menuItem->getContentSize().height));
    
    // display the final score
    
    
    // display the number of words
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(restartItem, menuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void EndGame::restartGameCallback(Object* pSender) {
    Director::getInstance()->replaceScene(Game::createScene());
}

void EndGame::menuCallback(Object* pSender) {
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
