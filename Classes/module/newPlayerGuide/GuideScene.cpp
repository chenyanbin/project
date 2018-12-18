//
//  GuideScene.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-9-10.
//
//

#include "GuideScene.h"
#include "NewPlayerGuild.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../commonData/data/GuideButtonManager.h"
#include "../publicLayer/GotoModule.h"

GuideScene::GuideScene()
:m_guideData(NULL)
,arrow(NULL)
,handEffect(NULL)
,isAbleClick(true)
,isClickArea(false)
,skillArrow(NULL)
,initScaleY(1)//.5
,TAG_CLIPNODE(2)
{
    
}
GuideScene::~GuideScene()
{
   
    m_guideData = NULL;
    handEffect = NULL;
    skillArrow = NULL;
    CommonEffect::pureCache(HAND_ARROW);
    const char* path = PublicShowUI::getResImgPath(IMG_NEWGUIDE_EFFECT, HAND_EFFECT);
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    ArmatureDataManager::getInstance()->removeAnimationData(HAND_EFFECT);
    ArmatureDataManager::getInstance()->removeArmatureData(HAND_EFFECT);
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("");
    path = NULL;
   
    arrow = NULL;
}
bool GuideScene::init()
{
    bool bref = false;
    do
    {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        this->isShowGrayBg = false;
        this->isAbleGuiding = false;
        setBg();
//        arrow = CommonEffect::create(HAND_ARROW);
//        arrow = Sprite::create(IMG_NEWGUIDE_ARROW1);
        arrow = Sprite::create(IMG_NEWGUIDE_ARROW);
        arrow->setAnchorPoint(Point(.7,0));
        arrow->setScaleY(initScaleY);
        this->addChild(arrow,5);
        
        const char* path = PublicShowUI::getResImgPath(IMG_NEWGUIDE_EFFECT, HAND_EFFECT);
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
        onDataLoaded(1);
        bref = true;
    }while (false);
    return bref;
}
DrawNode* GuideScene::getDrawNode()
{

    Size size =  handEffect->getContentSize();
    size.width += 10;
    size.height += 10;
    if(m_guideData)
    {
        Node* btn = GuideButtonManager::getInstance()->getButton(m_guideData->bottomId);
        if(btn)
        {
            size = btn->getContentSize();
            size = size / btn->getScale();
        }
        
    }
    
    Point anchorPoint = handEffect->getAnchorPoint();
    DrawNode *stencil = DrawNode::create();
    Point cp = handEffect->getPosition();
    Point rectangle[4];
    rectangle[0] = Point(-size.width * anchorPoint.x, -size.height * anchorPoint.y);
    rectangle[1] = Point(-size.width * anchorPoint.x + size.width,  -size.height * anchorPoint.y);
    rectangle[2] = Point(-size.width * anchorPoint.x + size.width, -size.height * anchorPoint.y + size.height);
    rectangle[3] = Point(-size.width * anchorPoint.x, -size.height * anchorPoint.y + size.height);
    Color4F white = {1, 1, 1, 1};
    //画一个多边形
    stencil->drawPolygon(rectangle, 4, white, 3, Color4F(0,0,0,1));
    stencil->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);
    Color4F red = {1, 0, 0, 1};

    stencil->setAnchorPoint(anchorPoint);
    stencil->setContentSize(size);
    return stencil;
   
}
void GuideScene::setClipNode()
{

    ClippingNode* clipNode = (ClippingNode*)this->getChildByTag(TAG_CLIPNODE);
    if(clipNode)
    {
        clipNode->removeFromParent();
    }
    Size size = VisibleRect::getVisibleRect().size;
    clipNode = ClippingNode::create();
    clipNode->setContentSize(size);
    clipNode->setAnchorPoint(Point::ZERO);
    clipNode->setInverted(true);
    
    LayerColor* layerColor = LayerColor::create(Color4B(0, 0, 0, 120), size.width*2, size.height*2);//
    layerColor->setAnchorPoint(Point::ZERO);
    layerColor->setPosition(-size.width/2, -size.height/2);
    clipNode->addChild(layerColor,1);
    
     size =  handEffect->getContentSize();
    size.width += 10;
    size.height += 10;
    if(m_guideData)
    {
        Node* btn = GuideButtonManager::getInstance()->getButton(m_guideData->bottomId);
        if(btn)
        {
             size = btn->getContentSize();
             size = size / btn->getScale();
        }
       
    }
    
  
    Point anchorPoint = handEffect->getAnchorPoint();
    DrawNode *stencil = DrawNode::create();
    Point cp = handEffect->getPosition();
    Point rectangle[4];
    rectangle[0] = Point(-size.width * anchorPoint.x, -size.height * anchorPoint.y);
    rectangle[1] = Point(-size.width * anchorPoint.x + size.width,  -size.height * anchorPoint.y);
    rectangle[2] = Point(-size.width * anchorPoint.x + size.width, -size.height * anchorPoint.y + size.height);
    rectangle[3] = Point(-size.width * anchorPoint.x, -size.height * anchorPoint.y + size.height);
    Color4F white = {1, 1, 1, 1};
    //画一个多边形
    stencil->drawPolygon(rectangle, 4, white, 3, Color4F(0,0,0,1));
    stencil->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);
    Color4F red = {1, 0, 0, 1};
    clipNode->setStencil(stencil);
    stencil->setAnchorPoint(anchorPoint);
    this->addChild(clipNode,0,TAG_CLIPNODE);
    stencil->setScale(VisibleRect::getVisibleRect().size.width / size.width);
    ScaleTo* scale = ScaleTo::create(.3, 1);
    stencil->runAction(scale);
    MoveTo* move = MoveTo::create(.3, cp);
    RemoveSelf* remove = RemoveSelf::create();
    stencil->runAction(move);
    clipNode->runAction(Sequence::create(DelayTime::create(.5), remove,NULL));
}
void GuideScene::onDataLoaded(float percent)
{
    if(percent < 1)
    {
        return;
    }
    handEffect = Armature::create(HAND_EFFECT);
    handEffect->getAnimation()->playWithIndex(0);
    handEffect->setAnchorPoint(Point(0.55,0.5));
//    handEffect->setScale(1.3);

//    RotateBy* rotate = RotateBy::create(1, 360);
//    handEffect->runAction(RepeatForever::create(Sequence::create(rotate,rotate->reverse(),NULL)));
//    Size size = handEffect->getContentSize();
    this->addChild(handEffect,100);
    handEffect->setVisible(this->arrow->isVisible());
    

}
void GuideScene::setBg()
{
//    LayerColor* layer = LayerColor::create(Color4B(0,0,0,1), designResolutionSize.width,designResolutionSize.height);
    LayerColor* layer = LayerColor::create(Color4B(0,0,0,0), VisibleRect::getVisibleRect().size.width,VisibleRect::getVisibleRect().size.height);
//    layer->setOpacity(100);
    this->setContentSize(layer->getContentSize());
    this->addChild(layer,-1,TAG_BG);
}

