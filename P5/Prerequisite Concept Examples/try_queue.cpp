#include <iostream>
#include <queue>

int main()
{
    std::queue<int> q;
    q.push(37);
    q.push(65);
    q.push(49);
    q.push(15);
    std::cout << q.size() << '\n';
    std::cout << q.back() << '\n';
    std::cout << q.front() << '\n';
    q.pop();
    std::cout << q.front() << '\n';
}
