#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"

using namespace std;
// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
    private:
        struct Node {
            T data;
            Node* next;

            Node():data(T{}),next(nullptr){
            }

            explicit Node(T value):data(value),next(nullptr){

            }

            void killSelf() {
                delete this;
            }
        };

    private:
        Node* head;
        int nodes;

    public:
        ForwardList() : nodes(0),head(nullptr) {}

        ~ForwardList(){
            Node* temp;
         	while(head!=nullptr){
                 temp=head;
                 head=head->next;
                 delete temp;
             }
        }

        T front(){
            return head->data;
        }

        T back(){
            Node* it=head;
            while(it->next!= nullptr){
                it->next;
            }
            return it->data;
        }

        void push_front(T data){
            Node* nh=new Node(data);
            nh->next=head;
            head=nh;
            nodes++;
        }

        void push_back(T data){
            if(head== nullptr) {
                head = new Node(data);
                return;
            }
            if(head->next==nullptr){
                head->next=new Node(data);
                nodes++;
                return;
            }
            auto it=head->next;
            while (it->next!= nullptr){
                it=it->next;
            }
            it->next=new Node(data);
            nodes++;
        }

        T pop_front(){
            Node* temp=head;
            head=head->next;
            T ret=temp->data;
            delete temp;
            nodes--;
            return ret;

        }

        T pop_back(){
            if(head== nullptr){
                return 0;
            }
            T ret;
            if(head->next==nullptr){
                ret=head->data;
                delete head;
                head=nullptr;

                nodes--;

                return ret;
            }
            auto it=head;
            while (it->next->next!= nullptr){
                it=it->next;
            }
            ret=it->next->data;
            delete it->next;
            it->next=nullptr;
            nodes--;
            return ret;
        }

        bool insert(T data, int pos){
            if(pos>nodes+1)return false;

            if (pos==0){
                this->push_front(data);
                return true;
            }
            Node* it=head;
            for(int i=1;i<pos;i++){
                it=it->next;
            }
            Node* nn=new Node(data);
            nn->next=it->next;
            it->next=nn;
            nodes++;
            return true;

        }

        bool remove(int pos){
            if(pos>nodes) return false;
            if (pos==0){
                this->pop_front();
                return true;
            }
            Node*it=head,*temp= head;
            for(int i=0;i<pos;i++){
                temp=it;
                it=it->next;
            }
            temp->next=it->next;
            nodes--;
            delete it;
        }

        T& operator[](int pos){
            Node*it=head;
            for(int i=0;i<pos;i++){
                it=it->next;
            }
            return it->data;
        }

        bool is_empty(){
            return nodes==0;
        }

        int size(){
            return nodes;
        }

        void clear(){
            Node* temp;
            while(head!=nullptr){
                temp=head;
                head=head->next;
                delete temp;
            }
            nodes=0;
        }
        
        void sort(){
            Node *new_head = new Node();

            if(T{}==0)
                new_head->data=-1073741824;

            new_head->next=head;
            head=new_head;
            nodes++;
            Node* it1=head,*it2=nullptr,*it3=head,*temp=nullptr;
            while(it1->next ){
                it2=it1;
                it1=it1->next;
                if(it1->data<it2->data){
                    it2->next=it1->next;
                    while(it3!=it2){
                        if(it1->data<it3->next->data){
                            temp=it3->next;
                            it3->next=it1;
                            it1->next=temp;
                            break;
                        }
                        it3=it3->next;
                    }
                    it3=head;
                }
            }
            this->pop_front();
        }

        bool is_sorted(){
            if(nodes<2){
                return true;
            }
            if(nodes==2){
                return head->data<head->next->data;
            }
            Node* it=head;

            while(it-> next!= nullptr){
                if(it->data>it->next->data)
                    return false;
                it=it->next;

            }
            return true;
        }

        void reverse(){
            Node* leftNode=head,*prev=nullptr,*rv=nullptr,
                    *rvTail=nullptr,*leftSideList=nullptr,*rightSideList=nullptr,*rightNode=nullptr;
            rvTail=leftNode;
            for(int i=0;i<=nodes;i++){
                prev=leftNode;
                leftNode=leftNode->next;
                prev->next=rv;
                rv=prev;
            }
            head=rv;
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