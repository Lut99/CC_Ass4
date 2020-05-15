/* LINKED LIST.cpp
 *   by Anonymous
 *
 * Created:
 *   5/15/2020, 7:37:09 PM
 * Last edited:
 *   5/15/2020, 8:54:22 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The LinkedList class implements an easy scalable array. This partilar
 *   implementation is double linked (i.e., has a link to both previous and
 *   next nodes) and works for the int datatype alone. Note that it is also
 *   optimised for usage in the LargeNumber class.
**/

#include <iostream>
#include <stdexcept>

#include "LinkedList.hpp"

using namespace std;
using namespace Numbers;


LinkedList::LinkedList()
    : head(nullptr),
    tail(nullptr),
    n_nodes(0)
{
    #ifdef DEBUG
    cout << "LinkedList::LinkedList()" << endl;
    #endif
}

LinkedList::LinkedList(initializer_list<int> values)
    : head(nullptr),
    tail(nullptr),
    n_nodes(0)
{
    #ifdef DEBUG
    cout << "LinkedList::LinkedList(" << values << ")" << endl;
    #endif

    // Add all elements to the LinkedList
    for (auto value : values) {
        this->add(value);
    }
}

LinkedList::LinkedList(const LinkedList& other)
    : head(nullptr),
    tail(nullptr),
    n_nodes(0)
{
    #ifdef DEBUG
    cout << "LinkedList::LinkedList(const LinkedList& " << other << ")" << endl;
    #endif

    // Best way is to just iterate over all elements and add 'em by function
    for (LinkedListNode* n = other.head; n != nullptr; n = n->next) {
        this->add(n->value);
    }
}

LinkedList::LinkedList(LinkedList&& other)
    : head(other.head),
    tail(other.tail),
    n_nodes(other.n_nodes)
{
    #ifdef DEBUG
    cout << "LinkedList::LinkedList(LinkedList&& " << other << ")" << endl;
    #endif

    // Make sure to set the other elements' to nullptr since we stole 'em
    other.head = nullptr;
    other.tail = nullptr;
    other.n_nodes = 0;
}

LinkedList::~LinkedList() {
    #ifdef DEBUG
    cout << "LinkedList::~LinkedList()" << endl;
    #endif

    // Only remove if there is something to remove
    if (this->head != nullptr) {
        #ifdef DEBUG
        // Sanity check that tail is also not removed
        if (this->tail == nullptr) {
            cerr << "ERROR: LinkedList::~LinkedList(): Head is non-empty (" << this->head << "), but tail is." << endl;
            throw std::exception("An exception has occured.");
        }
        #endif

        // Remove all elements
        for (LinkedListNode* n = this->head; n != nullptr;) {
            // Make sure we don't lose track of the next one, then delete this node
            LinkedListNode* next_n = n->next;
            delete n;
            n = next_n;
            
            #ifdef DEBUG
            // Decrement the size counter so we can do a sanity check
            this->n_nodes--;
            #endif
        }

        #ifdef DEBUG
        // Make sure that the size is correct (sanity check)
        if (this->n_nodes != 0) {
            cerr << "ERROR: LinkedList::~LinkedList(): Invalid size count '" << this->n_nodes << "'." << endl;
            throw std::exception("An exception has occured.");
        }
        #endif
    }

    #ifdef DEBUG
    // Sanity check that tail is removed as well now
    if (this->tail == nullptr) {
        cerr << "ERROR: LinkedList::~LinkedList(): Head is empty, but tail isn't (" << this->tail << ")." << endl;
        throw std::exception("An exception has occured.");
    }
    #endif
}



