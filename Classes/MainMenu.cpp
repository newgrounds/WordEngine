//
//  MainMenu.cpp
//  WordEngine
//
//  Created by Adam Gressen on 12/5/13.
//
//

#include "MainMenu.h"
#include "Game.h"
#include "cocos2d.h"
#include "Letter.h"

USING_NS_CC;

Scene* MainMenu::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

MenuItemLabel* MainMenu::createLabel(string name) {
    LabelTTF* lab = LabelTTF::create(name.c_str(), "Arial", 35);
    return MenuItemLabel::create(lab);
}

MenuItemLabel* MainMenu::createButton(string name, const ccMenuCallback &callback) {
    LabelTTF* lab = LabelTTF::create(name.c_str(), "Arial", 35);
    return MenuItemLabel::create(lab, callback);
}

// on "init" you need to initialize your instance
bool MainMenu::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    // add title label
    LabelTTF* titleLabel = LabelTTF::create("Word Engine", "Arial", 50);
    titleLabel->setPosition(Point(Director::getInstance()->getVisibleSize().width/2,
                                  Director::getInstance()->getVisibleSize().height - titleLabel->getContentSize().height/2 - Letter::PADDING));
    this->addChild(titleLabel, 1);
    
    // add a button to start the game
    MenuItemLabel* startItem = createButton("New Game", CC_CALLBACK_1(MainMenu::startGameCallback, this));
    
    // add a button to exit the app
    MenuItemLabel* exitItem = createButton("Exit", CC_CALLBACK_1(MainMenu::exitCallback, this));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, exitItem, NULL);
    //menu->setPosition(Point::ZERO);
    menu->alignItemsVertically();
    this->addChild(menu, 1);
    
    return true;
}

void MainMenu::startGameCallback(Object* pSender) {
    Director::getInstance()->replaceScene(Game::createScene());
}

void MainMenu::exitCallback(Object* pSender) {
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
