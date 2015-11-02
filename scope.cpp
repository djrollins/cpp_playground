#include <iostream>
#include <string>

std::string s = "global!";

int main()
{
    std::string s = "main!";

    std::cout << s << std::endl; // prints "main!"
    std::cout << ::s << std::endl; // prints "global!"

    {
        std::string s = "inner scope!";
        std::cout << s << std::endl; // prints "inner scope!"
        std::cout << ::s << std::endl; // prints "global!"
    }
}
