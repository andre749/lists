#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(){
            data= T{};
            next=nullptr;
            prev=nullptr;
        }

        Node(T value){
            data = value;
            next=nullptr;
            prev=nullptr;
        }

        void killSelf(){
            if(prev!=nullptr) prev->next = next;
            if(next!=nullptr) next->prev = prev;
            delete this;
        }
    };

private:
    Node* head;
    Node* tail;
    int nodes;

public:
    DoubleList() : List<T>(), nodes(0), head(nullptr), tail(nullptr) {}

    ~DoubleList(){
        clear();
    }

    T front(){
        return head->data;
    }

    T back(){
        return tail->data;
    }

    void push_front(T data){
        if(head == nullptr){
            Node *nuevo = new Node(data);
            head = tail = nuevo;
            nodes++;
            return;
        }
        Node *temp = new Node(data);
        temp->next = head;
        head->prev = temp;
        head = temp;
        nodes++;
    }

    void push_back(T data){
        if(head == nullptr){
            Node *nuevo = new Node(data);
            head = tail = nuevo;
            nodes++;
            return;
        }
        Node *temp = new Node(data);
        temp->prev = tail;
        tail -> next = temp;
        tail = temp;
        nodes++;
    }

    T pop_front(){
        if(head==nullptr) return T{};
        Node *temp = head;
        T val= temp->data;
        head = head->next;
        if(head!=nullptr){
            head->prev=nullptr;
        }
        else{
            tail = nullptr;
        }
        delete temp;
        nodes --;
        return val;
    }

    T pop_back(){
        if(head==nullptr) return T{}; //si le pongo tail o head es lo mismo
        Node *temp = tail;
        T val= temp->data;
        tail = tail->prev;
        if(tail!=nullptr){
            tail->next=nullptr;
        }
        else{
            head = nullptr;
        }
        delete temp;
        nodes --;
        return val;
    }

    void insert(T data, int pos){
        if(pos > nodes or pos<0) return;
        Node *temp = new Node(data);
        if(pos == 0){
            push_front(data);
            delete temp;
            return;
        }

        if(pos==nodes){
            push_back(data);
            delete temp;
            return;
        }
        Node* actual = head;
        for (int i = 0; i < pos; i++) {
            actual = actual->next;
        }

        Node* anterior = actual->prev;
        anterior->next = temp;
        temp->prev = anterior;
        temp->next = actual;
        actual->prev = temp;
        nodes++;
    }

    void remove(int pos){
        if(head== nullptr) return; //si le pongo tail o head es lo mismo
        if(pos > nodes or pos<1) return;

        Node *eliminar = head;
        for(int i=0; i<pos; i++){
            eliminar = eliminar->next;
        }
        if(eliminar==head){
            pop_front();
            return;
        }
        if(eliminar==tail){
            pop_back();
            return;
        }

        Node *antes = eliminar->prev;
        Node *despues = eliminar->next;
        antes->next= despues;
        despues->prev= antes;
        delete eliminar;
        nodes--;
    }

    T& operator[](int pos){

        Node *nodo=head;
        for(int i=0; i<pos; i++){
            nodo = nodo->next;
        }
        return nodo->data;
    }

    bool is_empty(){
        return head== nullptr;
    }

    int size(){
        return nodes;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        nodes = 0;
    }
    void swap(Node *nodo1, Node *nodo2){ //no se necesita el nodo2 porque se puede sacar de nodo1
        if (nodo1 == nullptr || nodo2 == nullptr || nodo1->next != nodo2) return;

        Node *anterior_n1 = nodo1->prev;
        Node *siguiente_n2 = nodo2->next;
        if(anterior_n1!= nullptr) anterior_n1->next = nodo2;
        else {
            head = nodo2;
        }

        if (siguiente_n2!= nullptr) siguiente_n2->prev = nodo1;
        else{
            tail = nodo1;
        }

        nodo2->prev = anterior_n1;
        nodo2->next = nodo1;
        nodo1->next= siguiente_n2;
        nodo1->prev = nodo2;

    }
    void sort(){
        if (head == nullptr || nodes < 2) return;
        bool swapped;

        do {
            swapped = false;
            Node* current = head;
            while (current != nullptr && current->next != nullptr) {
                if (current->data > current->next->data) {
                    Node* nextNode = current->next;

                    swap(current, nextNode);
                    swapped = true;

                    if (current->prev) {
                        current = current->prev;
                    }
                } else {
                    current = current->next;
                }
            }
        } while (swapped);
    }

    bool is_sorted(){
        if(head == nullptr or head->next== nullptr){
            return true;
        }

        Node *n1 = head;
        while(n1->next!= nullptr){
            if(n1->data>n1->next->data) return false;
            n1 = n1->next;
        }
        return true;

    }

    void reverse(){
        if (head== nullptr or nodes ==1) return;
        Node* nuevo = head;
        Node* temp;

        while (nuevo!= nullptr) {
            temp = nuevo->prev;
            nuevo->prev = nuevo->next;
            nuevo->next = temp;
            nuevo = nuevo->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }


    std::string name(){
        return "ForwardList";
    }

    void print(){
        if(head== nullptr){
            cout<<"La lista esta vacia\n";
            return;
        }
        Node* it=head;
        while(it!= nullptr){
            cout<<it->data<<" ";
            it=it->next;
        }
        cout<<"\n";

    }

};
#endif