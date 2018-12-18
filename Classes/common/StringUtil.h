#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <string>
#include <vector>
using namespace std;
#include "cocos2d.h"
USING_NS_CC;
class StringUtil {
public:
    static std::string urlencode(std::string str_source);
	static int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
	//unicodeתutf8
	static std::string a2u(const char *inbuf);
	//utf8תunicode
	static std::string u2a(const char *inbuf);

	static vector<string> split(const string& s, const string& delim);
	static string trim(const string& s);
	static string replace(string s, const string& olds, const string& news);
	static bool number(const string& s);
	static int str_utf8_char_len(unsigned char ch);
    
    static int str_utf8_len(const char* p_str);
    
    static char* sub_utf8_str(const char* p_str, unsigned int start, unsigned int end);
	static Size calculateStringWidth( const string &str,const string &fontName ,int fontSize);
	static vector<char*> splitString(const string &str,const string fontName,int fontSize,int width);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static HDC getHDCInstance();
	static SIZE sizeWithText2(const wchar_t * pszText, int nLen,HFONT _font);
	static HDC m_hDC;//   = CreateCompatibleDC(hdc);
	static HFONT m_hFont;
#endif
};



#define utf8(str) StringUtil::a2u(str).c_str()

#define utf8s(str) StringUtil::a2u(str)

#define CCLOG_UTF8(str) CCLOG(StringUtil::a2u(str).c_str())

#endif