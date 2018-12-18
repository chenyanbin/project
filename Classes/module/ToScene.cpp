//
//  ToScene.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/17.
//
//

#include "ToScene.h"
#include "famousGeneral/famouseBossCome/FamouseBossCome.hpp"
ToScene::ToScene()
:tag_openLayer(0)
{
    
}
ToScene::~ToScene()
{
    
}
bool ToScene::init(int openLayer)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Scene::init());
        this->tag_openLayer = openLayer;
        bref = true;
    } while (false);
    
    return bref;
}
ToScene* ToScene::create(int openLayer)
{
    ToScene* scene = new ToScene();
    if(scene && scene->init(openLayer))
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return NULL;
}
void ToScene::onEnter()
{
    Scene::onEnter();
    openLayer();
}
void ToScene::openLayer()
{
    BaseLayer* layer = NULL;
    switch (this->tag_openLayer)
    {
        case SCENE_TAG_BOSSCOME:
            FamouseBossCome::show();
            break;
    }
    if(layer)
    {
        this->addChild(layer,SCENE_LAYER_ZORDER,tag_openLayer);
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
    }
    
}
void ToScene::onExit()
{
    Scene::onExit();
}