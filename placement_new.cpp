/*
 * Understanding 'placement-new' - newing up an object in a pre-allocated
 * section of memory
 */
#include <stdlib.h>
#include <new>
#include <iostream>
#include <string>

template<typename T>
class Gizmo {
    T t_;
    public:
        Gizmo(const T&& t) : t_(std::move(t)) {}
        void print() const {std::cout << t_ << std::endl;}
};

std::ostream& operator<<(std::ostream& os, const Gizmo<std::string>& g) {
    g.print();
    return os;
}

int main() {
    auto temp = malloc(sizeof(Gizmo<Gizmo<std::string> >));
    new (temp) Gizmo<Gizmo<std::string> >(Gizmo<std::string>("Bonjour, World!"));
    auto the_gizmo = static_cast<Gizmo<Gizmo<std::string> >*>(temp);
    the_gizmo->print();
    delete the_gizmo;
}
