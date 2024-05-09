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