void LinkedList::add(int value) {
    #ifdef DEBUG
    cout << "LinkedList::add(" << value << ")" << endl;
    #endif

    // Create the new node
    LinkedListNode* new_n = new LinkedListNode {value, nullptr, nullptr};

    // Do different things depending whether there is a tail
    if (this->tail == nullptr) {
        #ifdef DEBUG
        // Sanity check that head is empty as well
        if (this->head != nullptr) {
            cerr << "ERROR: LinkedList::add(" << value << "): Head is non-empty (" << this->head << "), but tail is." << endl;
            throw std::exception("An exception has occured.");
        }
        #endif

        // Set as head and be done
        this->head = new_n;
    } else {
        #ifdef DEBUG
        // Sanity check that head is non-empty as well
        if (this->head == nullptr) {
            cerr << "ERROR: LinkedList::add(" << value << "): Head is empty but tail isn't (" << this->tail << ")" << endl;
            throw std::exception("An exception has occured.");
        }
        #endif

        // Set as next from the tail
        this->tail->next = new_n;
    }

    // Update the tail and size counters
    this->tail = new_n;
    this->n_nodes++;
}



LinkedListNode* LinkedList::get_head() const {
    #ifdef DEBUG
    cout << "LinkedList::get_head()" << endl;
    #endif

    return this->head;
}

LinkedListNode* LinkedList::get(size_t index) const {
    #ifdef DEBUG
    cout << "LinkedList::get(" << index << ")" << endl;

    // Also check if index is within bounds
    if (index >= this->n_nodes) {
        cerr << "ERROR: LinkedList::get(" << index << "): Index is out of bounds for list with size " << this->n_nodes << "." << endl;
        throw out_of_range("An exception has occured.");
    }
    #endif

    // Loop until we found it or we end up with nullptr
    LinkedListNode* n = this->head;
    for (; n != nullptr && index > 0; n = n->next) {
        index--;
    }

    // Return it
    return n;
}

LinkedListNode* LinkedList::get_tail() const {
    #ifdef DEBUG
    cout << "LinkedList::get_tail()" << endl;
    #endif
    
    return this->tail;
}



int LinkedList::operator[](size_t index) const {
    #ifdef DEBUG
    cout << "LinkedList:: " << (*this) << "[" << index << "]" << endl;
    #endif

    // Check if index is within bounds
    if (index >= this->n_nodes) {
        cerr << "ERROR: LinkedList:: " << this << "[" << index << "]: Index is out of bounds for list with size " << this->n_nodes << "." << endl;
        throw out_of_range("An exception has occured.");
    }

    // Loop until we found it (won't end up with nullptr, as long as n_nodes is correctly defined)
    LinkedListNode* n = this->head;
    for (; index > 0; n = n->next) {
        index--;
    }

    // Return it
    return n->value;
}



LinkedList& LinkedList::operator=(LinkedList other) {
    #ifdef DEBUG
    cout << "LinkedList::operator=(LinkedList " << other << ")" << endl;
    #endif

    // May look the same as the move assignment operator, but note the header; the copy constructor copied the object for us, we can just swap it
    
    // Make sure it isn't us in case the compiler does some clever optimising
    if (this != &other) {
        // Use the swap operator to handle this scenario in accordance to the copy-and-swap idiom
        swap(*this, other);
    }

    // Return ourselves
    return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& other) {
    #ifdef DEBUG
    cout << "LinkedList::operator=(LinkedList&& " << other << ")" << endl;
    #endif

    // Make sure it isn't us
    if (this != &other) {
        // Use the swap operator to handle this scenario in accordance to the copy-and-swap idiom
        swap(*this, other);
    }

    // Return ourselves
    return *this;
}

void Numbers::swap(LinkedList& l1, LinkedList& l2) {
    using std::swap;

    #ifdef DEBUG
    cout << "LinkedList::swap(" << l1 << ", " << l2 << ")" << endl;
    #endif

    // Swap all elements
    swap(l1.head, l2.head);
    swap(l1.tail, l2.tail);
    swap(l1.n_nodes, l2.n_nodes);
}



std::ostream& Numbers::operator<<(std::ostream& os, const LinkedList& l) {
    // Start by writing brackets
    os << "{";

    // Loop through all elements to write those
    for (LinkedListNode* n = l.head; n != nullptr; n = n->next) {
        // All except the first iterations need a comma
        if (n != l.head) {
            os << ", ";
        }
        os << n->value;
    }

    // Close with another bracket
    os << "}";

    return os;
}



size_t LinkedList::size() const {
    #ifdef DEBUG
    cout << "LinkedList::size()" << endl;
    #endif

    return this->n_nodes;
}