void GuideScene::updateGuideData(DictNewGuide* dictNewGuide)
{
    ClippingNode* clipNode = (ClippingNode*)this->getChildByTag(TAG_CLIPNODE);
    if(clipNode)
    {
        clipNode->removeFromParent();
    }
    m_guideData = dictNewGuide;
  
    Point cp;
    bool isStandScreen = false;
    if(m_guideData->bottomId > 0)
    {
        m_guideData->arrow = 1;
      
        this->setContentSize(VisibleRect::getVisibleRect().size);
        
         log("dictNewGuide->content=%s dictNewGuide->bottomId==%d",dictNewGuide->desc.c_str(),dictNewGuide->bottomId);
        cp = GuideButtonManager::getInstance()->getButtonPosition(dictNewGuide->bottomId);
  
        if(cp.x > 0 && cp.y > 0)
        {
            cp = this->convertToNodeSpace(cp);
             log("dictNewGuide->bottomId222 cp.x==%f cp.y=%f",cp.x,cp.y);
        }
       else
       {
           isStandScreen = true;
            this->setContentSize(SDResource.size);
           
           cp.x = m_guideData->x ;
           cp.y = this->getContentSize().height - m_guideData->y ;
        }
    }
    else
    {
        isStandScreen = true;
        this->setContentSize(SDResource.size);
        cp.x = m_guideData->x ;
        cp.y = this->getContentSize().height - m_guideData->y ;
        
        
    }
    if(isStandScreen)
    {
        setScaleMode();
    }
    
    arrow->stopAllActions();
    arrow->setVisible(m_guideData->arrow > 0);
    handEffect->setVisible(arrow->isVisible());
    if(arrow->isVisible())
    {
        arrow->setScaleY(initScaleY);
        arrow->setRotation(0);

        float _time = .3;
        handEffect->setVisible(false);
        MoveTo* moveTo = MoveTo::create(_time, cp);
        ActionInterval* rotateTo = NULL;
        handEffect->setPosition(cp.x,cp.y);
        int jiaodu = 0;
        switch (this->m_guideData->arrowDirect)
        {
            case 1://左
                jiaodu = 90;
               
                break;
            case 2://右
                jiaodu = -90;
               
                break;
            case 3://上
                jiaodu = 180;
               
                break;
            case 4://下
                jiaodu = 0;
             
                break;
            default:
                break;
        }
//         rotateTo = RotateTo::create(_time,jiaodu);
        arrow->setRotation(jiaodu);
//        if(rotateTo)
//        {
//            arrow->runAction(rotateTo);
//        }
        arrow->setPosition(cp);
        autoArrowPosition(cp);
//        arrow->runAction(Sequence::create(moveTo,CallFunc::create(CC_CALLBACK_0(GuideScene::autoArrowPosition, this,cp)), NULL));
    }

    
}

