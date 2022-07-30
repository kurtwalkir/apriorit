
/* Suggest to use namespace std */

#ifndef CODEREVIEWTASK_MYVECTOR_HPP /* Better to use #pragma once */
#define CODEREVIEWTASK_MYVECTOR_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

/*
 * MyVector stores a collection of objects with their names.
 *
 * For each object T, MyVector stores T`s name as std::string.
 * Several objects can have similar name.
 * operator[](const std::string& name) should return the first object
 * with the given name.
 *
 * Your task is to find as many mistakes and drawbacks in this code
 * (according to the presentation) as you can.
 * Annotate these mistakes with comments.
 *
 * Once you have found all the mistakes, rewrite the code
 * so it would not change its original purpose
 * and it would contain no mistakes.
 * Try to make the code more efficient without premature optimization.
 *
 * You can change MyVector interface completely, but there are several rules:
 * 1) you should correctly and fully implement copy-on-write idiom.
 * 2) std::pair<const T&, const std::string&> operator[](int index) const must take constant time at worst.
 * 3) const T& operator[](const std::string& name) const should be present.
 * 4) both operator[] should have non-const version.
 * 5) your implementation should provide all the member types of std::vector.
 * 6) your implementation should provide the following functions:
 *    1) begin(), cbegin(), end(), cend()
 *    2) empty(), size()
 *    3) reserve(), clear()
 */

template <typename T>
class MyVector : public std::vector<T> /* Avoid inheritance from vector class, prefer associations */
{
public:
    MyVector()
    {
        m_ref_ptr = new size_t(1);
        m_names = new std::vector<std::string>(); /* Memory leak in case of exception bad_alloc for m_ref_ptr */
    }

    /* Please implement Move ctr and assignment */
    MyVector(const MyVector& other)
        : std::vector<T>(other),
          m_ref_ptr(other.m_ref_ptr),
          m_names(other.m_names)
    {
        (*m_ref_ptr)++; /* Better to check pointer for nullptr before dereference */
    }

    ~MyVector()
    {
        if (--*m_ref_ptr == 0)
        {
            delete m_ref_ptr; /* Possible memory leak place */
            delete m_names;
        }
    }

    void push_back(const T& obj, const std::string& name)
    {
        copy_names();

        std::vector<T>::push_back(obj); /* Better to use vector inside class */
        m_names->push_back(name);
    }

    std::pair<const T&, const std::string&> operator[](int index) const
    {
        if (index >= std::vector<T>::size()) /* Better to use vector inside class */
        {
            throw new std::out_of_range("Index is out of range"); /* Dont allocate memory for an exception, no one will free this memory */
        }

        return std::pair<const T&, const std::string&>(std::vector<T>::operator[](index), (*m_names)[index]); /* Better to check pointer m_names for nullptr before dereference */
    }

    const T& operator[](const std::string& name) const
    {
        std::vector<std::string>::const_iterator iter = std::find(m_names->begin(), m_names->end(), name);
        if (iter == m_names->end())
        {
            throw new std::invalid_argument(name + " is not found in the MyVector"); /* Dont allocate memory for an exception, no one will free this memory */
        }

        return std::vector<T>::operator[](iter - m_names->begin()); /* Better to use vector inside class */
    }

private:
    void copy_names()
    {
        if (*m_ref_ptr == 1) /* Should be check of shared ptr */
        {
            return;
        }

        size_t* temp_ref_ptr = new size_t(1);
        std::vector<std::string>* temp_names = new std::vector<std::string>(*m_names); /* make shared pointer */

        (*m_ref_ptr)--;
        m_ref_ptr = temp_ref_ptr;
        m_names = temp_names;
    }

private:
    // Use copy-on-write idiom for efficiency (not a premature optimization)
    std::vector<std::string>* m_names; /* Use shared pointer, in this case we should not use m_ref_ptr */
    size_t* m_ref_ptr;
};


#endif //CODEREVIEWTASK_MYVECTOR_HPP

/* ------------------- Fix result -------------------------------------------- */

using namespace std;
#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>


template <typename T>
class MyVector
{
public:
    MyVector(): m_names(make_shared<vector<string>>()){}

    MyVector(const MyVector& other) : objects(other.objects),
          m_names(other.m_names) {}

    MyVector& operator=(const MyVector& other)
    {
         objects = other.objects;
         m_names = other.m_names;
         return *this;
    }

    MyVector(MyVector &&other) noexcept
    {
        objects = other.objects;
        m_names = other.m_names;
    }

    ~MyVector() = default;

    void push_back(const T& obj, const string& name)
    {
        copy_names();

        objects.push_back(obj);
        m_names->push_back(name);
    }

    pair<const T&, const string&> operator[](int index) const
    {
        if (index >= objects.size())
        {
            throw out_of_range("Index is out of range");
        }

        return pair<const T&, const string&>(objects.operator[](index), (*m_names)[index]);
    }

    T& operator[](const string& name)
    {
        std::vector<string>::const_iterator iter = find(m_names->begin(), m_names->end(), name);
        if (iter == m_names->end())
        {
            throw invalid_argument(name + " is not found in the MyVector");
        }

        return objects.operator[](iter - m_names->begin());
    }

private:
    void copy_names()
    {
        if (m_names.unique()) { return;}

        std::cout<<"Copy"<<endl;
        shared_ptr<vector<string>> temp_names = make_shared<vector<string>>(*m_names);
        m_names = temp_names;
    }

    std::shared_ptr<vector<string>> m_names;
    std::vector<T> objects; /* According to the task copy-on-write idiom we should use this approach only for names */
};


/*
int main() {

    MyVector<int> vec1;
    vec1.push_back(1, "val1");
    vec1.push_back(2, "val2");
    vec1.push_back(3, "val3");
    MyVector<int> vec2 (vec1);

    MyVector<int> vec3;
    vec3 = vec1;

    try {
        vec2.push_back(4, "val4");
        vec1["val4"];
    } catch(const exception & e) {
        cout<<e.what();
    }
}
*/