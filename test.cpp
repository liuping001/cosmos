//
// Created by liuping on 2019/1/21.
//
#include <iostream>
#include "Any.hpp"

using namespace std::endl;
using namespace std::cout;

// ----------------------------- test Any --------------------------------
namespace TAny {
    struct Base {
        Base() {
            cout << "construction" << endl;
        }
        virtual ~Base() {
            cout << "destruct" << endl;
        }
    };
    struct A : Base {};
    struct B : Base {};
    struct C : Base {};

    void TestAny () {
        Any any(1);
        any = A();
        any = B();
        any = C();
    }
}
// ----------------------------- test Any --------------------------------

int main() {
    TAny::TestAny();
}