void GuideScene::hideArrow()
{
    handEffect->setVisible(false);
    arrow->setVisible(false);
}
void GuideScene::autoArrowPosition(Point cp)
{
    arrow->stopAllActions();
    handEffect->setVisible(arrow->isVisible());
    arrow->setPosition(cp);
    MoveTo * moveTo = NULL;
    //1-左，2-右，3-上，6-下
    switch (this->m_guideData->arrowDirect)
    {
        case 1://左
            
            handEffect->setPosition(cp.x,cp.y);
   
            moveTo = MoveTo::create(.5,cp);
            cp.x += 50;
            
            break;
        case 2://右
            handEffect->setPosition(cp.x,cp.y);
          
            moveTo = MoveTo::create(.5,cp);
            cp.x -= 50;
            
            break;
        case 3://上
            handEffect->setPosition(cp.x ,cp.y);
            arrow->setPositionY(handEffect->getPositionY());
        
            moveTo = MoveTo::create(.5,cp);
            cp.y -= 50 ;
            
            break;
        case 4://下
            if(handEffect)
            {
                handEffect->setPosition(cp.x ,cp.y);
            }
      
            moveTo = MoveTo::create(.5,cp);
            cp.y += 50 ;
            
            break;
        default:
            if(handEffect)
            {
                handEffect->setPosition(cp.x ,cp.y);
            }
            return;
            break;
    }
    MoveTo* back = MoveTo::create(.5, cp);
    arrow->runAction(RepeatForever::create(Sequence::create(moveTo,back,NULL)));

    
    setSkillArrow();
}
void GuideScene::setSkillArrow()
{
    arrow->setOpacity(255);
   
    Point cp = this->arrow->getPosition();
    arrow->setScaleY(initScaleY);
    arrow->setAnchorPoint(Point(.5,0));
    switch (m_guideData->id)
    {
        case 2:
        {
            arrow->stopAllActions();
            arrow->setRotation(-90);
            Hide* hide = Hide::create();
            DelayTime* delayTime = DelayTime::create(1);

            arrow->setAnchorPoint(Point(.5,1));
            ScaleTo* scalby1 = ScaleTo::create(1, 1,1.5);
            ScaleTo* scaleBy2 = ScaleTo::create(0, 1,0.5);
            arrow->runAction(RepeatForever::create(Sequence::create(scalby1,scaleBy2,hide,delayTime,Show::create(),NULL)));
           
        }
           break;
//        case 4:
//            
//            {
//                arrow->setAnchorPoint(Point(.5,1));
//                arrow->stopAllActions();
//                arrow->setRotation(180);
//                FadeOut* hide = FadeOut::create(.2);
//                DelayTime* delayTime = DelayTime::create(.5);
//                
//                ScaleTo* scalby1 = ScaleTo::create(1, 1,1.5);
//                ScaleTo* scaleBy2 = ScaleTo::create(0, 1,0.2);
//                Sequence* sequence = Sequence::create(scalby1,scaleBy2,hide, delayTime,NULL);
//                Spawn* spawn = Spawn::create(FadeIn::create(1),sequence, NULL);
//                RepeatForever* repeat = RepeatForever::create(spawn);
//
//                arrow->runAction(repeat);
//            }
//            break;
        default:
            if(skillArrow && skillArrow->getParent())
            {
                skillArrow->removeFromParent();
                skillArrow = NULL;
            }
            
            break;
    }
    if(skillArrow && skillArrow->isVisible())
    {
        skillArrow->stopAllActions();
        MoveBy* moveBy1 = MoveBy::create(1, cp);
        MoveTo* moveTo = MoveTo::create(0, this->arrow->getPosition());
        Sequence* action = Sequence::create(moveBy1,moveTo, NULL);
        skillArrow->runAction(RepeatForever::create(action));
        arrow->setVisible(false);
    }
}
void GuideScene::setScaleMode()
{

    if(m_guideData->bottom)
    {
        NewPlayerGuild::getInstance()->alignToSceneBottom();
    }
    else
    {
        NewPlayerGuild::getInstance()->alignToSceneCenter();
        
    }
}

