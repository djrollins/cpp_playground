#include <iostream>

class Base
{
public:
    Base(int i) : i_(i) {}
    Base(const Base &b) = default;
    void virtual func()
    {
        std::cout << "func called from Base " << i_ << std::endl;
    }
    virtual ~Base();
    long i_;
};

class Derived : public Base
{
public:
    Derived(int i) : Base(i) {}
    void func()
    {
        std::cout << "func called from Derived " << i_ << std::endl;
    }
};

Base::~Base() {}

auto call_func_val(Base b)
{
    b.func();
}

auto call_func_ref(Base& b)
{
    b.func();
}

int main()
{
    Base b(0);
    Derived d(1);

    call_func_val(b); // func called from Base 0
    call_func_val(d); // func called from Base 1
    call_func_ref(b); // func called from Base 0
    call_func_ref(d); // func called from Derivied 1
}
