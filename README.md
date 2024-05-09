A header-only simple Pimpl helper class for c++.

Main objectives:
- using reference semantics to make it clear that the Pimpl object can't be null
- managing Pimpl object's lifetime (via std::unique_ptr)
- correctly propagating const to the Pimpl object when the "parent" object is const

Naming the Pimpl object `d` (class PimplD) and the parent object inside Impl `q` (class PimplQ) comes from Qt's Pimpl implementation.

# Usage

a.h:
```cpp
class A {
    public:
        A();
        ~A();
        
        void SetVal(int i);
        int GetVal() const;
        // ...other public stuff
    private:
        struct Impl;
        PimplD<Impl> d;
};
```

a.cpp:
```cpp
#include "a.h"

struct A::Impl {
    Impl(A& a) : q{a}
    {
        // A is accessible via q(), e.g.:
        // int i = q().GetVal();
    }
    
    PimplQ<A> q; // Only needed if you need to access A from Impl
    int mVal;
};

A::A()
    : d{*this} // passing *this is needed only if you need to access A from Impl
{}

A::~A() // Destructor is needed to allow the forward declaration of Impl with std::unique_ptr
{}

void A::SetVal(int i)
{
    d().mVal = i;
}
int A::GetVal() const
{
    return d().mVal;
}
```

# Building tests

```
mkdir build
cd build
cmake ..
make
./test
```
