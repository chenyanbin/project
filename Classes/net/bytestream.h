#ifndef __BYTESTREAM_H__
#define __BYTESTREAM_H__

#include <iostream>
#include <stdint.h>
/**
 *  此类基本功能将c++基本数据类型转换成Byte
 */
class ByteStream
{
public:
    
	ByteStream();
	ByteStream(int size);
	ByteStream(uint8_t* buf, int size, bool autorelease = true);
	~ByteStream();

public:
    
	void   setPosition(int position);
	int    position();
	int    length();
	size_t availableSize();
	void   skip(int bytes);
	uint8_t* getBuf();

public:
	void put(uint8_t byte);
	void putShort(int16_t v);
	void putInt(int32_t v);
	void putLong(int64_t v);
	void putBytes(const uint8_t* byte, int len);
	void putFloat(float floatValue);
	void putDouble(double doubleValue);
	void putUTF8(const char* str);
    void putUTF16BE(const char* str);

public:
	uint8_t get();
	int8_t	getByte();
	uint8_t getUByte();
	int16_t getShort();
	int32_t getInt();
	int64_t getLong();
	float	getFloat();
	double	getDouble();
	char*	getUTF8();
	char*	getUTF8(int32_t& len);
	void	getBytes(uint8_t* buf, int32_t len);
	void	getInts(int32_t *buf, int32_t len);

public:
    
    int32_t _count;
    int32_t _size;
    uint8_t* _buf;
	bool _autorelease;
    
private:
    
	void ensureCapacity(int newsize);
	bool checkSize(int readSize);
	static int32_t floatToIntBits(float value);
	static int64_t doubleToLongBits(double value);
    
};


//java value storage

typedef int32_t jint;
typedef int64_t jlong;
typedef signed char jbyte;

typedef unsigned char   jboolean;
typedef unsigned short  jchar;
typedef short           jshort;
typedef float           jfloat;
typedef double          jdouble;

typedef jint            jsize;

typedef unsigned char jubyte;
typedef jubyte u_char;

class JavaValue {

public:
	typedef union JavaCallValue {
		jfloat   f;
		jdouble  d;
		jint     i;
		jlong    l;
	} JavaCallValue;
    JavaValue()
    {
    };
    ~JavaValue()
    {
    }
private:
	JavaCallValue _value;

public:
	jfloat get_jfloat() const { return _value.f; }
	jdouble get_jdouble() const { return _value.d; }
	jint get_jint() const { return _value.i; }
	jlong get_jlong() const { return _value.l; }
	JavaCallValue* get_value_addr() { return &_value; }

	void set_jfloat(jfloat f) { _value.f = f;}
	void set_jdouble(jdouble d) { _value.d = d;}
	void set_jint(jint i) { _value.i = i;}
	void set_jlong(jlong l) { _value.l = l;}

	jboolean get_jboolean() const { return (jboolean) (_value.i);}
	jbyte get_jbyte() const { return (jbyte) (_value.i);}
	jchar get_jchar() const { return (jchar) (_value.i);}
	jshort get_jshort() const { return (jshort) (_value.i);}

};

#endif
