/* -------------------------------------------------------------------------
//  File Name   :   elempool.h
//  Author      :   bigthumb
//  Create Time :   2015-3-21 13:15:06
//  Description :
//
// -----------------------------------------------------------------------*/

#ifndef __ELEMPOOL_H__
#define __ELEMPOOL_H__

//-------------------------------------------------------------------------

// ��̬����ļ���ʾ����ʼ��ʱ������̶���С�����飬���ڴ��Ԫ�أ��ܹ�ͨ����������Ԫ������

typedef char ElemType;

class ElemPool
{
protected:
    struct Item
    {
        ElemType data;
        int      next;
    };
public:
    ElemPool(int capacity);
    ~ElemPool();
public:
    int capacity() const;           // ����Ĵ洢�ռ��С�������Ԫ�صĸ���������ͷ��㣩
    int malloc();                   // ���ط����������
    void free(int i);               // ��������Ϊi�Ľ��
    ElemType& item(int i);          // ��������Ϊi�Ľ�������
private:
    const int   m_c;
    Item*       m_list;             // ���õ������ͷ���
};

//--------------------------------------------------------------------------
#endif /* __ELEMPOOL_H__ */
