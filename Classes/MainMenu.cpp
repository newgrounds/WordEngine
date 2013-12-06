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

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// create labels
MenuItemLabel* createMenuItem(string name, const ccMenuCallback &callback) {
    LabelTTF* lab = LabelTTF::create(name.c_str(), "Arial", 35);
    return MenuItemLabel::create(lab, callback);
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add a button to start the game
    MenuItemLabel* startItem = createMenuItem("Start", CC_CALLBACK_1(MainMenu::startGameCallback, this));
    
    // add a button to exit the app
    MenuItemLabel* exitItem = createMenuItem("Exit", CC_CALLBACK_1(MainMenu::exitCallback, this));
    
    // position menu items
    startItem->setPosition(Point(origin.x + (screenSize.width/2),
                                 origin.y + (screenSize.height/2) - startItem->getContentSize().height/2));
    exitItem->setPosition(Point(origin.x + (screenSize.width/2),
                                origin.y + (screenSize.height/2) - startItem->getContentSize().height - exitItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, exitItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void MainMenu::startGameCallback(Object* pSender)
{
    Director::getInstance()->replaceScene(Game::createScene());
}

void MainMenu::exitCallback(Object* pSender)
{
    Director::getInstance()->end();
    exit(0);
}
