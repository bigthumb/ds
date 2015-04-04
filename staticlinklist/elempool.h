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

// 静态链表的简单演示，初始化时，分配固定大小的数组，用于存放元素，能够通过索引访问元素数据

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
    int capacity() const;           // 分配的存储空间大小，即存放元素的个数（包括头结点）
    int malloc();                   // 返回分配结点的索引
    void free(int i);               // 回收索引为i的结点
    ElemType& item(int i);          // 访问索引为i的结点的数据
private:
    const int   m_c;
    Item*       m_list;             // 备用的链表的头结点
};

//--------------------------------------------------------------------------
#endif /* __ELEMPOOL_H__ */
