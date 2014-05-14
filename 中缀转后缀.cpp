#include <iostream>
#include <stack>
#include <string>
using namespace std;
/* ��׺��ʾ�� ת �沨����ʾ����RPN��
    ��һ����ȡһ���ַ�    
        1. �����������һ�����֣����
        2. �����������һ�������ţ��뗣
        3. �����������һ�������ţ�������ֱ������һ�������ţ���û�������ţ�����
        4. �����������һ�������
           1. �����Ϊ�ջ��ջ����������ȼ��ߣ��뗣���ص� ��һ�� ( �����ŵ����ȼ����)
           2. ���ջ����������ȼ��ϸߣ�����ջ����������ص� 4.1
*/
string RPN(string& exp)
{
    stack<char> opStack;
    string rString;
    const string blank = " ";
    int len = exp.length();
    for(int i = 0; i < len; i++)
    {
        char ch = exp.at(i);
        //if( ch >= '0' && ch <= '9')
        //{
        //    // ����ch
        //    rString.append(blank + ch);
        //    continue;
        //}
        switch (ch)
        {
        case ' ':
            break;
        case '(':
            opStack.push(ch);
            break;
        case ')':
            while( ( ch = opStack.top() ) != '(')
            {
                rString.append(blank + ch);
                opStack.pop();
            }
        case '+':
        case '-':
        case '*':
        case '/':
        while(1)
        {
            if( opStack.empty() || 
                opStack.top() == '(' || 
                ( ch == '*'  ||  ch == '/' ) && 
                (opStack.top() == '+'  || opStack.top() == '-')  
                )
            {
                opStack.push(ch);
                break;
            }
            else
            {
                rString.append(blank + opStack.top());
                opStack.pop();
            }
        }
            break;
        // �����ֵĴ���
        default:
            rString.append(blank + ch);
            break;
        }

    }
    while( !opStack.empty())
    {
        if(opStack.top() != '(')
            rString.append(blank + opStack.top());
        opStack.pop();
    }
    return rString;
}
int main()
{
    string exp;
    while(1)
    {
        getline(cin,exp);
        if(exp != "#")
            cout << exp << " , " << RPN(exp) << endl;
        else
            break;
    }
    return 0;
}