#pragma once
#include <cstddef>
#include <utility>

template <typename T> class MySharedPtr {
  public:
    template <typename... Args> MySharedPtr(Args&&... args) {
        ptr_ = new T(std::forward<Args>(args)...);
        ctrl_ = new ControlBlock(); // strong_count = 1
    }

    MySharedPtr(const MySharedPtr& other) {
        ptr_ = other.ptr_;
        ctrl_ = other.ctrl_;
        if (ctrl_)
            ctrl_->strong_count++;
    }

    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            ctrl_ = other.ctrl_;
            if (ctrl_)
                ctrl_->strong_count++;
        }
        return *this;
    }

    ~MySharedPtr() { release(); }

  private:
    struct ControlBlock {
        size_t strong_count{1};
    };

    void release() {
        if (ctrl_) {
            ctrl_->strong_count--;
            if (ctrl_->strong_count == 0) {
                delete ptr_;
                delete ctrl_;
            }
        }
    }

    T* ptr_;
    ControlBlock* ctrl_;
};
