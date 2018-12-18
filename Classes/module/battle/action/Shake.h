#ifndef __SHAKE_H__  
#define __SHAKE_H__
  
#include "cocos2d.h"
USING_NS_CC;
class Shake : public ActionInterval
{  
    // Code by Francois Guibert  
    // Contact: www.frozax.com - http://twitter.com/frozax - www.facebook.com/frozax  
public:  
    Shake();
      
    // Create the action with a time and a strength (same in x and y)  
    static Shake* create(float d, float strength );
    // Create the action with a time and strengths (different in x and y)  
    static Shake* createWithStrength(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );  
      
protected:  
	virtual Shake* reverse() const override {return NULL;};
	virtual Shake* clone() const override {return NULL;};
    void startWithTarget(cocos2d::Node *pTarget);  
    void update(float time);  
    void stop(void);  
      
      
    // Initial position of the shaked node  
    float m_initial_x, m_initial_y;  
    // Strength of the action  
    float m_strength_x, m_strength_y;  
};  

//---------------------------------------------------------------------------------------------
#define SHAKEDOWN_FACTOR 5.0f	// 如配置为5即在1/5处达到峰值
class ShakeDown : public cocos2d::ActionInterval
{
public:
	ShakeDown();

	static ShakeDown* create(float duration, float height);
	bool initWithDuration(float duration, float height);

protected:
	virtual ShakeDown* reverse() const override {return NULL;};
	virtual ShakeDown* clone() const override {return NULL;};
	void startWithTarget(cocos2d::Node *pTarget);
	void update(float time);
	void stop(void);  

private:
	float m_initial_x, m_initial_y;
	float m_height;
};

#define SHAKEUPDOWN_TIME 0.2f
class ShakeUpDown : public cocos2d::ActionInterval
{
public:
	ShakeUpDown();

	static ShakeUpDown* create(float duration, float height);
	bool initWithDuration(float duration, float height);

protected:
	virtual ShakeUpDown* reverse() const override {return NULL;};
	virtual ShakeUpDown* clone() const override {return NULL;};
	void startWithTarget(cocos2d::Node *pTarget);
	void update(float time);
	void stop(void);  

private:
	float m_initial_x, m_initial_y;
	float m_height;
};
  
#endif //__SHAKE_H__
