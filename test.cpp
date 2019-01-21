//
// Created by liuping on 2019/1/21.
//
#include <iostream>
#include "Any.hpp"

using std::endl;
using std::cout;

// ----------------------------- test Any --------------------------------
namespace TAny {
    struct Base {
        Base() {
            cout << "construction" << endl;
        }
        Base(const Base &) {
            cout <<"copy construction" << endl;
        }
        Base(Base &&) {
            cout <<"move construction" << endl;
        }
        virtual ~Base() {
            cout << "destruct" << endl;
        }
    };

    void TestAny1 () {
        Any any(1);
        any = Base();
        /*
            construction
            move construction
            copy construction
            destruct
            destruct
            destruct
         */
    }
    struct Comm {
        virtual void Print() {cout << "comm" <<endl;}
    };
    struct A : Comm {
        virtual void Print() {cout << "A" <<endl;}
    };
    struct B : Comm {
        virtual void Print() {cout << "B" <<endl;}
    };
    struct C : Comm {
        virtual void Print() {cout << "C" <<endl;}
    };

    void TestAny2() {
        Any any = Comm();
        any.AnyCast<Comm>().Print();
        any = A();
        any.AnyCast<A>().Print();
        any = B();
        any.AnyCast<B>().Print();
        any = C();
        any.AnyCast<C>().Print();

    }
    void TestAny() {
        TestAny1();
        TestAny2();
    };
}
// ----------------------------- test Any --------------------------------

int main() {
    TAny::TestAny();
}