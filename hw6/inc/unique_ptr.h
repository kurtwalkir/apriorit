#pragma once
#include <iostream>

using namespace std;

namespace hw6_u
{
    template<typename T>
    class unique_ptr
    {
        T*   data;
        public:
            unique_ptr() : data(nullptr) {}
            explicit unique_ptr(T* data) : data(data) {}
            ~unique_ptr()
            {
                delete data;
            }

            unique_ptr(std::nullptr_t): data(nullptr) {}
            unique_ptr& operator=(std::nullptr_t)
            {
                reset();
                return *this;
            }

            unique_ptr(unique_ptr&& moving) noexcept : data(nullptr)
            {
                moving.swap(*this);
            }
            unique_ptr& operator=(unique_ptr&& moving) noexcept
            {
                moving.swap(*this);
                return *this;
            }

            template<typename U>
            unique_ptr(unique_ptr<U>&& moving)
            {
                unique_ptr<T> tmp(moving.release());
                tmp.swap(*this);
            }
            template<typename U>
            unique_ptr& operator=(unique_ptr<U>&& moving)
            {
                unique_ptr<T>    tmp(moving.release());
                tmp.swap(*this);
                return *this;
            }

            unique_ptr(unique_ptr const&) = delete;
            unique_ptr& operator=(unique_ptr const&) = delete;

            T* operator->() const {return data;}
            T& operator*()  const {return *data;}

            T* get() const {return data;}
            explicit operator bool() const {return data;}

            T* release() noexcept
            {
                T* result = nullptr;
                std::swap(result, data);
                return result;
            }
            void swap(unique_ptr& src) noexcept
            {
                std::swap(data, src.data);
            }
            void reset()
            {
                T* tmp = release();
                delete tmp;
            }
    };
    template<typename T>
    void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs)
    {
        lhs.swap(rhs);
    }
}
