#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include "a.h"

TEST_CASE("pimpl", "[pimpl]") {
    std::vector<std::string> callstack;
    A a{};
    a.mFnCallListener = [&](const std::string& name){
        // std::cout << name << std::endl;
        callstack.push_back(name);
    };
    SECTION("non-const") {
        a.foo();
        REQUIRE(callstack == std::vector<std::string>{
            "A::foo() non-const",
            "A::Impl::boo() non-const",
            "A::boo() non-const",
            "B::foo() non-const",
        });
    }
    SECTION("const") {
        const A& ac = a;
        ac.foo();
        REQUIRE(callstack == std::vector<std::string>{
            "A::foo() const",
            "A::Impl::boo() const",
            "A::boo() const",
            "B::foo() const",
        });
    }
}


struct Base {
    virtual ~Base() {}
    virtual int GetVal() { return 0; }
};
struct Derived1 : public Base {
    int GetVal() override { return 1; }
};
struct Derived2 : public Base {
    int GetVal() override { return 2; }
};

struct Big {
    Big(int type)
        : p(
            type == 1 ? std::make_unique<Derived1>() :
            type == 2 ? std::make_unique<Derived2>() :
                        std::make_unique<Base>())
    {}
    int GetVal() { return p().GetVal(); }
private:
    PimplD<Base> p;
};

TEST_CASE("pimpl external unique_ptr", "[pimpl]") {
    Big b0(0);
    Big b1(1);
    Big b2(2);
    REQUIRE(b0.GetVal() == 0);
    REQUIRE(b1.GetVal() == 1);
    REQUIRE(b2.GetVal() == 2);
}
