//
//  CutViewLayer.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-28.
//
//

#include "CutViewLayer.h"
CutViewLayer::CutViewLayer()
:_clippingToBounds(false)
{
    
}
CutViewLayer::~CutViewLayer()
{
    
}
bool CutViewLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        bref = true;
    } while (false);
    return bref;
}
void CutViewLayer::setCutRect(Rect rect)
{
       _clippingToBounds = true;
    this->_viewSize = rect.size;
    this->_startPos = Point(rect.getMinX(),rect.getMinY());
}
void CutViewLayer::beforeDraw()
{
    _beforeDrawCommand.init(_globalZOrder);
    _beforeDrawCommand.func = CC_CALLBACK_0(CutViewLayer::onBeforeDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_beforeDrawCommand);
}

/**
 * clip this view so that outside of the visible bounds can be hidden.
 */
void CutViewLayer::onBeforeDraw()
{
    if (_clippingToBounds)
    {
		_scissorRestored = false;
        Rect frame = getViewRect();
        auto glview = Director::getInstance()->getOpenGLView();
        
        if (glview->isScissorEnabled()) {
            _scissorRestored = true;
            _parentScissorRect = glview->getScissorRect();
            //set the intersection of _parentScissorRect and frame as the new scissor rect
            if (frame.intersectsRect(_parentScissorRect)) {
                float x = MAX(frame.origin.x, _parentScissorRect.origin.x);
                float y = MAX(frame.origin.y, _parentScissorRect.origin.y);
                float xx = MIN(frame.origin.x+frame.size.width, _parentScissorRect.origin.x+_parentScissorRect.size.width);
                float yy = MIN(frame.origin.y+frame.size.height, _parentScissorRect.origin.y+_parentScissorRect.size.height);
                glview->setScissorInPoints(x, y, xx-x, yy-y);
            }
        }
        else {
            glEnable(GL_SCISSOR_TEST);
            glview->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
        }
    }
}

void CutViewLayer::afterDraw()
{
    _afterDrawCommand.init(_globalZOrder);
    _afterDrawCommand.func = CC_CALLBACK_0(CutViewLayer::onAfterDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_afterDrawCommand);
}

/**
 * retract what's done in beforeDraw so that there's no side effect to
 * other nodes.
 */
void CutViewLayer::onAfterDraw()
{
    if (_clippingToBounds)
    {
        if (_scissorRestored) {//restore the parent's scissor rect
            auto glview = Director::getInstance()->getOpenGLView();
            
            glview->setScissorInPoints(_parentScissorRect.origin.x, _parentScissorRect.origin.y, _parentScissorRect.size.width, _parentScissorRect.size.height);
        }
        else {
            glDisable(GL_SCISSOR_TEST);
        }
    }
}

void CutViewLayer::visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated)
{
	// quick return if not visible
	if (!isVisible())
    {
		return;
    }
    
    bool dirty = parentTransformUpdated || _transformUpdated;
    if(dirty)
        _modelViewTransform = this->transform(parentTransform);
    _transformUpdated = false;
    
    // IMPORTANT:
    // To ease the migration to v3.0, we still support the kmGL stack,
    // but it is deprecated and your code should not rely on it
    kmGLPushMatrix();
    kmGLLoadMatrix(&_modelViewTransform);
    
    this->beforeDraw();
    
	if (!_children.empty())
    {
		int i=0;
		
		// draw children zOrder < 0
		for( ; i < _children.size(); i++ )
        {
			Node *child = _children.at(i);
			if ( child->getLocalZOrder() < 0 )
            {
				child->visit(renderer, _modelViewTransform, dirty);
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw(renderer, _modelViewTransform, dirty);
        
		// draw children zOrder >= 0
		for( ; i < _children.size(); i++ )
        {
			Node *child = _children.at(i);
			child->visit(renderer, _modelViewTransform, dirty);
		}
        
	}
    else
    {
		this->draw(renderer, _modelViewTransform, dirty);
    }
    
    this->afterDraw();
    
	kmGLPopMatrix();
}
Rect CutViewLayer::getViewRect()
{
    Point screenPos = this->convertToWorldSpace(_startPos);
    
    float scaleX = this->getScaleX();
    float scaleY = this->getScaleY();
    
    for (Node *p = _parent; p != NULL; p = p->getParent()) {
        scaleX *= p->getScaleX();
        scaleY *= p->getScaleY();
    }
    
    // Support negative scaling. Not doing so causes intersectsRect calls
    // (eg: to check if the touch was within the bounds) to return false.
    // Note, Node::getScale will assert if X and Y scales are different.
    if(scaleX<0.f) {
        screenPos.x += _viewSize.width*scaleX;
        scaleX = -scaleX;
    }
    if(scaleY<0.f) {
        screenPos.y += _viewSize.height*scaleY;
        scaleY = -scaleY;
    }
    
    return Rect(screenPos.x, screenPos.y, _viewSize.width*scaleX, _viewSize.height*scaleY);
}
