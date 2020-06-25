#include <iostream>
#include "include/list.hpp"
int main()
{
    std::cout<<"hello world";
    ce::list<int> a;
    a.push_back(1);
    std::cout<<a.toString();
    return 0;
}
