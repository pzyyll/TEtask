#ifndef MYCACHE_H
#define MYCACHE_H

#include <cstddef>
#include <sys/types.h>

//using std::size_t;

class MyCache
{
    public:
        //typedef std::size_t size_t;
        using size_t = std::size_t;

        MyCache();
        virtual ~MyCache();

        // ��ʼ����������Ҫ����ʾ���á�
        void init();
        void deinit();

        void setsize(const size_t msize);
        size_t maxsize();

        //�������ã�(pBuf, cnt: ��Ҫд������ݵ��׵�ַ���Լ��ֽ���)
        //��������ֵΪ�ɹ�д���ֽ�����ʧ������·���-1;
        ssize_t write(const void *pBuf, size_t cnt);

        // �������ã�(pBuf, cnt: �ӻ����ж�ȡ���ݺ��ŵ��������׵�ַ��
        //                       ��Ҫ���ȡ���ֽ�����������������Ч����С��Ҫ����ֽ�����
        //                       ��ֻ���ػ���������Ч���ݴ�С)
        //��������ֵΪ�ɹ���ȡ���ֽ�������ȡʧ�ܷ���-1��
        ssize_t read(void *pBuf, size_t cnt);

    private:
        //���������
        ssize_t processRead(char *pChar, size_t cnt);

    private:
        char *pBuffer;       //�������׵�ַ
        size_t bufSize;      //��������С
        size_t pos;          //��������Ч��������λ��
        size_t mCount;       //��������ǰ�洢�ֽ���
};

#endif // MYCACHE_H
