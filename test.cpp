//
// Created by liuping on 2019/1/21.
//
#include <iostream>
#include "Any.hpp"

using std::endl;
using std::cout;



// ----------------------------- test Any begin --------------------------------
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
            添加移动赋值后少了一次构造
            construction
            move construction
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

        // 转型错误
        try {
            any.AnyCast<A>();
        } catch (std::exception e) {
            cout << e.what() << endl;
        }

    }
    void TestAny() {
        TestAny1();
        TestAny2();
    };
}
// ----------------------------- test Any end --------------------------------



// ----------------------------- test Aspect begin -----------------------------
#include "Aspect.hpp"
namespace TAspect {
    struct LoggingAspect
    {
        void Before(int i)
        {
            std::cout <<"entering"<< std::endl;
        }

        void After(int i)
        {
            std::cout <<"leaving"<< std::endl;
        }
    };

    void foo(int a)
    {
        cout <<"real HT function: "<<a<< endl;
    }

    int TestAspect()
    {
        Invoke<LoggingAspect>(&foo, 1); //织入方法
        cout <<"-----------------------"<< endl;
        Invoke<LoggingAspect>(&foo, 1);
        return 0;
    }
}
// ----------------------------- test Aspect end -----------------------------


int main() {
    TAny::TestAny();
    TAspect::TestAspect();
}