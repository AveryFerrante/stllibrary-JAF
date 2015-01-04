#ifndef AVLTREE_H
#define AVLTREE_H

#include <cstddef>

template<typename _T> class AVLTree
{

private: // node struct

    struct Node
    {
    public: // Member variables, the rest of the class needs to be able to access these directly still
        _T __data;
        Node* __right;
        Node* __left;

    public: // Constructors & Destructors to make creation easier
        Node(_T &info)
        {
            __data = info;
            __right = NULL;
            __left = NULL;
        }

    };


private: // Member variables

    Node* _root;

private: // Utility functions

    void buildTree(Node* root, Node* toAdd)
    {

    }



public: // Constructors & Destructors
    AVLTree(_T info) // Cannot have empty avl tree, the user must provide an initial root.
    {
        _root = new Node(info);
    }



public: // User functionality

    void add(_T info)
    {


    }


};

#endif // AVLTREE_H
