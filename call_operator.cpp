#include <iostream>

class Test
{
public:
    Test(int i, float j) : i_(i) {
        std::cout << j << std::endl;
    }
    auto operator()(int i)
    {
        std::cout << i_ + i<< std::endl;
    }
private:
    int i_;
};

class Test2
{
public:
    Test2(Test t) : t_(t) {}
    Test t_;
};

int main()
{
    Test t{2, 2.1};
    t(1);

    Test2 t2((33, 5.1));
}