void GuideScene::onEnter()
{

    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void GuideScene::onExit()
{
    BaseLayer::onExit();
    setAbleTouch();
}
void GuideScene::onExitTransitionDidStart()
{
    this->setClickEnabled(false);
    BaseLayer::onExitTransitionDidStart();
    if(handEffect)
    {
        handEffect->pause();
    }
}
void GuideScene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void GuideScene::setAbleTouch()
{
      isAbleClick = true;
}
void GuideScene::setTouchIsAllow(Point point)
{
    isClickArea = false;
    m_eventDispatcher->setSwallowTouches(true);
    Point cp = convertToNodeSpace(point);
 
    if(handEffect && m_guideData && m_guideData->arrow >= 1 && isAbleClick)
    {

        DrawNode* drawNode = this->getDrawNode();
        drawNode->setPosition(handEffect->getPosition());
        Rect rect = drawNode->getBoundingBox();
      
        if(handEffect->isVisible() && rect.containsPoint(cp))
        {
            m_eventDispatcher->setSwallowTouches(false);
            isAbleClick = false;
            DelayTime* delay = DelayTime::create(1);
            CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(GuideScene::setAbleTouch, this));
            this->stopAllActions();
            this->runAction(Sequence::create(delay,callBack, NULL));
            cp = this->convertToNodeSpace(cp);
            log("可点击");
            isClickArea = true;
        }
        else
        {
            m_eventDispatcher->setSwallowTouches(true);
            log("不可点击111");
        }
    }
    else
    {
        log("不可点击2222");
     
        m_eventDispatcher->setSwallowTouches(true);
    }
}
bool GuideScene::onTouchBegan(Touch *touch, Event *unused_event)
{
 
    if(m_guideData)
    {
        setTouchIsAllow(touch->getLocation());
        
        return true;
    }
    return false;
}
void GuideScene::onTouchMoved(Touch *touch, Event *unused_event)
{

}


void GuideScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(m_guideData == NULL)
    {
        NewPlayerGuild::getInstance()->next();
        return;
    }
    if(m_guideData)
    {
        if( m_guideData->arrow == 0)
        {//如果没有箭头指引，则自动下一步
            int functionID = m_guideData->goFunction;
            if(functionID == 0)
            {
                NewPlayerGuild::getInstance()->next();
            }
            else if(functionID > 0)
            {
                NewPlayerGuild::getInstance()->next();
                GotoModule::gotoModuleByFunctionID(functionID, SCENE_TAG_MAINUI);
            }
           
        }
        else if(m_guideData->arrow == 2)
        {
            if(handEffect && m_guideData && m_guideData->arrow >= 1)
            {
                Point cp = convertToNodeSpace(touch->getLocation());
                Rect rect = this->handEffect->getBoundingBox();
                if(m_guideData->id == 4)
                {
                    return;
                }
                if(handEffect->isVisible() && rect.containsPoint(cp))
                {
                     NewPlayerGuild::getInstance()->next();
                }
                else
                {
                    setClipNode();
                }
             
            }
        }
        else if(m_guideData->arrow == 3)//任意处下一步
        {
             NewPlayerGuild::getInstance()->next();
        }
        else if(m_guideData->arrow == 1)
        {
//            if(m_guideData->bottomId > 0 && GuideButtonManager::getInstance()->getButton(m_guideData->bottomId) == NULL)
//            {
//                NewPlayerGuild::getInstance()->next();
//            }
            if(m_guideData->bottomId == 0 && isClickArea)
            {
                NewPlayerGuild::getInstance()->next();
            }
            if(!isClickArea)
            {
                 setClipNode();
            }
          
        }
    }

}