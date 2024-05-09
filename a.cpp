#include "a.h"
#include "b.h"
#include <iostream>

struct A::Impl {
    Impl(A& a) : q{a} {
        mB.mFnCallListener = [&](const std::string& s){
            q().mFnCallListener(s);
        };
    }
    void boo() {
        q().mFnCallListener("A::Impl::boo() non-const");
        q().boo();
    }
    void boo() const {
        q().mFnCallListener("A::Impl::boo() const");
        q().boo();
    }
    PimplQ<A> q;
    B mB;
};

A::A() : d{*this}
{}

A::~A()
{}

void A::foo()
{
    mFnCallListener("A::foo() non-const");
    d().boo();
    d().mB.foo();
}
void A::foo() const
{
    mFnCallListener("A::foo() const");
    d().boo();
    d().mB.foo();
}
void A::boo()
{
    mFnCallListener("A::boo() non-const");
}
void A::boo() const
{
    mFnCallListener("A::boo() const");
}
