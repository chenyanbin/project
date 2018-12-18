//
//  DynamicallyCreateObj.h
//
//  动态创建对像
//
//  Created by 孙宏利 on 14-4-7.
//
//

#ifndef IpGame_DynamicallyCreateObj_h
#define IpGame_DynamicallyCreateObj_h

#include <map>
#include <string>
using namespace std;


// 声明具有动态创建的基类
#define DECLEAR_DYNCRT_BASE(CBase) \
public: \
typedef CBase *(*ClassGen)(); /* 声明函数指针*/ \
static CBase *Create(const string &class_name) /* 工厂函数 */ \
{ \
    std::map<string, ClassGen>::iterator iter = m_class_set.find(class_name); \
    if (m_class_set.end() != iter) \
    { \
        return ((*iter).second)(); \
    } \
    return NULL; \
} \
protected: \
static void Register(const string &class_name, ClassGen class_gen) /* 注册函数 */ \
{ \
    m_class_set.insert(map<string, ClassGen>::value_type(class_name, class_gen)); \
} \
static std::map<string, ClassGen> m_class_set; /* 存储子类信息 */

// 用于声明一个能够被动态创建的类(用一个全局对象进行注册)
#define DECLEAR_DYNCRT_CLASS(CDerived, CBase) \
public: \
struct CDerived##Register /* 辅助类，用于注册 */ \
{ \
CDerived##Register() \
{ \
static bool bRegistered = false; /* 注册子类，虽然map能保证唯一，但仍只注册一次 */ \
if(!bRegistered) \
{ \
CBase::Register(#CDerived, CDerived::Create); /* 注册子类信息 */ \
bRegistered = true; \
} \
} \
} ; \
static CBase *Create() /* 工厂函数 */ \
{ \
return new CDerived; \
} \
static struct CDerived##Register m_t##CDerived##Register;

// 用于实现基类
#define IMPLEMENT_DYNCRT_BASE(CBase)  \
std::map<string, CBase::ClassGen> CBase::m_class_set;

// 用于实现一个能被动态创建的类
#define IMPLEMENT_DYNCRT_CLASS(CDerived) \
static CDerived::CDerived##Register m_t##CDerived##Register;
#endif
