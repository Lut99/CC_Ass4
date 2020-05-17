/* LINKED LIST.hpp
 *   by Anonymous
 *
 * Created:
 *   5/15/2020, 7:35:57 PM
 * Last edited:
 *   5/17/2020, 6:23:30 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Header file for the LinkedList class.
**/

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <cstddef>
#include <initializer_list>
#include <ostream>

namespace Numbers {
    /* Represents a node in the LinkedList. */
    struct LinkedListNode {
        /* Stores the value in this node. */
        int value;
        /* Stores a link to the next node. */
        LinkedListNode* next;
        /* Stores a link to the previous node. */
        LinkedListNode* prev;
    };

    /* The LinkedList class itself. */
    class LinkedList {
        private:
            /* Stores the head of the list. */
            LinkedListNode* head;
            /* Stores the tail of the list. */
            LinkedListNode* tail;

            /* Stores the size (in nodes) of the list. */
            std::size_t n_nodes;

        public:
            /* Default constructor for the LinkedList class: creates an empty list. */
            LinkedList();
            /* This constructor takes a {...} list of values. */
            LinkedList(std::initializer_list<int> values);
            /* Copy constructor for the LinkedList class. */
            LinkedList(const LinkedList& other);
            /* Move constructor for the LinkedList class. */
            LinkedList(LinkedList&& other);
            /* Deconstructor for the LinkedList class. If DEBUG is given, also performs some sanity checks. */
            ~LinkedList();

            /* Adds a new element to the end of list. Returns the new node to immediately work with it. */
            LinkedListNode* add(int value);
            /* Adds a new element to the beginning of the list. Returns the new node to immediately work with it. */
            LinkedListNode* add_head(int value);

            /* Returns a reference to the head of the list. Returns a nullptr if the list has no such element.  */
            LinkedListNode* get_head() const;
            /* Returns a reference to the node with the given index in the list. Returns a nullptr if the list has no such element. If DEBUG is defined, throws an out_of_range exception if the index is too large. */
            LinkedListNode* get(std::size_t index) const;
            /* Returns a reference to the tail of the list. Returns a nullptr if the list has no such element.  */
            LinkedListNode* get_tail() const;
            
            /* Get the value at the given index of the list. Throws an out_of_range exception if index is too large. */
            int operator[](std::size_t index) const;

            /* Assignment copy operator for the LinkedList class. */
            LinkedList& operator=(LinkedList other);
            /* Assignment move operator for the LinkedList class. */
            LinkedList& operator=(LinkedList&& other);
            /* Swap operator for the LinkedList class. */
            friend void swap(LinkedList& l1, LinkedList& l2);

            /* Writes the list in string format to given stream. */
            friend std::ostream& operator<<(std::ostream& os, const LinkedList& l);

            /* Return the size of the list. */
            std::size_t size() const;
    };

    /* Defines the swap operator for the LinkedList class. */
    void swap(LinkedList& l1, LinkedList& l2);
    /* Defines the stream operator for the LinkedList class. */
    std::ostream& operator<<(std::ostream&, const LinkedList& l);
}

#endif

