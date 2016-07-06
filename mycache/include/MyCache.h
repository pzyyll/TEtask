#ifndef MYCACHE_H
#define MYCACHE_H

#include <cstddef>
#include <sys/types.h>

using std::size_t;

class MyCache
{
    public:
        MyCache();
        virtual ~MyCache();

        void init();
        void deinit();
        void setsize(const size_t msize);
        size_t maxsize();
        ssize_t write(const void *pBuf, size_t cnt);
        ssize_t read(void *pBuf, size_t cnt);

    private:
        //处理写操作
        ssize_t processRead(char *pChar, size_t cnt);

    private:

    char *pBuffer;
    size_t bufSize;
    size_t pos;         //缓存区首元素位置
    size_t mCount;       //缓存区当前存储字节数
};

#endif // MYCACHE_H
