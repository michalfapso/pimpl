#include "b.h"
#include <iostream>

B::B()
{}

B::~B()
{}

void B::foo()
{
    mFnCallListener("B::foo() non-const");
}
void B::foo() const
{
    mFnCallListener("B::foo() const");
}