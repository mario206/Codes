/*
在数组a 下标 1 ~ n 间存在一棵完全二叉树，将其转化为堆
void make_heap(int n,int a[])
在数组a 下标 1 ~ n 之间存在一棵完全二叉树，节点r为“近似堆”，左右子树为堆
void down(int r,int n,int a[])
*/
void swap(int& a,int &b)
{
    int t = a;
    a = b;
    b = t;
}
void down(int r,int n,int a[])
{
    int c = 2 * r;
    while(c <= n)
    {
        if(c + 1 <= n)
            if(a[c] < a[c + 1])
                c += 1;

        if(a[r] < a[c])
            swap(a[r],a[c]);
        // 对刚才较大结点的子树进行下调
        r = c;
        c = c * 2;
    }
}
void make_heap(int n,int a[])
{
    for(int r = n / 2; r >= 1; --r)
        down(r,n,a);
}
#include <iostream>
using namespace std;
int main()
{
    const int n = 100;
    int a[n + 1];
    for(int i = 1;i <= n;i++)
        a[i] = i;
    for(int i = 1;i <= n;i++)
        cout << a[i] << " ";
    cout << endl;
    make_heap(n,a);
    for(int i = 1;i <= n;i++)
        cout << a[i] << " ";
}
