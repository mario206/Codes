#include <iostream>
#include <stack>
#include <string>
using namespace std;
/* 中缀表示法 转 逆波兰表示法（RPN）
    【一】读取一个字符    
        1. 如果遇到的是一个数字，输出
        2. 如果遇到的是一个左括号，入棧
        3. 如果遇到的是一个右括号，出棧，直到遇到一个左括号（若没有左括号，出错）
        4. 如果遇到的是一个运算符
           1. 如果棧为空或比栈顶运算符优先级高，入棧，回到 【一】 ( 左括号的优先级最低)
           2. 如果栈顶运算符优先级较高，弹出栈顶运算符，回到 4.1
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
        //    // 返回ch
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
        // 对数字的处理
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