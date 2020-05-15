/* TEST LINKEDLIST.cpp
 *   by Anonymous
 *
 * Created:
 *   5/15/2020, 8:34:29 PM
 * Last edited:
 *   5/15/2020, 8:54:59 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file provides some tests for the LinkedList class.
**/

#include <iostream>

#include "LinkedList.hpp"

using namespace std;
using namespace Numbers;


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

    cout << "LinkedList tests success!" << endl << endl;
    return EXIT_SUCCESS;
}
