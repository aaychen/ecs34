#include "list.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Visible.
 */
struct A
{
    A(int a) : a{a} {}  // intentionally not marked explicit
    int a;
};
std::ostream& operator<<(std::ostream& os, const struct A& obj)
{
    os << "hi there: " << obj.a;
    return os;
}

/**
 * Visible.
 */
std::ostream& operator<<(std::ostream& os, const std::vector<int>& vals)
{
    for (const auto& val : vals)
        os << val << ' ';
    return os;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "You did not pass a test case number as command-line argument to this executable."
            << std::endl;
        return 1;
    }
    int caseNum = std::stoi(argv[1]);
    std::cout << std::boolalpha;
    switch (caseNum)
    {
        case 1:
        {
            List<std::string> lst;
            lst.pushBack("spongebob");
            lst.pushBack("squidward");
            std::cout << lst;
            lst.pushBack("patrick");
            std::cout << lst;
            break;
        }
        case 2:
        {
            List<A> lst;
            lst.pushBack(8);
            lst.pushBack(15);
            lst.pushBack(20);
            std::cout << lst;
            lst.pushBack(45);
            lst.pushBack(-37);
            lst.pushBack(100);
            std::cout << lst;
            break;
        }
        case 4:
        {
            List<int> lst, lst2;
            lst.pushBack(50);
            lst2.pushFront(100);
            lst.pushFront(40);
            lst2.pushFront(90);
            lst2.pushBack(110);
            lst.pushFront(30);
            lst.pushBack(60);
            lst.pushFront(20);
            lst2.pushBack(120);
            std::cout << lst << lst2;
            break;
        }
        case 6:
        {
            List<int> lst;
            std::cout << lst.length() << '\n';
            lst.pushFront(1);
            lst.pushBack(2);
            lst.pushBack(3);
            lst.pushFront(4);
            std::cout << lst.length() << '\n';
            break;
        }
        case 8:
        {
            List<int> lst, lst2;
            lst.pushBack(50);
            lst2.pushFront(100);
            lst.pushFront(40);
            lst2.pushFront(90);
            lst2.pushBack(110);
            lst.pushFront(30);
            lst.pushBack(60);
            lst.pushFront(20);
            lst2.pushBack(120);
            std::cout << lst.contains(100) << '\n';
            std::cout << lst2.contains(100) << '\n';
            std::cout << lst.contains(50) << '\n';
            std::cout << lst2.contains(50) << '\n';
            break;
        }
        case 10:
        {
            List<int> vals;
            vals += 8;
            vals += 17;
            vals += 53;
            vals += 47;
            std::cout << vals;
            vals.pushFront(10);
            vals.pushBack(20);
            std::cout << vals;
            break;
        }
        case 12:
        {
            List<int> lst;
            std::cout << lst.remove(10) << '\n';
            lst.pushBack(5);
            std::cout << lst.length() << '\n';  // 1
            std::cout << lst.remove(5) << ' ' << lst.length() << '\n';
            lst.pushFront(10);
            lst += 15;
            std::cout << lst.remove(15) << '\n';
            lst += 30;
            std::cout << lst;  // 10 30
            break;
        }
        case 13:
        {
            List<int> lst1, lst2;
            for (unsigned i = 0; i < 10; ++i)
            {
                lst1.pushBack(i);
                lst2.pushFront(i);
            }
            std::cout << lst1 << lst2;
            std::cout << lst1.length() << ' ' << lst2.length() << '\n';
            lst1.remove(3);
            lst2.remove(3);
            std::cout << lst1 << lst2;
            std::cout << lst1.length() << ' ' << lst2.length() << '\n';
            std::cout << lst1.remove(9) << ' ' << lst1.remove(11) << '\n';
            std::cout << lst1.length() << ' ' << lst2.length() << '\n';
            lst1 += 15;
            lst1 += 15;
            lst1 += 15;
            std::cout << lst1.remove(15) << ' ' << lst1;
            std::cout << lst1.remove(15) << ' ' << lst1;
            std::cout << lst1.remove(15) << ' ' << lst1;
            std::cout << lst1.remove(15) << ' ' << lst1;
            break;
        }
        case 15:
        {
            List<int> lst;
            lst -= 10;
            lst.pushBack(5);
            std::cout << lst.length() << '\n';  // 1
            lst -= 5;
            std::cout << lst.length() << '\n';
            lst.pushFront(10);
            lst += 15;
            lst -= 15;
            lst += 30;
            std::cout << lst;  // 10 30
            break;
        }
        case 17:
        {
            int* ptr1 = new int{30};
            int* ptr2 = new int{20};
            int* ptr3 = new int{70};
            int* ptr4 = new int{50};
            int* ptr5 = new int{90};
            List<int**> lst;
            lst.pushBack(&ptr1);  // 30
            lst.pushBack(&ptr2);  // 20
            lst.pushBack(&ptr3);  // 70
            lst[0] = &ptr3;  // 70
            lst[1] = &ptr2;  // 20 (no change)
            lst[1] = &ptr3;  // 70
            lst[2] = &ptr4;  // 50
            lst[0] = &ptr5;  // 90
            for (unsigned i = 0; i < lst.length(); ++i)
                std::cout << **lst[i] << '\n';
            delete ptr1;
            delete ptr2;
            delete ptr3;
            delete ptr4;
            delete ptr5;
            break;
        }
        case 18:
        {
            List<int> vals;
            try
            {
                vals[0] = 5;
                std::cout << vals;
            }
            catch (const std::out_of_range& ex)
            {
                std::cout << "Caught exception!\n";
            }
            catch (...)
            {
                std::cout << "Wronge exception type!\n";
            }
            break;
        }
        case 19:
        {
            List<std::vector<int>> lst;
            std::vector<int> vals1{10, 20, 30};
            lst.pushBack(vals1);
            std::vector<int> vals2{40, 50};
            lst.pushBack(vals2);
            std::cout << lst;
            lst[1][0] = 90;
            lst[0].push_back(80);
            std::cout << lst;
            break;
        }
        case 21:
        {
            int* ptr1 = new int{30};
            int* ptr2 = new int{20};
            int* ptr3 = new int{70};
            int* ptr4 = new int{50};
            int* ptr5 = new int{90};
            List<int**> lst;
            lst.pushBack(&ptr1);  // 30
            lst.pushBack(&ptr2);  // 20
            lst.pushBack(&ptr4);  // 50
            lst.pushBack(&ptr1);  // 30
            lst.pushBack(&ptr2);  // 20
            lst.pushBack(&ptr5);  // 90
            lst.pushBack(&ptr1);  // 30
            lst.pushBack(&ptr2);  // 20
            lst.pushBack(&ptr3);  // 70
            const List<int**>& lstRef = lst;
            for (unsigned i = 0; i < lst.length(); ++i)
                std::cout << **lstRef[i] << '\n';
            delete ptr1;
            delete ptr2;
            delete ptr3;
            delete ptr4;
            delete ptr5;
            break;
        }
        case 22:
        {
            List<std::string> lst1, lst2;
            lst1.pushFront("abc");
            lst1.pushFront("abc2");
            lst1.pushFront("abc3");
            lst2.pushBack("xyz");
            lst2.pushBack("xyz2");
            lst2.pushBack("xyz3");
            std::cout << lst1 << lst2;
            const List<std::string>& lst1Ref = lst1, lst2Ref = lst2;
            for (unsigned i = 0; i < lst1.length(); ++i)
            {
                std::cout << lst1Ref[i] << ' ' << lst2Ref[i] << '\n';
            }
            break;
        }
        case 24:
        {
            List<unsigned> vals;
            for (unsigned i = 10; i < 200; i += 10)
                vals.pushBack(i);
            List<unsigned> vals2{vals};
            std::cout << vals << vals2;
            std::cout << vals.remove(70) << '\n' << vals << vals2;
            std::cout << vals.remove(75) << '\n' << vals << vals2;
            std::cout << vals.contains(190) << ' ' << vals2.contains(190) << '\n';
            List<unsigned> vals3{vals2};
            std::cout << vals << vals2 << vals3;
            break;
        }
        case 25:
        {
            List<int> vals;
            vals.pushBack(13);
            List<int> vals2{vals};
            vals.pushBack(20);
            vals2.pushBack(20);
            vals -= 13;
            vals2 -= 20;
            std::cout << vals << vals2;
            break;
        }
        case 27:
        {
            List<unsigned> vals;
            for (unsigned i = 10; i < 200; i += 10)
                vals.pushBack(i);
            List<unsigned> vals2{vals};
            std::cout << vals << vals2;
            std::cout << vals.remove(70) << '\n' << vals << vals2;
            std::cout << vals.remove(75) << '\n' << vals << vals2;
            std::cout << vals.contains(190) << ' ' << vals2.contains(190) << '\n';
            vals = vals2;
            std::cout << vals.remove(70) << '\n' << vals << vals2;
            std::cout << vals.remove(75) << '\n' << vals << vals2;
            std::cout << vals.contains(190) << ' ' << vals2.contains(190) << '\n';
            break;
        }
        case 28:
        {
            List<int> vals;
            for (int i = 0; i < 10000; ++i) vals += i;
            List<int> vals2{vals};
            vals -= 0;
            vals2 -= 9999;
            vals2 = vals;
            vals2 -= 9999;
            vals2 = vals;
            vals = vals2;
            std::cout << vals.length() << ' ' << vals2.length() << '\n';
            for (int i = 10; i < 10000; ++i) vals -= i;
            std::cout << vals;
            std::cout << vals.length() << ' ' << vals2.length() << '\n';
            break;
        }
        case 30:
        {
            // Same as 8.
            List<int> lst, lst2;
            lst.pushBack(50);
            lst2.pushFront(100);
            lst.pushFront(40);
            lst2.pushFront(90);
            lst2.pushBack(110);
            lst.pushFront(30);
            lst.pushBack(60);
            lst.pushFront(20);
            lst2.pushBack(120);
            std::cout << lst.contains(100) << '\n';
            std::cout << lst2.contains(100) << '\n';
            std::cout << lst.contains(50) << '\n';
            std::cout << lst2.contains(50) << '\n';
            break;
        }
        case 31:
        {
            // Same as 24.
            List<unsigned> vals;
            for (unsigned i = 10; i < 200; i += 10)
                vals.pushBack(i);
            List<unsigned> vals2{vals};
            std::cout << vals << vals2;
            std::cout << vals.remove(70) << '\n' << vals << vals2;
            std::cout << vals.remove(75) << '\n' << vals << vals2;
            std::cout << vals.contains(190) << ' ' << vals2.contains(190) << '\n';
            List<unsigned> vals3{vals2};
            std::cout << vals << vals2 << vals3;
            break;
        }
        case 32:
        {
            // Same as 28.
            List<int> vals;
            for (int i = 0; i < 10000; ++i) vals += i;
            List<int> vals2{vals};
            vals -= 0;
            vals2 -= 9999;
            vals2 = vals;
            vals2 -= 9999;
            vals2 = vals;
            vals = vals2;
            std::cout << vals.length() << ' ' << vals2.length() << '\n';
            for (int i = 10; i < 10000; ++i) vals -= i;
            std::cout << vals;
            std::cout << vals.length() << ' ' << vals2.length() << '\n';
            break;
        }
        default:
            std::cerr << "Invalid case number." << std::endl;
            return 2;
    }
    return 0;
}
