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
            Node *temp;
            while(head->next!= nullptr){
                temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = nullptr;
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
            if(head==nullptr) return;
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
            if(head==nullptr) return; //si le pongo tail o head es lo mismo
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
            Node *temp = new Node(data);
            if(head== nullptr){
                head = tail = temp;
                nodes++;
                return;
            }
            if(pos > nodes or pos<1) return;
            Node *antes = head;
            for(int i=0; i<pos-1; i++){
                antes = antes->next;
            }
            Node *despues = antes->next;
            antes->next = temp;
            temp->next =despues;
            despues->prev = temp;
            temp->prev = antes;
            nodes++;
        }

        void remove(int pos){
            if(head== nullptr) return; //si le pongo tail o head es lo mismo
            if(pos > nodes or pos<1) return;
            if(pos==1){
                this->pop_front();
                nodes--;
                return;
            }
            Node *eliminar = head;
            for(int i=0; i<pos; i++){
                eliminar = eliminar->next;
            }
            Node *antes = eliminar->prev;
            Node *despues = eliminar->next;
            eliminar->next= nullptr; eliminar->prev= nullptr;
            antes->next=despues;
            despues->prev=antes;
            delete eliminar;
            nodes--;
        }

        T& operator[](int pos){
            Node *nodo=head;
            for(int i=0; i<pos; i++){
                nodo = nodo->next;
            }
            T valor = nodo->data;
            return valor;
        }

        bool is_empty(){
            return head== nullptr;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while(head!=tail or head->next!=tail->prev){
                this->pop_front();
                this->pop_back();
            }
            if(head==tail){
                this->pop_front();
            }
            else{
                this->pop_back();
                this->pop_front();
            }
            nodes =0;
        }
        void swap(Node *nodo1, Node *nodo2){ //no se necesita el nodo2 porque se puede sacar de nodo1
            if(nodo1== nullptr or nodo2== nullptr) return;
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
            if(head == nullptr or nodes < 2) return;
            for(int i=0; i<nodes-1; i++){
                Node *actual = head;
                for(int j=0; j<nodes-(i+1); j++){
                    if(actual->data>actual->next->data){
                        swap(actual, actual->next);
                        actual = actual->prev;
                    }
                    actual=actual->next;
                }
            }

        }

        bool is_sorted(){
            if(nodes==1){
                return true;
            }
            if(nodes==2){
                return head->data<head->next->data;
            }
            bool vand = true;
            Node *n1 = head, *n2 = head->next;
            while(n2->next!= nullptr){
                if(n1->data>n2->data) return false;
                n1 = n1->next;
                n2 = n2->next;
            }
            return vand;

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