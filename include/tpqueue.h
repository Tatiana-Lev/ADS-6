// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
struct SYM {
    char ch;
    int prior;
};
template<typename T>
class TPQueue {
    private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* head;

    public:
    TPQueue() : head(nullptr) {}
    ~TPQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    TPQueue(const TPQueue&) = delete;
    TPQueue& operator=(const TPQueue&) = delete;
    void push(const T& val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        if (val.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr &&
            current->next->data.prior >= val.prior) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    T pop() {
        if (head == nullptr) {
            return T{};
        }
        T result = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return result;
    }
};
#endif  // INCLUDE_TPQUEUE_H_
