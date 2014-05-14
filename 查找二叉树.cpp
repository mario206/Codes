#include <iostream>
template <typename T>
class BTree
{
public:
    struct Node
    {
        Node():left(NULL),right(NULL){};
        Node(const T& item)
        {
            data = item;
            left = right = NULL;
        }
        T       data;
        Node* left;
        Node* right;
    };
     typedef Node* NodePointer;
public:
    BTree():root(NULL){};
    void Insert(const T& item);
    void Search(const T& item,NodePointer& x,NodePointer& parent,bool& found);
    void Delete(const T& item);
    void PrintTree();
    void Inorder(NodePointer ptr);
private:
    NodePointer root;
};
template <typename T>
void BTree<T>::Insert(const T& item)
{
    bool found;
    NodePointer x,parent;
    Search(item,x,parent,found);
    // item 不存在，添加到 parent 下
    if(!found)
    {
        x = new Node(item);

        if(parent == 0)    // 插入到根部
            root = x;
        else if(item < parent -> data)
            parent -> left = x ;
        else
            parent -> right = x ;
    }
}
template <typename T>
void BTree<T>::Search(const T& item,NodePointer& x,NodePointer& parent,bool& found)
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
void BTree<T>::Delete(const T& item)
{
    bool found;
    NodePointer x;
    Search(item,x,parent,found);
    // 没找到
    if(!found)
        return ;
    if(x -> left != NULL && x ->right != NULL)   // 有两个孩子
        {
            // 找到右子树中找到最小的结点(最左)
            parent = x ;
            NodePointer min_of_right = x -> right;
            while(min_of_right != NULL)
            {
                parent = min_of_right;
                min_of_right = min_of_right -> left;
            }
            x - >data = min_of_right -> data;
            x = min_of_right;
        }
    // 处理结点只有0或1个孩子的情况
    NodePointer subtree = x -> left;
    if(subtree == NULL)
        subtree = x -> right;
    // 被删除的是根
    if(parent == 0)
        root = subtree;
    else if (parent -> left == x )
        parent -> left = subtree;
    else
        parent ->right = subtree;
    delete x;
}
template <typename T>
void BTree<T>::PrintTree()
{
    Inorder(root);
}
template <typename T>
void BTree<T>::Inorder(NodePointer ptr)
{
    if(ptr != NULL)
    {
        Inorder(ptr -> left);
        std::cout << ptr -> data;
        Inorder(ptr -> right);
    }
}