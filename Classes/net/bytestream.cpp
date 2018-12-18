#include "bytestream.h"
#include <stdio.h>
ByteStream::ByteStream()
	: _count(0), _size(0), _buf(NULL), _autorelease(true)
{
}

ByteStream::ByteStream(int size)
	: _count(0), _size(size), _buf(new uint8_t[size]), _autorelease(true)
{
    memset(_buf, 0, sizeof(uint8_t) * size);
}

ByteStream::ByteStream(uint8_t* buf, int size, bool autorelease)
	: _count(0), _size(size), _buf(buf), _autorelease(autorelease)
{}

ByteStream::~ByteStream()
{
	if(_autorelease)
    {
//        std::cout<<"~ByteStream~ByteStream ";
        delete []_buf;
        _buf = NULL;
    }
		
}

void ByteStream::ensureCapacity(int newsize)
{
	if (newsize - _size > 0){
		int oldCapacity = _size;
		int newCapacity = oldCapacity << 1;
		if (newCapacity - newsize < 0)
			newCapacity = newsize;
		if (newCapacity < 0) {
			if (newsize < 0) // overflow
				return;
			newCapacity = INT32_MAX;
		}
		uint8_t* newBuf = new uint8_t[newCapacity];
		memset(newBuf, 0, newCapacity);
		memcpy(newBuf, _buf, oldCapacity);
		delete[] _buf;
		_buf = newBuf;
		_size = newCapacity;
	}
}

bool ByteStream::checkSize(int readSize)
{
	if(_count + readSize > _size)
		return false;
	return true;
}

void ByteStream::setPosition(int position)
{
	_count = position;
}

int ByteStream::position()
{
    
	return _count;
}

int ByteStream::length()
{
	return _size;
}

void ByteStream::put(uint8_t byte)
{
    ensureCapacity(position() + sizeof(uint8_t));
    _buf[_count++] = byte;
}

uint8_t ByteStream::get()
{
    if(!checkSize(sizeof(uint8_t)))
        return 0;
    return _buf[_count++];
}

uint8_t ByteStream::getUByte()
{
    return get();
}

int8_t ByteStream::getByte()
{
    if(!checkSize(sizeof(uint8_t)))
        return 0;
    return _buf[_count++];
}

void ByteStream::putShort(int16_t v)
{
    ensureCapacity(position() + sizeof(int16_t));
    _buf[_count++] = (v >> 8) & 0xff;
    _buf[_count++] = v & 0xff;
}

void ByteStream::putFloat(float floatValue)
{
	JavaValue v;
	v.set_jfloat(floatValue);
	int32_t intv = v.get_jint();
    std::cout<<"--------"<<intv<<std::endl;
	putInt(intv);
}

void ByteStream::putDouble(double doubleValue)
{
	putLong(doubleToLongBits(doubleValue));
}

int16_t ByteStream::getShort()
{
    if(!checkSize(sizeof(int16_t)))
        return 0;
    int16_t r1 = (int16_t)_buf[_count++] << 8;
	int16_t r2 = (int16_t)_buf[_count++];
	int16_t ret = r1 | r2;
    return ret;
}

void ByteStream::putInt(int32_t v)
{
    ensureCapacity(position() + sizeof(int32_t));
    _buf[_count++] = (v >> 24) & 0xff;
    _buf[_count++] = (v >> 16) & 0xff;
    _buf[_count++] = (v >> 8) & 0xff;
    _buf[_count++] = v & 0xff;
}

int32_t ByteStream::getInt()
{
    if(!checkSize(sizeof(int32_t)))
        return 0;
    int32_t ret = (int32_t)_buf[_count++] << 24;
    ret|= (int32_t)_buf[_count++] << 16;
    ret|= (int32_t)_buf[_count++] <<8;
    ret|= (int32_t)_buf[_count++];
    return ret;
}

void ByteStream::getInts(int32_t *buf, int32_t len)
{
	if(!checkSize(sizeof(int32_t)*len))
		return;
	for(int32_t i = 0; i < len; i++)
	{
		buf[i]  = (int32_t)_buf[_count++] << 24;
		buf[i] |= (int32_t)_buf[_count++] << 16;
		buf[i] |= (int32_t)_buf[_count++] <<8;
		buf[i] |= (int32_t)_buf[_count++];
	}
}

void ByteStream::putLong(int64_t v)
{
    ensureCapacity(position() + sizeof(int64_t));
    _buf[_count++] = (v >> 56) & 0xff;
    _buf[_count++] = (v >> 48) & 0xff;
    _buf[_count++] = (v >> 40) & 0xff;
    _buf[_count++] = (v >> 32) & 0xff;
    _buf[_count++] = (v >> 24) & 0xff;
    _buf[_count++] = (v >> 16) & 0xff;
    _buf[_count++] = (v >> 8) & 0xff;
    _buf[_count++] = v & 0xff;
}

