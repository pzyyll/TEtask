#include "MyCache.h"
#include <iostream>
#include <cstring>

MyCache::MyCache() : pBuffer(nullptr), bufSize(131072), pos(0), mCount(0)
{
}

MyCache::~MyCache()
{
    deinit();
}

void MyCache::init()
{
    pBuffer = new char[bufSize]();
}

void MyCache::deinit()
{
    if (pBuffer != nullptr) {
        delete [] pBuffer;
        pBuffer = nullptr;
    }
}

void MyCache::setsize(const size_t msize)
{
    bufSize = msize;
    init();
}

size_t MyCache::maxsize()
{
    return bufSize;
}

ssize_t MyCache::read(void *pBuf, size_t cnt)
{
    ssize_t rsize = 0;

    if (mCount == 0) {
        rsize = -1;
    } else if (cnt >= mCount) {
        rsize = processRead((char *)pBuf, mCount);
    } else {
        rsize = processRead((char *)pBuf, cnt);
    }

    return rsize;
}

ssize_t MyCache::write(const void *pBuf, size_t cnt)
{
    if (bufSize - mCount < cnt) {
        return -1;
    }

    //缓存区中空闲的第一个位置；
    size_t np = (pos + mCount) % bufSize;

    //判断到缓存区尾部的空间是否可容纳下数据
    if (np + cnt <= bufSize) {
        memcpy(pBuffer + np, pBuf, cnt);
    } else {
        size_t firsWriteSize = bufSize - np;
        memcpy(pBuffer + np, pBuf, firsWriteSize);
        np = 0;

        size_t secWriteSize = cnt - firsWriteSize;
        memcpy(pBuffer + np, pBuf, secWriteSize);
    }

    mCount += cnt;

    return cnt;
}

ssize_t MyCache::processRead(char *pChar, size_t cnt)
{
    size_t tailPos = pos + cnt;
    if (tailPos <= bufSize) {

        memcpy(pChar, pBuffer + pos, cnt);

        pos += cnt;
        if (pos == bufSize)         //循环使用缓存区
            pos = 0;
    } else {
        size_t pChar_CurrPos = 0;
        size_t firstReadSize = bufSize - pos;

        memcpy(pChar, pBuffer + pos, firstReadSize);

        pos = 0;
        mCount -= firstReadSize;
        pChar_CurrPos = firstReadSize;

        size_t secReadSize = cnt - firstReadSize;

        memcpy(pChar + pChar_CurrPos, pBuffer + pos, secReadSize);

        pos += secReadSize;
    }
    mCount -= cnt;

    return (ssize_t)cnt;
}

