//
//  CutViewLayer.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-28.
//
//

#ifndef __SuiTang__CutViewLayer__
#define __SuiTang__CutViewLayer__

#include "cocos2d.h"
USING_NS_CC;
class CutViewLayer:public Layer
{
public:
    CutViewLayer();
    ~CutViewLayer();
    virtual bool init();
    virtual void visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated) override;
    void setCutRect(Rect rect);
protected:
    void beforeDraw();
    void onBeforeDraw();
    void afterDraw();
    void onAfterDraw();
    Rect getViewRect();
protected:
    CustomCommand _beforeDrawCommand;
    CustomCommand _afterDrawCommand;
    Size _viewSize;
    Point _startPos;
    bool _clippingToBounds;
    /**
     * scissor rect for parent, just for restoring GL_SCISSOR_BOX
     */
    Rect _parentScissorRect;
    bool _scissorRestored;
    
};

#endif /* defined(__SuiTang__CutViewLayer__) */
