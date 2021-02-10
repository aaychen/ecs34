#include "list.hpp"

struct X
{
    X() { std::cout << "Constructor!\n"; }
    ~X() { std::cout << "Destructor!\n"; }
};

int main()
{
    std::cout << std::boolalpha;
    List<int> lst;
    lst.pushBack(15);
    lst.pushFront(33);
    lst.pushFront(20);
    lst.pushBack(50);
    lst.pushFront(40);
    lst += 80;
    std::cout << lst;
    std::cout << lst.length() << '\n';
    std::cout << "lst[3]=" << lst[3] << '\n';
    lst[2] = 90;
    std::cout << lst;
    std::cout << "Contains 50: " << lst.contains(50) << '\n' << "Contains -10: " << lst.contains(-10) << '\n';
    std::cout << "Remove 50: " << lst.remove(50) << ' ' << lst;
    std::cout << "Remove 80: " << lst.remove(80) << ' ' << lst;
    std::cout << "Remove -10: " << lst.remove(-10) << ' ' << lst;
    lst.pushFront(200);
    lst.pushBack(300);
    lst += 100;
    std::cout << lst;
    lst.remove(200);
    lst -= 40;
    std::cout << lst;
    std::cout << "Copy construction...\n";
    List<int> lst2{lst};
    lst2.remove(90);
    std::cout << lst << lst2;

    std::cout << "Copy assignment...\n";
    lst2 = lst;
    std::cout << lst << lst2;
    lst.pushBack(-400);
    lst2.pushFront(-100);
    lst2 += -200;
    std::cout << lst << lst2;
    std::cout << lst.length() << ' ' << lst2.length() << '\n';

    std::cout << "Trying strings...\n";
    List<std::string> strings;
    std::cout << strings;
    std::cout << strings.length() << '\n';
    strings.pushBack("def");
    strings.pushFront("abc");
    strings += "ghi";
    std::cout << strings;
    std::cout << strings.length() << '\n';
    strings -= "gh";
    strings -= "abc";
    std::cout << "After removing \"abc\": " << strings;
    std::cout << strings.length() << '\n';
    strings.pushFront("jklmn");
    std::cout << strings;
    std::cout << strings[2] << '\n';
    std::cout << "Copy construction...\n";
    auto strings2 = strings;
    std::cout << strings[1] << ' ' << strings2[1] << '\n';
    strings.remove("def");
    strings2.pushFront("op");
    std::cout << "strings: " << strings
              << "strings2: " << strings2;
    std::cout << "strings[1]: " << strings[1] << '\n'
              << "strings2[1]: " << strings2[1] << '\n';

    std::cout << "Trying class X...\n";
    List<X> objs;
    objs.pushBack(X{});
    std::cout << "Trying out-of-range index...\n";
    try
    {
        auto o = objs[3];
    }
    catch (const std::out_of_range& ex)
    {
        std::cerr << "I accept your exception!\n";
    }
    catch (...)
    {
        std::cerr << "Wrong type of exception!\n";
    }

    std::cout << std::noboolalpha;
}
