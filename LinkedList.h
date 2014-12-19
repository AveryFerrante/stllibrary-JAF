// Created by Joseph Avery Ferrante on 12/18/14

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstddef> // This is for nullptr

using namespace std;

template<typename _T, unsigned int numberForGrouping = 0> class LinkedList
{
private: // Struct

    struct Node
    {
        _T __data;
        Node* __next;
        Node* __prev;


        Node(const _T &info)
        {
            __data = info;
            __next = nullptr;
            __prev = nullptr;
        }

        Node(const _T &info, Node* const previous)
        {
            __data = info;
            __next = nullptr;
            __prev = previous;
        }
    };

private: // Member variables

    Node* _head;
    Node* _tail;
    unsigned int _totalSize;
    unsigned int _groupNumber;

    // This contains a Node* to every 'numberForGrouping' Nodes for faster looking up / insertion / deletion
    // This is 0 by default, and will not be used if the user does not specifiy a value > 0.
    vector<Node*> _referenceVector;


public: // Constructors / Destructors
    LinkedList() { _ctor(); _totalSize = 0; }
    LinkedList(_T info) { _ctor(info); _totalSize = 1; }
    ~LinkedList() { _dtor(_head); }



public: // Functionality

    void push(_T info)
    {
        if(_head == nullptr) _ctor(info); // Nothing is in the list yet
        else
        {
            Node* temp = new Node(info, _tail); // Links it backwards
            _tail->__next = temp; // Links it forwards
            _tail = temp; // New 'last' Node
        }

        increaseSize();
    }

    _T pop()
    {
        if(_tail != nullptr)
        {
            _T temp = _tail->__data;
            if(_totalSize == 1) // There would be no items in the list after this pop
            {
                delete _tail;
                _tail = nullptr;
                _head = nullptr;
            }
            else
            {
                _tail = _tail->__prev;
                delete _tail->__next;
                _tail->__next = nullptr;
            }

            decreaseSize();
            return temp;
        }

        // ERROR HANDLING IF THEY TRY TO POP FROM A LIST CONTAINING 0 ELEMENTS
    }

    void insertHead(_T info)
    {
        Node* newNode = new Node(info);
        newNode->__next = _head;
        _head->__prev = newNode;
        _head = newNode;
        increaseSize();
    }

    void insertAfter(unsigned int index, _T info) // Inserts the Node* AFTER the Node at index
    {
        // ERROR HANDLING TO CHECK THE BOUNDS OF INDEX

        Node* temp = atIndex(index);

        if(index == (_totalSize - 1)) // basically just doing an append
            push(info);
        else
            insert(temp, info);
    }

    bool insertAfter(const _T &key, _T info) // true if successful, false if the key is not in the LL
    {
        Node* temp = atKey(key);
        if(temp != nullptr)
        {
            if(temp == _tail)
                push(info);
            else
                insert(temp, info);

            return true;
        }

        return false;
    }

    void insertBefore(unsigned int index, _T info) // Insers the Node* BEFORE the Node at index
    {
        // ERROR HANDLING TO CHECK BOUNDS OF INDEX

        if(index > 0) insertAfter(--index, info);

        else // == 0, wants to create a new head basically
            insertHead(info);
    }

    bool insertBefore(const _T &key, _T info)
    {
        Node* temp = atKey(key);
        if(temp != nullptr)
        {
            if(temp == _head)
                insertHead(info);
            else
                insert(temp->__prev, info);

            return true;
        }

        return false;
    }

    int size() { return _totalSize; }

    _T& operator[](unsigned int index)
    {
        if(index >= _totalSize) { throw invalid_argument("Attempted to access elements outside of largest bounds."); }

        return atIndex(index)->__data;
    }

    _T& head()
    {
        if(_head != nullptr)
            return _head->__data;

        // ERROR HANDLE IF THERE ARE NO ELEMENTS
    }

    _T& tail()
    {
        if(_tail != nullptr)
            return _tail->__data;

        // ERROR HANDLE IF THERE ARE NO ELEMENTS
    }





private: // Utility functions for above functions

    void _ctor()
    {
        _head = nullptr;
        _tail = nullptr;
        _groupNumber = numberForGrouping;
    }

    void _ctor(_T &info)
    {
        Node* temp = new Node(info);
        _head = temp;
        _tail = _head;
        _groupNumber = numberForGrouping;
    }

    void _dtor(Node* start)
    {

        Node* old;
        while(start)
        {
            old = start;
            start = start->__next;
            delete old;
        }
    }

    void insert(Node* position, const _T &info) // This does a Node insertion after the position Node
    {
        Node* newNode = new Node(info, position); // Link it backwards
        newNode->__next = position->__next;
        position->__next->__prev = newNode; // Link the Node after newNode back to newNode
        position->__next = newNode;
        increaseSize();
    }


    void increaseSize()
    {
        ++ _totalSize;
        if((_groupNumber) && _totalSize % _groupNumber == 0)
                    _referenceVector.push_back(_tail); // This will put a reference into the vector for helping to look up
    }

    void decreaseSize() { -- _totalSize; }


    Node* atKey(const _T &key)
    {
        Node* temp = _head;
        while(temp != nullptr && !(temp->__data == key)) // User should overload the == operator for this function
            temp = temp->__next;

        return temp; // returns nullptr if the key does not exist
    }

    Node* atIndex(unsigned int index)
    {
        // All errors related to no elements existing should be handled before calling this function
        Node* temp;
        if((_groupNumber) && index > _groupNumber)
        {
            temp = _referenceVector[(index / _groupNumber) - 1]; // 0 is the starting index
            for(size_t i = 0; i < (index % _groupNumber) + 1; ++i)
                temp = temp->__next;
        }
        else
        {
            temp = _head;
            for(size_t i = 0; i < index; ++i)
                temp = temp->__next;
        }

        return temp;
    }


};

#endif // LINKEDLIST_H
