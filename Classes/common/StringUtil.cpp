#include <string>

#include "StringUtil.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "../../../iconv/include/iconv.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "iconv.h"
HFONT StringUtil::m_hFont = 0;
#elif(CC_TARGT_PLATFORM == CC_PLATFORM_IOS)
#include <iconv.h>

#endif


using namespace std;



std::string StringUtil::urlencode(std::string str_source)
{
    char const *in_str = str_source.c_str();
    int in_str_len = strlen(in_str);
    int out_str_len = 0;
    std::string out_str;
    register unsigned char c;
    unsigned char *to, *start;
    unsigned char const *from, *end;
    unsigned char hexchars[] = "0123456789ABCDEF";
    
    from = (unsigned char *) in_str;
    end = (unsigned char *) in_str + in_str_len;
    start = to = (unsigned char *) malloc(3 * in_str_len + 1);
    
    while (from < end) {
        c = *from++;
        
        if (c == ' ') {
            *to++ = '+';
        } else if ((c < '0' && c != '-' && c != '.') || (c < 'A' && c > '9')
                   || (c > 'Z' && c < 'a' && c != '_') || (c > 'z' && c != '~')) {
            to[0] = '%';
            to[1] = hexchars[c >> 4];
            to[2] = hexchars[c & 15];
            to += 3;
        } else {
            *to++ = c;
        }
    }
    *to = 0;
    
    out_str_len = to - start;
    out_str = (char *) start;
    free(start);
    return out_str;
}

int StringUtil::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)  
{  
//	iconv_t cd;  
//	const char *temp = inbuf;
//    char **pin = (char**)&temp;
//
//	
//	char **pout = &outbuf;  
//	memset(outbuf,0,outlen);  
//	cd = iconv_open(to_charset,from_charset);  
//	if(cd==0) return -1;  
//	if(iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;  
//	iconv_close(cd);  
//	return 0;  
}

/*UTF8תΪGB2312*/  
std::string StringUtil::u2a(const char *inbuf)  
{  
	size_t inlen = strlen(inbuf);  
	char * outbuf = new char[inlen * 2 + 2];  
	std::string strRet;  
	if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)  
	{  
		strRet = outbuf;  
	}  
	else
	{
		strRet = inbuf; 
	}
	delete [] outbuf;  
	return strRet;  
}

/*GB2312תΪUTF8*/  
std::string StringUtil::a2u(const char *inbuf)  
{
    size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];  
	std::string strRet;  
	if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)  
	{  
		strRet = outbuf;  
	}  
	else
	{
		strRet = inbuf;
	}
	delete [] outbuf;
	return strRet;  
} 

vector<string> StringUtil::split(const string& s, const string& delim)
{
	vector<string> ret;
	string::size_type posend = 0, posbegin = 0, delimlen = delim.length();
	for(posend = s.find(delim); string::npos != posend; posend = s.find(delim, posend))
	{
		ret.push_back(s.substr(posbegin, posend-posbegin));
		posbegin = posend = posend + delimlen;
	}
	ret.push_back(s.substr(posbegin));
	return ret;
}

string StringUtil::trim(const string& s)
{
	string::size_type posleft = s.find_first_not_of(' ');
	if (posleft != string::npos)
	{
		string::size_type posright = s.find_last_not_of(' ');
		if (posright != string::npos)
			return s.substr(posleft, posright - posleft + 1);
		return s.substr(posleft);
	}
	return s;
}

string StringUtil::replace(string s,  const string& olds, const string& news)
{
	if(olds != news)
	{
		string::size_type pos = 0, oldslen = olds.length();
		for(pos = s.find(olds); string::npos != pos; pos = s.find(olds, pos+oldslen))
			s.replace(pos, oldslen, news);
	}
	return s;
}

