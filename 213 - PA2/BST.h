#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void copy(BSTNode<T> *& lhs, BSTNode<T> *rhs);
    void destruct(BSTNode<T> *& node);
    bool contains_help(BSTNode<T> *root, BSTNode<T> *node) const;
    void insert_help(BSTNode<T> *& root, const T &data);
    void remove_help(BSTNode<T> *& root, T data);
    T getMinOfRight(BSTNode<T> *node);
    BSTNode<T> *searcher(BSTNode<T> *root, const T &data) const;
    bool there_is(BSTNode<T> *root, const T &data) const;
    void getSuc(BSTNode<T> *root, BSTNode<T> *&suc, BSTNode<T> *node, TraversalPlan tp, bool &found) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    /* TODO */
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    if(obj.getRoot() == NULL){
        root = NULL;
    }
    else
        copy(root, obj.getRoot());
}
template<class T>
void BST<T>::copy(BSTNode<T> *& lhs, BSTNode<T> *rhs){
    if(rhs != NULL){
        lhs = new BSTNode<T>(rhs->data, NULL, NULL);
        copy(lhs->left, rhs->left);
        copy(lhs->right, rhs->right);
    }
    else 
        lhs = NULL;
}

template<class T>
BST<T>::~BST() {
    /* TODO */
    destruct(root);
    root = NULL;
}

template<class T>
void BST<T>::destruct(BSTNode<T> *& node){
    if(node != NULL){
        destruct(node -> left);
        destruct(node -> right);
        if(node -> left == NULL && node -> right == NULL){
            delete node;
            node = NULL;
        }
    }
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    if(root == NULL)
        return true;
    else
        return false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    /* TODO */
    return contains_help(root, node);
}

template<class T>
bool BST<T>::contains_help(BSTNode<T> *root, BSTNode<T> *node) const{
    /* TODO */
    if(root == NULL){
        return false;
    }
    if(node == root){
        return true;
    }
    return contains_help(root -> left, node) || contains_help(root -> right, node);
}

template<class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    insert_help(root, data);
}

template<class T>
void BST<T>::insert_help(BSTNode<T> *& root, const T &data) {
    /* TODO */
    if(root == NULL){
        root = new BSTNode<T>(data, NULL, NULL);
        return;
    }
    else{
        if(data < root -> data)
            insert_help(root -> left, data);
        else if(data > root -> data)
            insert_help(root -> right, data);
    }
}

template<class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    remove_help(root, data);
}

template<class T>
void BST<T>::remove_help(BSTNode<T> *& root, T data) {
          if (root == NULL)
             return;
          else if (root->data > data)
             remove_help(root->left, data);
          else if (root->data < data)
             remove_help(root->right , data);
          else  
             if (root->left != NULL && root->right != NULL) {
                root->data = getMinOfRight(root->right);
                remove_help(root->right, root->data);
               }
             else {
                BSTNode<T> * tmp = root;
                root = (root->left != NULL)? root->left : root->right;
                delete tmp;
             }
        }

template<class T>
T BST<T>::getMinOfRight(BSTNode<T> *node){
    if(node -> left){
        return getMinOfRight(node -> left);
    }
    else{
        return  node -> data;
    }
}


template<class T>
void BST<T>::removeAllNodes() {
    /* TODO */
    if(root == NULL)
        return;
    destruct(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    /* TODO */
    if(root == NULL)
        return NULL;
    return searcher(root, data);
}

template<class T>
BSTNode<T> *BST<T>::searcher(BSTNode<T> *root, const T &data) const{
    if(root == NULL)
        return NULL;
    if(root -> data == data){
        return root;
    }
    else if(there_is(root -> left, data)){
        return searcher(root -> left, data);
    }
    else if(there_is(root -> right, data)){
        return searcher(root -> right, data);
    }
    else{
        return NULL;
    }
}


template<class T>
bool BST<T>::there_is(BSTNode<T> *root, const T &data) const{
    if(root == NULL){
        return false;
    }
    if(root -> data == data){
        return true;
    }
    return there_is(root -> left, data) || there_is(root -> right, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) {
        /* TODO */
        BSTNode<T> *suc = NULL;
        bool ch = 0;
        getSuc(root, suc, node, inorder, ch);
        return suc;
    } 
    else if (tp == preorder) {
        /* TODO */
        BSTNode<T> *suc = NULL;
        bool ch = 0;
        getSuc(root, suc, node, preorder, ch);
        return suc;
    } 
    else if (tp == postorder) {
        /* TODO */
        BSTNode<T> *suc = NULL;
        bool ch = 0;
        getSuc(root, suc, node, postorder, ch);
        return suc;
    }
}

template<class T>
void BST<T>::getSuc(BSTNode<T> *root, BSTNode<T> *&suc, BSTNode<T> *node, TraversalPlan tp, bool &found) const{
    if (tp == inorder) {
        if(root == NULL){
            return;
        }
        getSuc(root -> left, suc, node, inorder, found);
        if(found){
            suc = root;
            found = 0;
            return;
        }
        if(root == node){
            found = 1;
        }
        getSuc(root -> right, suc, node, inorder, found);
    } 
    else if (tp == preorder) {
        if(root == NULL){
            return;
        }
        if(found){
            suc = root;
            found = 0;
            return;
        }
        if(root == node){
            found = 1;
        }
        getSuc(root -> left, suc, node, preorder, found);
        getSuc(root -> right, suc, node, preorder, found);
    } 
    else if (tp == postorder) {
        if(root == NULL){
            return;
        }
        getSuc(root -> left, suc, node, postorder, found);
        getSuc(root -> right, suc, node, postorder, found);
        if(found){
            suc = root;
            found = 0;
            return;
        }
        if(root == node){
            found = 1;
        }
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    destruct(root);
    copy(root, rhs.root);
}


template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    else if (tp == preorder) {
        /* TODO */
        std::cout << "\t" << node->data;
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } 
    else if (tp == postorder) {
        /* TODO */
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->data;
    }
}