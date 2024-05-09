#include <memory>
#include <functional>
#include <string>
#include "pimpl.h"

class A {
    public:
        A();
        ~A();
        void foo();
        void foo() const;
        void boo();
        void boo() const;

        std::function<void(const std::string&)> mFnCallListener;
    private:
        struct Impl;
        PimplD<Impl> d;
};