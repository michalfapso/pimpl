#include <functional>
#include <string>

class B {
    public:
        B();
        ~B();
        void foo();
        void foo() const;

        std::function<void(const std::string&)> mFnCallListener;
    private:
        int mVal = 10;
};