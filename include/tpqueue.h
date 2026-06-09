// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
    char ch;
    int prior;
};

template<typename T>
class TPQueue {
 public:
    TPQueue() : head_(nullptr), count_(0) {}

    ~TPQueue() {
        while (head_ != nullptr) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
    }

    void push(const T& item) {
        Node* new_node = new Node(item);

        if (isEmpty()) {
            head_ = new_node;
        } else if (item.prior > head_->data.prior) {
            new_node->next = head_;
            head_ = new_node;
        } else {
            Node* current = head_;
            // Ищем место для вставки
            while (current->next != nullptr &&
                   current->next->data.prior >= item.prior) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
        count_++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = head_;
        T result = head_->data;
        head_ = head_->next;
        delete temp;
        count_--;
        return result;
    }

    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return head_->data;
    }

    bool isEmpty() const {
        return head_ == nullptr;
    }

    int size() const {
        return count_;
    }

    void clear() {
        while (head_ != nullptr) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
        count_ = 0;
    }

 private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head_;
    int count_;
};
#endif  // INCLUDE_TPQUEUE_H_
