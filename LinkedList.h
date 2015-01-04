// Created by Joseph Avery Ferrante on 12/18/14
// INSERTING CANNOT BREAK THE REFERENCE SYSTEM!!!

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstddef> // This is for NULL

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
            __next = NULL;
            __prev = NULL;
        }

        Node(const _T &info, Node* const previous)
        {
            __data = info;
            __next = NULL;
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
        if(_head == NULL) _ctor(info); // Nothing is in the list yet
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
        if(_tail != NULL)
        {
            _T temp = _tail->__data;
            bool deleted = decreaseSize();
            if(_totalSize == 1) // There would be no items in the list after this pop
            {
                if(!deleted)
                    delete _tail;
                _tail = NULL;
                _head = NULL;
            }
            else
            {
                _tail = _tail->__prev;
                if(!deleted)
                    delete _tail->__next;
                _tail->__next = NULL;
            }

            return temp;
        }

        else
            throw out_of_range("Failed to 'pop' element: the current list is empty.");
    }

    void insertHead(_T info)
    {
        Node* newNode = new Node(info);
        if(_totalSize == 0)
        {
            _head = newNode;
            _tail = newNode;
        }
        else
        {
            newNode->__next = _head;
            _head->__prev = newNode;
            _head = newNode;
        }

        bool newElement = increaseSize();
        if(_groupNumber)
            _shiftForward(0, newElement, true);
    }

    void insertAfter(unsigned int index, _T info) // Inserts the Node* AFTER the Node at index
    {
        if(index > (_totalSize - 1))
            throw out_of_range("Attempted to access an element outside of the range of the current list");

        if(index == (_totalSize - 1)) // basically just doing an append
            push(info);

        else
        {
            Node* temp = atIndex(index);
            bool newElement = insert(temp, info);
            if(_groupNumber)
                _shiftForward(index, newElement, true);
        }
    }

    bool insertAfter(const _T &key, _T info) // true if successful, false if the key is not in the LL
    {
        Node* temp = atKey(key);
        if(temp != NULL)
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
        if(index > (_totalSize - 1))
            throw out_of_range("Attempted to access an element outside of the range of the current list");

        if(index > 0) insertAfter(--index, info);

        else // == 0, wants to create a new head basically
            insertHead(info);
    }

    bool insertBefore(const _T &key, _T info)
    {
        Node* temp = atKey(key);
        if(temp != NULL)
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
        if(index >= _totalSize) throw invalid_argument("Attempted to access elements outside of largest bounds.");
        return atIndex(index)->__data;
    }

    bool exists(const _T &source)
    {
        if(atKey(source) != NULL)
            return true;

        return false;
    }

    _T& head()
    {
        if(_head != NULL)
            return _head->__data;

        else
            throw out_of_range("Failed to return 'head' data: the current list is empty");
    }

    _T& tail()
    {
        if(_tail != NULL)
            return _tail->__data;

        else
            throw out_of_range("Failed to return 'tail' data: the current list is empty");
    }


private: // Utility functions for above functions

    void _ctor()
    {
        _head = NULL;
        _tail = NULL;

        if(numberForGrouping < 2)
            throw invalid_argument("The reference number must be greater than 1");

        _groupNumber = numberForGrouping;
    }

    void _ctor(_T &info)
    {
        Node* temp = new Node(info);
        _head = temp;
        _tail = _head;

        if(numberForGrouping < 2)
            throw invalid_argument("The reference number must be greater than 1");

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

    bool insert(Node* position, const _T &info) // This does a Node insertion after the position Node
    {
        Node* newNode = new Node(info, position); // Link it backwards
        newNode->__next = position->__next;
        position->__next->__prev = newNode; // Link the Node after newNode back to newNode
        position->__next = newNode;
        return increaseSize();
    }

    bool increaseSize() // Returns true if a new element was added to the reference vector so I know not to shift this one when adjusting during an insert
    {
        ++ _totalSize;
        if((_groupNumber) && _totalSize % _groupNumber == 0)
        {
            _referenceVector.push_back(_tail); // This will put a reference into the vector for helping to look up
            return true;
        }
        return false;
    }

    bool decreaseSize()
    {
        if((_groupNumber) && _totalSize % _groupNumber == 0) // We are popping a reference index, so pop it from the vector
        {
            _referenceVector.pop_back(); // This destroys the removed element
            --_totalSize;
            cout << "Deleted in decreaseSize" << endl;
            return true; // So we know the element has been deleted and I don't attempt to re-delete it
        }

        -- _totalSize;
        return false;
    }


    Node* atKey(const _T &key)
    {
        Node* temp = _head;
        while(temp != NULL && !(temp->__data == key)) // User should overload the == operator for this function
            temp = temp->__next;

        return temp; // returns NULL if the key does not exist
    }

    Node* atIndex(unsigned int index)
    {
        // All errors related to no elements existing should be handled before calling this function
        Node* temp;
        if((_groupNumber) && index >= _groupNumber)
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

    void _shiftForward(int startIndex, bool newElement, bool insertAfter) // This shifts the references in the vector to their 'prev' node ( used when an insert occurs )
    {
        if(insertAfter) // We inserted after the index, so we will not shift anything before or at it
            ++startIndex;
        else // We inserted before the index, so it needs to be included in evaluation of shifting
            --startIndex;

        int start = 0; // By default, if startIndex is < _groupNumber, I need to shift the entire vector.
        if(startIndex >= _groupNumber)
            start = startIndex / _groupNumber; // This shifts everything that is AFTER the insert

        if(newElement) // Don't shift the last element (the new one just added)
        {
            for(int i = start; i < _referenceVector.size() - 1; ++i)
            {
                assert ( ( _referenceVector[i])->__prev != NULL );
                _referenceVector[i] = (_referenceVector[i])->__prev;
            }
        }

        else
        {
            for(int i = start; i < _referenceVector.size(); ++i)
            {
                assert ( ( _referenceVector[i])->__prev != NULL );
                _referenceVector[i] = (_referenceVector[i])->__prev;
            }
        }
    }
};

#endif // LINKEDLIST_H
