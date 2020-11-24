#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v;  // default constructor: empty vector
    v.push_back(8);
    v.push_back(17);
    v.push_back(12);
    std::cout << v[2] << '\n';  // array indexing works
    std::cout << v.at(1) << '\n';  // at() method throws exception if
                                   // given out-of-range index.
    std::cout << "Size: " << v.size() << '\n';
    std::vector<int> v2(5, 3);  // use one of the non-default constructors;
                                // vector of 5 ints, each 3.
    for (unsigned i = 0; i < v2.size(); ++i)  // iterate in C-style way
        std::cout << v2[i] << ' ';
    std::cout << '\n';
    for (int x : v2)  // iterate with foreach loop (not supported before C++11);
                      // isn't useful if we need the index.
        std::cout << x << ' ';
    std::cout << std::endl;
}
