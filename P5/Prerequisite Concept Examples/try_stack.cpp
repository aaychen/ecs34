#include <iostream>
#include <stack>

int main()
{
    std::stack<int> s;
    s.push(8);
    s.push(15);
    s.push(19);
    std::cout << s.size() << '\n';
    std::cout << s.top() << '\n';
    s.pop();  // pop 19
    s.pop();  // pop 15
    std::cout << s.top() << std::endl;
    return 0;
}