bool StringUtil::number(const string& s)
{
	try
	{
		stringstream streamIn(s);
		int tmp = 0;
		streamIn>>tmp;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

#include <cstring>
#include <cstdlib>

static unsigned char utf8_look_for_table[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
};

#define UTF8LEN(_X_) utf8_look_for_table[(_X_)]

int StringUtil::str_utf8_char_len(unsigned char ch)
{
	return (int)(UTF8LEN((ch)));
}

int StringUtil::str_utf8_len(const char* p_str)
{
	char* str = (char*) p_str;
	int clen = strlen(p_str);
	int len = 0;
    
	for(char *ptr = str;
		*ptr != 0 && len < clen;
		len++,
		ptr += UTF8LEN(((unsigned char)*ptr))
        );
    
	return len;
}

char* StringUtil::sub_utf8_str(const char* p_str, unsigned int start, unsigned int end)
{
	int len = str_utf8_len(p_str);
	char* str = (char*) p_str;
    
	if( (int)start >= len ) return NULL;
	if( (int)end > len ) end = len;
    
	char *sptr = str;
	for(int i = 0; i < (int)start; ++i,sptr += utf8_look_for_table[(unsigned char)*sptr]);
    
	char *eptr = sptr;
	for(int i = start; i < (int)end; ++i,eptr += utf8_look_for_table[((unsigned char)*eptr)]);
    
	int retLen = eptr - sptr;
	char *retStr = new char[(retLen + 1)];
	memcpy(retStr, sptr, retLen);
	retStr[retLen] = '\0';
    
	return retStr;
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

HDC StringUtil::m_hDC = NULL;

HDC StringUtil::getHDCInstance()
{
	if (!m_hDC)
	{
		HWND m_hWnd = NULL;
		HDC hdc = GetDC(m_hWnd);
		m_hDC = CreateCompatibleDC(hdc);
		ReleaseDC(m_hWnd,hdc);
	}

	return m_hDC;
}
SIZE StringUtil::sizeWithText2(const wchar_t * pszText, int nLen,HFONT _font)
{
	SIZE tRet = {0};
	do 
	{
		CC_BREAK_IF(! pszText || nLen <= 0);

		RECT rc = {0, 0, 0, 0};
		DWORD dwCalcFmt = DT_CALCRECT;

		
		// use current font to measure text extent
		HGDIOBJ hOld = SelectObject(StringUtil::getHDCInstance(), _font);

		// measure text size
		DrawTextW(StringUtil::getHDCInstance(), pszText, nLen, &rc, dwCalcFmt);
		SelectObject(StringUtil::getHDCInstance(), hOld);

		tRet.cx = rc.right;
		tRet.cy = rc.bottom;
	} while (0);

	return tRet;
}

#endif

Size StringUtil::calculateStringWidth(const string &str,const string &inFontName ,int fontSize)
{
	Size ret;
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto label = LabelTTF::create(str, inFontName, fontSize);
    ret = label->getContentSize();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto label = LabelTTF::create(str, inFontName, fontSize);
    ret = label->getContentSize();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//find font object
	const char* pszText = str.c_str();
	std::string fontName = inFontName;
	std::string fontPath;
	HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	LOGFONTA    tNewFont = {0};
	LOGFONTA    tOldFont = {0};
	GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);
	if (fontName.c_str())
	{    
		// create font from ttf file
		int nFindttf = fontName.find(".ttf");
		int nFindTTF = fontName.find(".TTF");
		if (nFindttf >= 0 || nFindTTF >= 0)
		{
			fontPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fontName.c_str());
			int nFindPos = fontName.rfind("/");
			fontName = &fontName[nFindPos+1];
			nFindPos = fontName.rfind(".");
			fontName = fontName.substr(0,nFindPos);                
		}
		tNewFont.lfCharSet = DEFAULT_CHARSET;
		strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());
	}
	if (fontSize)
	{
		tNewFont.lfHeight = -fontSize;
	}
	if(m_hFont)
	{
		GetObjectA(m_hFont, sizeof(tOldFont), &tOldFont);
	}
	
	// disable Cleartype
	tNewFont.lfQuality = ANTIALIASED_QUALITY;

	if(tOldFont.lfHeight != tNewFont.lfHeight
		|| 0 != strcmp(tOldFont.lfFaceName, tNewFont.lfFaceName))
	{
		m_hFont = NULL;
		// create new font
		m_hFont = CreateFontIndirectA(&tNewFont);
	}
	

	//test string width
	int nRet = 0;
	wchar_t * pwszBuffer = 0;
	do 
	{
		CC_BREAK_IF(! pszText);

		int nLen = strlen(pszText);
		// utf-8 to utf-16
		int nBufLen  = nLen + 1;
		pwszBuffer = new wchar_t[nBufLen];
		CC_BREAK_IF(! pwszBuffer);

		memset(pwszBuffer, 0, sizeof(wchar_t)*nBufLen);
		nLen = MultiByteToWideChar(CP_UTF8, 0, pszText, nLen, pwszBuffer, nBufLen);

		SIZE newSize = sizeWithText2(pwszBuffer, nLen,m_hFont);

		ret.width = newSize.cx;
		ret.height = newSize.cy;
	}while (false);


	
#else
	
#endif

	return ret;
}


vector<char*> StringUtil::splitString( const string &str,const string fontName,int fontSize,int width)
{
	vector<char*> vec;

	//////////////////////////
	string text = str;
	const char* cstr = text.c_str();
	int lineStart = 0;
	int lineWid = 0;
	int charCount = str_utf8_len(cstr);

	// Loop to break the text into lines.
	int i = 0;

	while (i < charCount) {
		char* ch = sub_utf8_str(cstr,i,i+1);

		if (strcmp(ch,"\n") == 0) {
			// If new line is found, record current line information and
			// step to next line.
			char* ch1 = sub_utf8_str(cstr,i-1,i);
			if (i > 0 && strcmp(ch1,"\r") == 0) {
				vec.push_back(sub_utf8_str(cstr,lineStart,i-1));
			} else {
				vec.push_back(sub_utf8_str(cstr,lineStart,i));
			}

			lineStart = i + 1;
			lineWid = 0;
		} else {
			Size charWid = calculateStringWidth(ch,fontName,fontSize);

			if (lineWid == 0 || lineWid + charWid.width <= width) {
				lineWid += charWid.width;
			} else {
				vec.push_back(sub_utf8_str(cstr,lineStart,i));
				lineStart = i;
				lineWid = charWid.width;
			}
		}

		i++;
	}

	// Handle the last line.
	if (lineWid > 0) {
		vec.push_back(sub_utf8_str(cstr,lineStart,charCount));
	}


	///////////////////////////


	return vec;
}

