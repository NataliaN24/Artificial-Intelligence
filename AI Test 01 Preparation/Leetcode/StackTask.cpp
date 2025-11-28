Check if a string of parentheses is balanced using a stack

You are given a string consisting of:

(  )  {  }  [  ]


Your task is to:

✔ Use a stack
✔ Check whether the string is balanced
✔ Print "YES" if balanced, "NO" otherwise

  #include<iostream>
#include<stack>
#include<string>
using namespace std;

int main()
{
    string s;
    cin >> s;

    stack<char> st;

    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];

        if (c == '(' || c == '{' || c == '[')
        {
            st.push(c);
        }
        else if (c == ')' || c == '}' || c == ']')
        {
            if (st.empty())
            {
                cout << "Not balanced";
                return 0;
            }

            char top = st.top();

            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '['))
            {
                st.pop();
            }
            else
            {
                cout << "Not balanced";
                return 0;
            }
        }
    }

    if (st.empty())
        cout << "Balanced";
    else
        cout << "Not balanced";

    return 0;
}
