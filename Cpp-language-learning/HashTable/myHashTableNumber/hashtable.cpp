#include "hashtable.h"
#include <malloc.h>
#include <memory.h>

// 构造函数
hashtable::hashtable(int HashTablsSize)
{
    iHashTableSize = HashTablsSize;
    iHashTableDataCount = 0; // Table中数据个数
    pHashTable = (Node**)malloc(sizeof(Node*) * iHashTableSize);
    if (NULL == pHashTable)
    {
        return;
    }
    memset(pHashTable, 0, sizeof(Node*) * iHashTableSize);
}

// 析构函数
hashtable::~hashtable()
{
    free(pHashTable);
    pHashTable = NULL; //释放内存后，将指针设置为NULL。避免产生“野指针”
    iHashTableSize = 0;
    iHashTableDataCount = 0;
}

// 哈希函数
int inline hashtable::HashFun(int val)
{
    return (val ^ 0xdeadbeef) % iHashTableSize;
}

bool hashtable::InsertHashTable(int val)
{
    int key = HashFun(val);

    for(Node *p = pHashTable[key]; p != NULL; p = p->next)
    {
        if (val == p->value)
        {
            return true;
        }
    }

    Node *pNode = new Node(val);
    if (NULL == pNode)
    {
        return false;
    }

    pNode->next = pHashTable[key];
    pHashTable[key] = pNode;

    iHashTableDataCount++; // Table中数据个数
    return true;
}

bool hashtable::FindHashTable(int val)
{
    int key = HashFun(val);

    for(Node *p = pHashTable[key]; p!= NULL; p = p->next)
    {
        if (val == p->value)
        {
            return true;
        }
    }
    return false;
}

int hashtable::SizeHashTable()
{
    return iHashTableSize;
}
