#include <stack>
#include <iostream>
#include <iomanip>
template <typename T>
class BST
{
public:
    class BinNode
    {
    public:
        BinNode():left(NULL),right(NULL){};
        BinNode(const T& item)
        {
            data = item;
            left = right = NULL;
        }
        T       data;
        BinNode* left;
        BinNode* right;
    };
     typedef BinNode* BinNodePointer;
public:
    BST():root(NULL){};
    void Insert(const T& item);
    void Search(const T& item,BinNodePointer& x,BinNodePointer& parent,bool& found);
    void Delete(const T& item);
    void Print();                       // ���� InOrder ��ӡ��
    void PrintTree();                   // ��������״��ӡ��
    void InOrder(BinNodePointer ptr);  // �������ptr�ڵ�
private:
    BinNodePointer root;
};
template <typename T>
void BST<T>::Insert(const T& item)
{
    bool found;
    BinNodePointer x,parent;
    Search(item,x,parent,found);
    // item �����ڣ���ӵ� parent ��
    if(!found)
    {
        x = new BinNode(item);
        
        if(parent == 0)    // ���뵽����
            root = x;
        else if(item < parent -> data)
            parent -> left = x ;
        else
            parent -> right = x ;
    }
}
template <typename T>
void BST<T>::Search(const T& item,BinNodePointer& x,BinNodePointer& parent,bool& found)
{
    x = root;
    parent = 0;
    found = false;
    for(;;)
    {
        if(found == true || x == NULL)
            return ;
        if(x -> data > item)
        {
            parent = x ;
            x = x -> left;
        }
        else if(x -> data < item)
        {
            parent = x;
            x = x -> right;
        }    
        else
            found = true;
    }
}
template <typename T>
void BST<T>::Delete(const T& item)
{
    bool found;
    BinNodePointer x;
    Search(item,x,parent,found);
    // û�ҵ�
    if(!found)
        return ;
    if(x -> left != NULL && x ->right != NULL)   // ����������
        {
            // �ҵ����������ҵ���С�Ľ��(����)
            parent = x ;
            BinNodePointer min_of_right = x -> right;
            while(min_of_right != NULL)
            {
                parent = min_of_right;
                min_of_right = min_of_right -> left;
            }
            x - >data = min_of_right -> data;
            x = min_of_right;
        }
    // ������ֻ��0��1�����ӵ����
    BinNodePointer subtree = x -> left;
    if(subtree == NULL)
        subtree = x -> right;
    // ��ɾ�����Ǹ�
    if(parent == 0)
        root = subtree;
    else if (parent -> left == x )
        parent -> left = subtree;
    else
        parent ->right = subtree;
    delete x;
}
template <typename T>
void BST<T>::Print()
{
    InOrder(root);
}
template <typename T>
void BST<T>::InOrder(BinNodePointer ptr)
{
    if(ptr != NULL)
    {
        InOrder(ptr -> left);
        std::cout << ptr -> data << " ";
        InOrder(ptr -> right);
    }
}
template <typename T>
void BST<T>::PrintTree()
{
    int index = 0;
    int index_i = 0;
    std::deque<BinNodePointer> _deque;
    BinNodePointer p,q;
    _deque.push_back(root);
    p = q = root;
    while(q = _deque.front() )
    {
        _deque.pop_front();
        if(q -> left)
            _deque.push_back(q ->left);
        if(q ->right)
            _deque.push_back(q ->right);
        if(q == p -> left || q == p ->right )
        {
            cout << endl;
            index_i = 0;
            index += 8;
            if(q -> left || q -> right)
                p = q;
            else
                p = _deque.front();
        }
        cout << setw(index + index_i) << q -> data;
        index_i += 8;
        
    }
    
}