int64_t ByteStream::getLong()
{

    if(!checkSize(sizeof(int64_t)))
        return 0;
    uint64_t ret = 0;
    ret = (int64_t)_buf[_count++] << 56;
    ret|= (int64_t)_buf[_count++] << 48;
    ret|= (int64_t)_buf[_count++] << 40;
    ret|= (int64_t)_buf[_count++] << 32;
    ret|= (int64_t)_buf[_count++] << 24;
    ret|= (int64_t)_buf[_count++] << 16;
    ret|= (int64_t)_buf[_count++] <<8;
    ret|= (int64_t)_buf[_count++];
    return ret;
}

void ByteStream::putBytes(const uint8_t *byte, int len)
{
    ensureCapacity(position() + sizeof(uint8_t)*len);
    memcpy(&_buf[position()], byte, len);
    _count += len;
}

void ByteStream::getBytes(uint8_t* buf, int len)
{
    if(!checkSize(sizeof(uint8_t)*len))
        return;
    memcpy(buf, &_buf[_count], len);
    _count += len;
}

void ByteStream::putUTF8(const char *str)
{
    int len = 0;
    int idx = 0;
    while(str[idx]!='\0'){
        len++;
        idx++;
    }
	putInt(len);
	putBytes((uint8_t*)str, len);
}

char* ByteStream::getUTF8(int32_t& len)
{
    short utfLen = getInt();
    char* utfBuffer = new char[utfLen + 1];
    if(!checkSize(utfLen)){
        utfBuffer[0] = '\0';
    }
    else
    {
        getBytes((uint8_t*)utfBuffer, utfLen);
        utfBuffer[utfLen] = '\0';
    }
    
    len = utfLen + 2;
    
    return utfBuffer;
}

//剩余可读字节数
size_t ByteStream::availableSize()
{
	size_t ret = _size - _count;

	return ret;
}

char* ByteStream::getUTF8()
{
    int len = 0;
    return getUTF8(len);
}

uint8_t* ByteStream::getBuf()
{
    uint8_t* ret = new uint8_t[_size];
    memcpy(ret, _buf, _size);
    return ret;
}

float ByteStream::getFloat()
{
	jint intv = getInt();
	JavaValue v;
	v.set_jint(intv);
	float ret = v.get_jfloat();
	return ret;

}

//bool ByteStream::getBool()
//{
//	jint intv = getInt();
//	JavaValue v;
//	v.set_jint(intv);
//	float ret = v.get_jfloat();
//	return ret;
//    
//}
double ByteStream::getDouble()
{
	jlong longv = getLong();
	JavaValue v;
	v.set_jlong(longv);
	jdouble ret = v.get_jdouble();
//    char string[12] = {0};
//    sprintf(string, "%.3f Test", ret);
    
	return ret;
}

void ByteStream::skip(int bytes)
{
	if(checkSize(bytes))
		_count += bytes;
}

# define FLOAT_EXP_BIT_MASK	0x7F800000
# define FLOAT_SIGNIF_BIT_MASK	0x007FFFFF

int32_t ByteStream::floatToIntBits(float value)
{
	JavaValue v;
	v.set_jfloat(value);
	int32_t result = v.get_jint();

    // Check for NaN based on values of bit fields, maximum
    // exponent and nonzero significand.
    if ( ((result & FLOAT_EXP_BIT_MASK) == FLOAT_EXP_BIT_MASK) &&
            (result & FLOAT_SIGNIF_BIT_MASK) != 0)
        result = 0x7fc00000;
    return result;
}

# define DOUBLE_EXP_BIT_MASK	0x7FF0000000000000L
# define DOUBLE_SIGNIF_BIT_MASK	0x000FFFFFFFFFFFFFL

int64_t ByteStream::doubleToLongBits(double value)
{
	JavaValue v;
	v.set_jdouble(value);
	int64_t result = v.get_jlong();
    std::cout<<"-----"<<result<<std::endl;
    if (result==0xFFFFFFFFFFFFFFFF) {
      std::cout<<"==="<<result<<std::endl;  
    }
    // Check for NaN based on values of bit fields, maximum
    // exponent and nonzero significand.
    if ( ((result & DOUBLE_EXP_BIT_MASK) ==DOUBLE_EXP_BIT_MASK) &&(result & DOUBLE_SIGNIF_BIT_MASK) != 0L)
    {
        result = 0x7ff8000000000000L;
    }
    
    return result;
}
