/* TEST LINKEDLIST.cpp
 *   by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 8:34:29 PM
 * Last edited:
 *   5/18/2020, 9:23:24 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file provides some tests for the LinkedList class.
**/

#include <iostream>

#include "LinkedList.hpp"

using namespace std;


bool test_store_incremental() {
    // Define the reference list
    int expected[] = {0, 1, 2, 3, 4};

    // Create the LinkedList
    LinkedList l;

    // Add all of these elements
    for (int i = 0; i < 5; i++) {
        l.add(expected[i]);
    }

    // Check if these elements make sense (slow way)
    for (size_t i = 0; i < 5; i++) {
        if (l[i] != expected[i]) {
            cout << " [FAIL]" << endl << endl;
            cerr << "ERROR: Unexpected value at index " << i << ": got " << l[i] << ", expected " << expected[i] << "." << endl << endl;
            return false;
        }
    }

    // Succes
    cout << " [ OK ]" << endl;
    return true;
}

bool test_store_at_once() {
    // Define the reference list
    int expected[] = {0, 1, 2, 3, 4};

    // Create the LinkedList
    LinkedList l({0, 1, 2, 3, 4});

    // Check if these elements make sense (slow way)
    for (size_t i = 0; i < 5; i++) {
        if (l[i] != expected[i]) {
            cout << " [FAIL]" << endl << endl;
            cerr << "ERROR: Unexpected value at index " << i << ": got " << l[i] << ", expected " << expected[i] << "." << endl << endl;
            return false;
        }
    }

    // Succes
    cout << " [ OK ]" << endl;
    return true;
}

bool test_copy() {
    // Define the reference list
    int expected[] = {0, 1, 2, 3, 4};

    // Create the LinkedList
    LinkedList l({0, 1, 2, 3, 4});

    // Copy it to another two LinkedList (both methods of copying)
    LinkedList l1(l);
    LinkedList l2;
    l2 = l;

    // Check if these elements make sense (slow way)
    for (size_t i = 0; i < 5; i++) {
        if (l1[i] != expected[i]) {
            cout << " [FAIL]" << endl << endl;
            cerr << "ERROR: Unexpected value at index " << i << " for l1: got " << l1[i] << ", expected " << expected[i] << "." << endl << endl;
            return false;
        }
        if (l2[i] != expected[i]) {
            cout << " [FAIL]" << endl << endl;
            cerr << "ERROR: Unexpected value at index " << i << " for l2: got " << l2[i] << ", expected " << expected[i] << "." << endl << endl;
            return false;
        }
    }

    // Succes
    cout << " [ OK ]" << endl;
    return true;
}

bool test_links() {
    // First, define the order of elements we should see
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Next, create a LinkedList with those elements
    LinkedList l({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    // First: check if the size is correct
    if (l.size() != 10) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: List should have length 10, but reports it is " << l.size() << " long." << endl << endl;
        return false;
    }

    // Loop forward manually to check if the links are correct
    int count = 0;
    for (LinkedListNode* n = l.get_head(); n != nullptr; n = n->next) {
        // Check if the element is what we expect
        if (n->value != expected[count]) {
            cout << " [FAIL]" << endl << endl;
            cerr << "ERROR: Forward pass: Node " << count << " has value " << n->value << " while it should be " << expected[count] << "; previous link probably broken." << endl << endl;
            return false;
        }
        
        count++;
    }
    // If the count is not correct, also error
    if (count != 10) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: Forward pass: List " << l << " has no more links after " << count << " elements (should be 10 long)." << endl << endl;
        return false;
    }

    // Do the same, backward
    count = 9;
    for (LinkedListNode* n = l.get_tail(); n != nullptr; n = n->prev) {
        // Check if the element is what we expect
        if (n->value != expected[count]) {
            cout << " [FAIL]" << endl << endl;
            cerr << "ERROR: Backward pass: Node " << count << " has value " << n->value << " while it should be " << expected[count] << "; previous link probably broken." << endl << endl;
            return false;
        }
        
        count--;
    }
    // If the count is not correct, also error
    if (count != -1) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: Backward pass: List " << l << " has no more links after " << count << " elements (should be 10 long)." << endl << endl;
        return false;
    }

    // Otherwise... all is fine!
    cout << " [ OK ]" << endl;
    return true;
}


int main() {
    cout << "  Testing incremental growth...";
    if (!test_store_incremental()) {
        cout << "LinkedList tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing instant growth...    ";
    if (!test_store_at_once()) {
        cout << "LinkedList tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing memory management... ";
    if (!test_copy()) {
        cout << "LinkedList tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing link validity...     ";
    if (!test_links()) {
        cout << "LinkedList tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "LinkedList tests success!" << endl << endl;
    return EXIT_SUCCESS;
}
