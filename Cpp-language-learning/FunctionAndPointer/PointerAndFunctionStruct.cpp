#include <iostream>

using namespace std;

struct Node
{
    int value;
    int data;

    Node()
    {
        this->value = 0;
        this->data = 0;
    }
};

void InitNode(Node **ppNode, int val, int dat)
{
    (*ppNode)->value = val;
    (*ppNode)->data = dat;

    cout << "ppNode  = " << ppNode << endl;
    cout << "&ppNode = " << &ppNode << endl;
}
int main()
{
    Node *pNode = new Node();

    cout << sizeof(*pNode) << endl;
    cout << "value   = " << pNode->value << endl;
    cout << "data    = " << pNode->data << endl;
    cout << "pNode   = " << pNode << endl;
    cout << "&pNode  = " << &pNode << endl;

    InitNode(&pNode, 1, 2);

    cout << "value   = " << pNode->value << endl;
    cout << "data    = " << pNode->data << endl;
    cout << "pNode   = " << pNode << endl;
    cout << "&pNode  = " << &pNode << endl;
    return 0;
}
