#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class CircularList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(){

        }

        Node(T value){
            data = value;
        }

        void killSelf(){
            delete this;
        }
    };

private:
    Node* head;//sentinel
    int nodes;

public:
    CircularList() : List<T>() {
        head = new Node();
        head->next = head;
        head->prev = head;

        nodes = 0;
    }

    ~CircularList(){
        // TODO
    }

    T front(){
        return head->next->data;
    }

    T back(){
        return head->prev->data;
    }

    void push_front(T data){
        Node *nuevo = new Node(data);

        head->next->prev = nuevo;
        nuevo->next = head->next;
        head->next = nuevo;
        nuevo->prev = head;

        ++nodes;
    }

    void push_back(T data){
        Node *nuevo = new Node(data);

        head->prev->next = nuevo;
        nuevo->prev = head->prev;
        nuevo->next = head;
        head->prev = nuevo;

        ++nodes;
    }

    T pop_front(){
        if (is_empty()) {
            throw std::out_of_range("La lista está vacía");
        }

        Node *temp = head->next;
        T temp_value = temp->data;

        temp->next->prev = head;
        head->next = temp->next;

        --nodes;
        delete temp;
        return temp_value;
    }

    T pop_back(){
        if (is_empty()) {
            throw std::out_of_range("La lista está vacía");
        }

        Node *temp = head->prev;
        T temp_value = temp->data;

        temp->prev->next = head;
        head->prev = temp->prev;

        --nodes;
        delete temp;
        return temp_value;
    }

    bool insert(T data, int pos){
        Node *temp = head;
        if (pos < 0 || pos > nodes) return false;

        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }

        Node *nuevo = new Node(data);
        nuevo->next = temp->next;
        nuevo->prev = temp;
        temp->next->prev = nuevo;
        temp->next = nuevo;

        ++nodes;
        return true;
    }

    bool remove(int pos){
        if (pos < 0 || pos >= nodes) return false;

        Node* temp = head->next;
        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
        --nodes;
        return true;
    }

    T& operator[](int pos){
        Node *temp = head->next;
        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool is_empty(){
        return head->next == head;
    }

    int size(){
        return nodes;
    }

    void clear(){
        while (!is_empty()) {
            pop_front();
        }
    }

    Node* split(Node* primera) {
        Node* slow = primera;
        Node* fast = primera;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* segunda = slow->next;
        slow->next = nullptr;
        if (segunda) segunda->prev = nullptr;
        return segunda;
    }

    Node* mergeSort(Node* node) {
        if (!node || !node->next) return node;

        Node* segunda = split(node);

        Node* left = mergeSort(node);
        Node* right = mergeSort(segunda);

        return merge(left, right);
    }

    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;

        if (a->data < b->data) {
            a->next = merge(a->next, b);
            if (a->next) a->next->prev = a;
            a->prev = nullptr;
            return a;
        } else {
            b->next = merge(a, b->next);
            if (b->next) b->next->prev = b;
            b->prev = nullptr;
            return b;
        }
    }

    void sort(){
        if (nodes <= 1) return;

        Node* first = head->next;
        head->prev->next = nullptr;
        first->prev = nullptr;

        Node* sorted = mergeSort(first);

        head->next = sorted;
        sorted->prev = head;

        Node* temp = sorted;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = head;
        head->prev = temp;
    }

    bool is_sorted(){
        if (is_empty() || nodes == 1) return true;

        Node* temp = head->next;

        while(temp->next != head){
            if(temp->data > temp->next->data){
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    void reverse(){
        if (is_empty() || nodes == 1) return;

        Node* actual = head->next;

        while (actual != head){
            Node* temp = actual->next;
            actual->next = actual->prev;
            actual->prev = temp;
            actual = temp;
        }

        Node* temp = head->next;
        head->next = head->prev;
        head->prev = temp;
    }

    std::string name(){
        return "Circular Doubly Linked";
    }
};

#endif