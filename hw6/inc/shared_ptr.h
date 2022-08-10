
#pragma once
#include <iostream>

namespace hw6_s {
    template <class T>
    class shared_ptr {
        T* ptr;
        int* ref_count;

        void initialize_ref_count() {
            if (ref_count != nullptr)
                return;
            try {
                ref_count = new int;
                *ref_count = 1;
            }
            catch (std::bad_alloc& e) {
                std::cerr << "Memory allocation error: " << e.what();
            }
        }

    public:
        shared_ptr() : ptr(nullptr), ref_count(nullptr) {}
        shared_ptr(nullptr_t ptr) : ptr(ptr), ref_count(nullptr) {}
        shared_ptr(T* ptr) : ptr(ptr), ref_count(nullptr) {
            initialize_ref_count();
        }

        ~shared_ptr() {
            --(*ref_count);
            if (*ref_count == 0) {
                delete ref_count;
                ref_count = nullptr;
                delete ptr;
                ptr = nullptr;
            }
        }

        shared_ptr(const shared_ptr& copy) {
            ptr = copy.ptr;
            ref_count = copy.ref_count;
            if (ref_count != nullptr) {
                ++(*ref_count);
            }
        }

        shared_ptr& operator=(const shared_ptr& copy) {
            ptr = copy.ptr;
            ref_count = copy.ref_count;
            if (ref_count != nullptr) {
                ++(*ref_count);
            }
            return *this;
        }

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }
    };
}