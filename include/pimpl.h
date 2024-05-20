#pragma once

#include <memory>

template<typename T>
class PimplD {
    public:
        template <typename S>
        explicit PimplD(std::unique_ptr<S> p)
            : mStorage{std::move(p)}
        {}

        template <typename... Args>
        explicit PimplD(Args&&... args)
            : mStorage{std::make_unique<T>(std::forward<Args>(args)...)}
        {}

        const T& operator()() const { return *mStorage; }
              T& operator()()       { return *mStorage; }
    private:
        std::unique_ptr<T> mStorage;
};

template<typename T>
class PimplQ {
    public:
        explicit PimplQ(T& q)
            : mStorage{q}
        {}

        // Pimpl(std::unique_ptr<T>&& d) : _storage_d{std::move(d)} {}
        const T& operator()() const { return mStorage; }
              T& operator()()       { return mStorage; }
    private:
        T& mStorage;
};
