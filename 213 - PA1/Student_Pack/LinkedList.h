#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
    Node<T> *cur = obj.getFirstNode();
    size = obj.getSize();
    if(obj.getSize() == 0){
        head = NULL;
    }
    else{
        head = new Node<T>(cur -> data);
        Node<T> *tmp = head;
        Node<T> *tra = head;
        cur = cur -> next;
        while(cur != obj.getFirstNode()){
            tra -> next = new Node<T>(cur -> data);
            tra = tra -> next;
            tra -> prev = tmp;
            tmp = tmp -> next;
            cur = cur -> next;
        }
        tra -> next = head;
        head -> prev = tra;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    removeAllNodes();
}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    int count = 1;
    Node<T> *cur = head;
    if(head == NULL)
        return 0;
    while(cur -> next != head){
        count++;
        cur = cur -> next;
    }
    return count;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    if(head == NULL){
        return true;
    }
    else
        return false;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    Node<T> *cur = head;
    if(head == NULL){
        return false;
    }
    while(cur -> next != head){
        if(cur == node)
            return true;
        cur = cur -> next;
    }
    if(cur != node)
        return false;
    else
        return true;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
    if(head == NULL)
        return NULL;
    else
        return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    if(head == NULL)
        return NULL;
    return head -> prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    Node<T> *cur = head;
    if(head == NULL || head -> data == data){
        return getFirstNode();
    }
    do{
        if(cur -> data == data)
            return cur;
        cur = cur -> next;
    }while(cur != head);
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
    int i = 0;
    Node<T> *cur = head;
    if(index >= size || index < 0 || head == NULL)
        return NULL;
    do{
        if(i == index)
            return cur;
        i++;
        cur = cur -> next;
    }while(cur != head);
    return NULL;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */
    Node<T> *ins = new Node<T>(data);
    size++;
    if(isEmpty()){
        ins -> next = ins;
        ins -> prev = ins;
        head = ins;
    }
    else{
        Node<T> *back = head -> prev;
        ins -> next = head;
        ins -> prev = back;
        back -> next = ins;
        head -> prev = ins;
        head = ins;
    }
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */
    
    Node<T> *ins = new Node<T>(data);
    size++;
    if(isEmpty()){
        ins -> next = ins;
        ins -> prev = ins;
        head = ins;
    }
    else{
        Node<T> *back = head -> prev;
        ins -> next = head;
        ins -> prev = back;
        back -> next = ins;
        head -> prev = ins;
    }
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    Node<T> *cur = head;
    if(head != NULL && contains(node)){
        Node<T> *ins = new Node<T>(data);
        size++;
        while(cur != node){
            cur = cur -> next;
        }
        ins -> prev = cur;
        ins -> next = cur -> next;
        cur -> next = ins;
        cur = ins -> next;
        cur -> prev = ins;
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
    
    if(k > 1 && head != NULL){
        Node<T> *cur = head;
        int i = 0;
        do{
            if(i % k == k - 2){
                Node<T> *ins = new Node<T>(data);
                ins -> prev = cur;
                ins -> next = cur -> next;
                cur -> next = ins;
                cur = ins -> next;
                cur -> prev = ins;
                size++;
                i = 0;
            }
            else{
                cur = cur -> next;
                i++;
            }
        }while(cur != head);
    }
    
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    
    Node<T> *cur = head;
    if(contains(node)){
        if(head == node){
            if(getSize() == 1){
                delete head;
                head = NULL;
            }
            else{
                Node<T> *tmp = head;
                cur = cur -> prev;
                cur -> next = cur -> next -> next;;
                cur = cur -> next;
                cur -> prev = tmp -> prev;
                delete tmp;
                head = cur;
            }
        }
        else{
            while(cur -> next != node){
                cur = cur -> next;
            }
            Node<T> *tmp = cur -> next;
            cur -> next = cur -> next -> next;;
            cur = cur -> next;
            cur -> prev = tmp -> prev;
            delete tmp;
        }
        size--;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
    Node<T> *cur = head;
    if(head != NULL){
        if(head -> data == data){
            if(getSize() == 1){
                delete head;
                head = NULL;
            }
            else{
                Node<T> *tmp = head;
                cur = cur -> prev;
                cur -> next = cur -> next -> next;;
                cur = cur -> next;
                cur -> prev = tmp -> prev;
                delete tmp;
                head = cur;
            }
            size--;
        }
        else{
            bool exists = true;
            while(cur -> next -> data != data){
                if(cur == head){
                    exists = false;
                    break;
                }
                cur = cur -> next;
            }
            if(exists){
                Node<T> *tmp = cur -> next;
                cur -> next = cur -> next -> next;;
                cur = cur -> next;
                cur -> prev = tmp -> prev;
                delete tmp;
                size--;
            }
        }
    }
    
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    while(!isEmpty()){
        removeNode(head);
    }
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    if(k > 1 && head != NULL){
        Node<T> *cur = head;
        int i = 0;
        do{
            if(i % k == k - 2 && cur -> next != head){
                this -> removeNode(cur -> next);
                i++;
                size--;
            }
            cur = cur -> next;
            i++;
        }while(cur != head);
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */
    if(contains(node1) && contains(node2)){
        Node<T> *cur1 = head, *cur2 = head;
        while(cur1 -> next != node1){
            cur1 = cur1 -> next;
        }
        while(cur2 -> next != node2){
            cur2 = cur2 -> next;
        }
        cur1 -> next = node2;
        node2 -> prev = cur1;
        cur2 -> next = node1;
        node1 -> prev = cur2;
        cur1 = cur1 -> next -> next;
        cur2 = cur2 -> next -> next;
        cur1 -> prev = node1;
        node1 -> next = cur1;
        cur2 -> prev = node2; 
        node2 -> next = cur2;
        if(node1 == head){
            head = node2;
        }
        else if(node2 == head){
            head = node1;
        }
    }
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    if(head != NULL){
        for(int i = 0; i < size; i++){
            if(i != (i*i + seed) % size){
                swap(getNodeAtIndex(i), getNodeAtIndex((i*i + seed) % size));
            }
        }
    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    Node<T> *cur = rhs.getFirstNode();
    removeAllNodes();
    if(rhs.getSize() == 0){
        head = NULL;
    }
    else{
        head = new Node<T>(cur -> data);
        Node<T> *tmp = head;
        Node<T> *tra = head;
        cur = cur -> next;
        while(cur != rhs.getFirstNode()){
            tra -> next = new Node<T>(cur -> data);
            tra = tra -> next;
            tra -> prev = tmp;
            tmp = tmp -> next;
            cur = cur -> next;
        }
        tra -> next = head;
        head -> prev = tra;
    }
    size = rhs.getSize();
    return *this;
}

#endif //LINKEDLIST_H
