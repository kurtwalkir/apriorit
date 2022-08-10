#pragma once
#include "shared_ptr.h"

using namespace hw6_s;

namespace hw6_w {

    template <typename T>
    class weak_ptr
    {
        shared_ptr<T> *ptr;

    public:
        weak_ptr(): ptr( new shared_ptr<T>{}){}

        weak_ptr(weak_ptr<T> &sharedPtr): ptr(&sharedPtr){}
        weak_ptr(const weak_ptr<T> &weakPtr): ptr(weakPtr.ptr){}
        weak_ptr(weak_ptr<T>&& weakPtr):ptr(weakPtr.m_sharedPtr) {
            weakPtr.ptr = new shared_ptr<T>();
        }

        weak_ptr<T>& operator=(shared_ptr<T>& obj) {
            ptr = &obj;
        }
        weak_ptr<T>& operator=(const weak_ptr<T>& weakPtr) {
            ptr = weakPtr.ptr;
        }
        weak_ptr<T>& operator=(weak_ptr<T>&& weakPtr) {
            ptr = weakPtr.m_sharedPtr;
            weakPtr.ptr = new weak_ptr<T>{};
        }

        weak_ptr<T>& lock() {
            return *ptr;
        }

        size_t use_counter(){
            return ptr->use_counter();
        }
    };
}
