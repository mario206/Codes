/*
������a �±� 1 ~ n �����һ����ȫ������������ת��Ϊ��
void make_heap(int n,int a[])
������a �±� 1 ~ n ֮�����һ����ȫ���������ڵ�rΪ�����ƶѡ�����������Ϊ��
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
        // �ԸղŽϴ�������������µ�
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
