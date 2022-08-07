#pragma once
#include <iostream>
#include <initializer_list>
#include <memory>

using namespace std;

namespace hw7 {
    template <typename T>
    class LinkedList {
        class Node{
        public:
            Node():next(nullptr){}
            Node(T inData): next(nullptr), data(inData){}
            T data;
            unique_ptr<Node> next;
        };

        unique_ptr<Node> head;
        size_t elements = 0;
    public:

        LinkedList() = default;
        LinkedList(const LinkedList &obj) {
            auto current = obj.head.get();
            while(current != nullptr) {
                push_front(current->data);
                current = current->next.get();
            }
        }

        LinkedList& operator= (const LinkedList &obj) {
            if (this != &obj) {

                while(elements) {
                    pop_front();
                }

                auto current = obj.head.get();
                while(current != nullptr) {
                    push_front(current->data);
                    current = current->next.get();
                }
            }
            return *this;
        }

        LinkedList(LinkedList &&obj)noexcept : head(nullptr), elements(0) {
            elements = obj.elements;
            head = std::move(obj.head);
        }

        LinkedList& operator= (LinkedList &&obj){

            if (this != &obj) {
                while(elements) {
                    pop_front();
                }

                auto current = obj.head.get();
                while(current != nullptr) {
                    push_front(current->data);
                    current = current->next.get();
                }
            }
            return *this;
        }

        LinkedList(std::initializer_list<T> initList) {
            for(const auto &it: initList) {
                push_front(it);
            }
            elements = initList.size();
        }

        ~LinkedList() = default;

        void push_front(const T data) {
            auto tmp = make_unique<Node>(data);
            if (head == nullptr) {
                head = std::move(tmp);
            } else {
                tmp->next = std::move(head);
                head = std::move(tmp);
            }
            elements++;
        }

        void pop_front() {
            if(head == nullptr) {
                return;
            }
            auto tmp = std::move(head);
            head = std::move(tmp->next);
            elements--;
        }

        const size_t& size() const {
            return elements;
        }

        const T& operator [](int indx) {
            auto current = head.get();
            for (auto i = 0; i<indx; i++) {
                current = current->next.get();
            }
            return current->data;
        }

        class iterator {
            friend class LinkedList;
            Node *nodePtr;
            iterator(Node *newPtr): nodePtr(newPtr) {}
        public:
            iterator() : nodePtr(nullptr) {}
            T& operator*() const {
                return nodePtr->data;
            }

            iterator operator++(int) {
                iterator temp = *this;
                nodePtr = nodePtr->next;
                return temp;
            }

            bool operator!=(const iterator& itr) const {
                return nodePtr != itr.nodePtr;
            }

            iterator& operator++()
            {
                if (nodePtr != nullptr) {
                    nodePtr = nodePtr->next.get();
                }
                return *this;
            }
        };

        iterator begin() const {
            return iterator(head.get());
        }

        iterator end() const {
            return iterator(nullptr);
        }
    };
};