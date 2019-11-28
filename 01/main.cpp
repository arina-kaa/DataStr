/*
Каравайцева Арина, ИПС

   22. В строке текстового файла  задано  выражение  из  целых 
чисел и операций '+', '-', '*', '/', '^'.  Порядок  вычислений 
определяется приоритетом операций и круглыми скобками. Возможен
одноместный минус в начале  выражения  или  после  открывающей 
скобки. Преобразовать выражение в постфиксную  форму (алгоритм 
Дейкстры) и вычислить его значение. Показать этапы  выполнения
(11).
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include "classes/stack.h"
#include "classes/resultOptions.h"

using namespace std;

bool inArray(const char store[], const int storeSize, const char query)
{
    bool result = false;
    for (size_t i = 0; i < storeSize; ++i)
    {
        if (store[i] == query)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool isOperation(char c)
{
    const int arraySize = 5;
    char operators[arraySize] = {'+', '-', '*', '/', '^'};
    return inArray(operators, arraySize, c);
}

bool isLeftAssociative(char c)
{
    const int arraySize = 4;
    char operators[arraySize] = {'+', '-', '*', '/'};
    return inArray(operators, arraySize, c);
}

bool isRightAssociative(char c)
{
    const int arraySize = 1;
    char operators[arraySize] = {'^'};
    return inArray(operators, arraySize, c);
}

int getPriority(char c)
{
    int priority = -1;
    if (c == '^')
        priority = 3;
    else if (c == '*' || c == '/')
        priority = 2;
    else if (c == '+' || c == '-')
        priority = 1;
    return priority;
}

bool isBrackets(char c)
{
    return (c == '(') || (c == ')');
}

bool isValidSymbol(char c)
{
    return isdigit(c) || isOperation(c) || isBrackets(c);
}

void printStepResults(char c, string s, Stack<char> &st)
{
    cout << "Infix char: " << c << endl;
    cout << "Postfix string: " << s << endl;
    cout << "Stack: ";
    st.print();
    cout << endl
         << endl;
}

int getPostfixFromInfix(string strInfix, string &strPostfix)
{
    Stack<char> st;
    int resultCode = resultOptions::validString;

    if (strInfix.length() == 0)
    {
        resultCode = resultOptions::emptyString;
    }

    for (int i = 0; (i < strInfix.length()) && (resultCode == resultOptions::validString); i++)
    {
        if (!isValidSymbol(strInfix[i]))
        {
            resultCode = resultOptions::invalidSymbol;
            break;
        }

        if (isdigit(strInfix[i]))
        {
            strPostfix += strInfix[i];
        }
        else if (isOperation(strInfix[i]))
        {
            if ((i > 0) && isOperation(strInfix[i - 1]))
            {
                resultCode = resultOptions::severalOperations;
                break;
            }

            if (isLeftAssociative(strInfix[i]))
            {
                if ((strInfix[i] == '-') && ((strPostfix.length() == 0) || (!st.empty() && (st.top() == '('))))
                {
                    strPostfix += '0';
                }
                while (!st.empty() && (getPriority(strInfix[i]) <= getPriority(st.top())) && st.top() != '(')
                {
                    strPostfix += st.top();
                    st.pop();
                }
                st.push(strInfix[i]);
            }
            else if (isRightAssociative(strInfix[i]))
            {
                while (!st.empty() && (getPriority(strInfix[i]) < getPriority(st.top())) && st.top() != '(')
                {
                    strPostfix += st.top();
                    st.pop();
                }
                st.push(strInfix[i]);
            }
        }
        else if (isBrackets(strInfix[i]))
        {
            if (strInfix[i] == '(')
            {
                st.push(strInfix[i]);
            }
            else if (strInfix[i] == ')')
            {
                while (!st.empty() && st.top() != '(')
                {
                    strPostfix += st.top();
                    st.pop();
                }
                if (st.top() == '(')
                    st.pop();
            }
        }

        printStepResults(strInfix[i], strPostfix, st);
    }

    while (!st.empty())
    {
        if (!isBrackets(st.top()))
        {
            strPostfix += st.top();
            st.pop();
        }
        else
        {
            resultCode = resultOptions::notClosedBrackets;
            break;
        }
    }

    st.~Stack();
    return resultCode;
}

int getResultFromPostfix(string s)
{
    Stack<int> st;
    int result = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]))
        {
            st.push(s[i] - '0');
        }
        else if (isOperation(s[i]))
        {
            int y = st.top();
            st.pop();
            int x = st.top();
            st.pop();

            switch (s[i])
            {
            case '+':
                result = x + y;
                break;
            case '-':
                result = x - y;
                break;
            case '*':
                result = x * y;
                break;
            case '/':
                result = x / y;
                break;
            case '^':
                result = pow(x, y);
                break;
            }

            st.push(result);
        }
    }

    result = st.top();
    st.~Stack();
    return result;
}

bool getBoolFromAnswer(string s)
{
    bool result = false;
    if (s == "yes" || s == "y" || s == "true" || s == "1")
    {
        result = true;
    }
    return result;
}

int main() // task 22
{
    string strInfix = "";
    string strPostfix = "";
    bool shouldContinue = true;

    while (shouldContinue)
    {
        cout << "Enter infix expression:" << endl;
        getline(cin, strInfix);
        cout << endl;
        int resultCode = getPostfixFromInfix(strInfix, strPostfix);
        if (resultCode == resultOptions::validString)
        {
            cout << "Postfix expression: " << strPostfix << endl;
            int resultExpression = getResultFromPostfix(strPostfix);
            cout << "Result of postfix expression: " << resultExpression << endl;
        }
        else
        {
            resultOptions::printError(resultCode);
        }
        strPostfix = "";
        cout << endl
             << "Do you want to continue?" << endl;
        string answer = "";
        getline(cin, answer);
        shouldContinue = getBoolFromAnswer(answer);
    }

    return 0;
}