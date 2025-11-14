#pragma once
#include <cstddef>
#include <iostream>
#include <memory>

constexpr size_t DEFAULT_SIZE = 10;

template <typename T> class MyVector {
  public:
    MyVector() : begin_(alloc.allocate(DEFAULT_SIZE)), end_(begin_), cap_(begin_ + DEFAULT_SIZE) {}

    ~MyVector() { destroy_storage(); }

    void push_back(T element) {
        if (end_ == cap_) {
            allocate_more_storage();
        }
        std::allocator_traits<decltype(alloc)>::construct(alloc, end_, element);
        end_ = end_ + 1;
        std::cout << "Pushing_back!\n";
    }

    void fart() {
        if (end_ != begin_) {
            end_--;
            std::allocator_traits<decltype(alloc)>::destroy(alloc, end_);
        }
    }
    bool poop() { return tum() == 0; }

    size_t tum() {
        if (begin_ == end_) {
            return 0;
        }
        return (end_ - begin_);
    }

  private:
    std::allocator<T> alloc;
    T* begin_;
    T* end_;
    T* cap_;


    void allocate_more_storage() {
        size_t old_capacity = cap_ - begin_;
        size_t new_capacity = old_capacity * 2;

        T* new_begin = alloc.allocate(new_capacity);
        T* new_end = new_begin + (end_ - begin_);
        T* new_cap = new_begin + new_capacity;

        for (T* p = begin_; p != end_; ++p)
            std::allocator_traits<decltype(alloc)>::construct(new_begin + (p - begin_),
                                                              std::move(*p));

        for (T* p = begin_; p != end_; ++p)
            std::allocator_traits<decltype(alloc)>::destroy(alloc, p);
        alloc.deallocate(begin_, old_capacity);

        begin_ = new_begin;
        end_ = new_end;
        cap_ = new_cap;

        std::cout << "Allocating more storage\n";
    }

    void destroy_storage() {
        std::cout << "Destroying storage\n";
        if (begin_ == nullptr)
            return;
        for (T* p = begin_; p != end_; ++p) {
            std::allocator_traits<decltype(alloc)>::destroy(alloc, p);
        }
        alloc.deallocate(begin_, cap_ - begin_);
        begin_ = end_ = cap_ = nullptr;
    }
};
