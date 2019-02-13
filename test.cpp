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
            std::cout <<"entering" << i << std::endl;
        }

        void After(int i)
        {
            std::cout <<"leaving"<< i <<std::endl;
        }
    };

    void foo(int a)
    {
        cout <<"real HT function: "<<a<< endl;
    }

    int TestAspect()
    {
        Invoke<LoggingAspect>(&foo, 1); //织入方法
        return 0;
    }
}
// ----------------------------- test Aspect end -----------------------------


// ----------------------------- test object pool begin-----------------------
#include "object_pool/SimpleObjectPool.hpp"
namespace TObjectPool {

//test code
    class A {};
    void test_object_pool() {
        SimpleObjectPool <A> p;
        p.add(std::unique_ptr<A>(new A()));
        p.add(std::unique_ptr<A>(new A()));
        {
            auto t = p.get();
            p.get();
            std::cout <<"size:"<<p.size() << std::endl;
        }
        std::cout <<"size:"<<p.size() << std::endl;
        {
            auto t1 = p.get();
            auto t2 = p.get();
            std::cout <<"size:"<<p.size() << std::endl;
        }

        std::cout << "size:"<<p.size() << std::endl;
    }
    void TestObjectPool() {
        test_object_pool();
    }
}
// ----------------------------- test object pool end-----------------------


// ----------------------------- test Bind begin -----------------------------
// 这个bind作者只是展示了其关键实现，工程上还是得使用std::bind
// ----------------------------- test Bind end  ------------------------------


// ----------------------------- test function cache begin -------------------------

// ----------------------------- test function cache end   -------------------------

// ----------------------------- test function range begin -------------------------
#include "Range.hpp"
namespace TRange {
    template <class T> void Print (RangeImpl<T> range) {
        for (auto item : range) {
            cout << " " << item ;
        }
        cout << endl;
    }
    void TestRange() {
        Print(Range(5));
        Print(Range(5, 10));
        Print(Range(5, 20, 3));
    }
}
// ----------------------------- test function range end   -------------------------
int main() {
    TAny::TestAny();
    TAspect::TestAspect();
    TObjectPool::TestObjectPool();
    TRange::TestRange();
}