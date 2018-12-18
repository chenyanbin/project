// Code by Francois Guibert  
// Contact: www.frozax.com - http://twitter.com/frozax - www.facebook.com/frozax  
  
  
#include "shake.h"  

// not really useful, but I like clean default constructors  
Shake::Shake() : m_strength_x(0), m_strength_y(0), m_initial_x(0), m_initial_y(0)
{  
}  
  
Shake* Shake::create( float d, float strength )
{  
    // call other construction method with twice the same strength  
    return createWithStrength( d, strength, strength );  
}  
  
Shake* Shake::createWithStrength(float duration, float strength_x, float strength_y)
{  
    Shake *pRet = new Shake();
      
    if (pRet && pRet->initWithDuration(duration, strength_x, strength_y))  
    {  
        pRet->autorelease();  
    }  
    else  
    {  
        CC_SAFE_DELETE(pRet);
        pRet = NULL;
    }  
      
      
    return pRet;  
}  
  
bool Shake::initWithDuration(float duration, float strength_x, float strength_y)
{  
    if (ActionInterval::initWithDuration(duration))  
    {  
        m_strength_x = strength_x;  
        m_strength_y = strength_y;  
        return true;  
    }  
      
    return false;  
}  
  
// Helper function. I included it here so that you can compile the whole file  
// it returns a random value between min and max included  
static float fgRangeRand( float min, float max )  
{  
    float rnd = ((float)rand()/(float)RAND_MAX);  
    return rnd*(max-min)+min;  
}  
  
void Shake::update(float dt)
{  
    float randx = fgRangeRand( -m_strength_x, m_strength_x )*dt;  
    float randy = fgRangeRand( -m_strength_y, m_strength_y )*dt;  
      
    // move the target to a shaked position  
    _target->setPosition( Point(m_initial_x, m_initial_y) + Point( randx, randy));  
}  
  
void Shake::startWithTarget(Node *pTarget)
{  
    ActionInterval::startWithTarget( pTarget );  
      
    // save the initial position  
    m_initial_x = pTarget->getPosition().x;  
    m_initial_y = pTarget->getPosition().y;  
}  
  
void Shake::stop(void)
{  
    // Action is done, reset clip position  
    this->getTarget()->setPosition( Point( m_initial_x, m_initial_y ) );  
      
    ActionInterval::stop();  
}  
//---------------------------------------------------------------------------------------------------
// not really useful, but I like clean default constructors  
ShakeDown::ShakeDown()
	:m_initial_x(0), m_initial_y(0) ,m_height(0)
{
}

ShakeDown* ShakeDown::create( float duration, float height )
{  
	ShakeDown *pRet = new ShakeDown();
	if (pRet && pRet->initWithDuration(duration, height))
		pRet->autorelease();
	else
		CC_SAFE_DELETE(pRet);
	return pRet;  
}

bool ShakeDown::initWithDuration(float duration, float height)
{  
	m_height = height;
	if (ActionInterval::initWithDuration(duration))
		return true;
	return false;  
}

void ShakeDown::update(float time)
{
	/*float y = 0;
	if(time < 1.0f / SHAKEDOWN_FACTOR)
		y = -m_height / (1.0f/SHAKEDOWN_FACTOR) * time;
	else
		y = -m_height / ((SHAKEDOWN_FACTOR-1)/SHAKEDOWN_FACTOR) * (1.0f-time);*/

	float y = 0.0f;
	if(time <= 0.2f)
		y = m_height * (time / 0.2f);
	else if(time <= 0.5f)
		y = m_height*0.2f + m_height*0.8f * ((0.5f-time) / 0.3f);
	else 
		y = m_height*0.2f * ((1.0f-time) / 0.5);

	if(_target->getPositionY() >= m_initial_y)
		y = -y;
	_target->setPosition( Point(m_initial_x, m_initial_y) + Point(0, y));
}

void ShakeDown::startWithTarget(Node *pTarget)
{  
	ActionInterval::startWithTarget(pTarget);
	m_initial_x = pTarget->getPosition().x;
	m_initial_y = pTarget->getPosition().y;
}
void ShakeDown::stop(void)
{  
	// Action is done, reset clip position  
	this->getTarget()->setPosition( Point( m_initial_x, m_initial_y ) );  

	ActionInterval::stop();  
}  

// not really useful, but I like clean default constructors  
ShakeUpDown::ShakeUpDown()
	:m_initial_x(0), m_initial_y(0) ,m_height(0)
{
}

ShakeUpDown* ShakeUpDown::create( float duration, float height )
{  
	ShakeUpDown *pRet = new ShakeUpDown();
	if (pRet && pRet->initWithDuration(duration, height))
		pRet->autorelease();
	else
		CC_SAFE_DELETE(pRet);
	return pRet;  
}

bool ShakeUpDown::initWithDuration(float duration, float height)
{  
	m_height = height;
	if (ActionInterval::initWithDuration(duration))
		return true;
	return false;  
}

void ShakeUpDown::update(float time)
{
	float y = 0.0f;
	if(time <= 0.2f)
		y = m_height * (time / 0.2f);
	else if(time <= 0.4f)
		y = m_height*0.5f + m_height*0.5f * ((0.4f-time) / 0.2f);
	else if(time <= 0.6f)
		y = m_height*0.25f + m_height*0.25f * ((0.6f-time) / 0.2f);
	else 
		y = m_height*0.25f * ((1.0f-time) / 0.4);

	/*
	if(time <= 0.2f)
		y = m_height * (time / 0.2f);
	else if(time <= 0.3f)
		y = m_height;
	else 
		y = m_height * ((1.0f-time) / 0.6);*/

	if(_target->getPositionY() >= m_initial_y)
		y = -y;

	_target->setPosition( Point(m_initial_x, m_initial_y) + Point(0, y));
}

void ShakeUpDown::startWithTarget(Node *pTarget)
{  
	ActionInterval::startWithTarget(pTarget);
	m_initial_x = pTarget->getPosition().x;
	m_initial_y = pTarget->getPosition().y;
}

void ShakeUpDown::stop(void)  
{  
	// Action is done, reset clip position  
	this->getTarget()->setPosition( Point( m_initial_x, m_initial_y ) );  

	ActionInterval::stop();  
}  

//---------------------------------------------------------------------------------------------------