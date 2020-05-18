/* LARGE NUMBER.cpp
 *   by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 7:31:26 PM
 * Last edited:
 *   5/18/2020, 9:23:37 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   File for the LargeNumber class, which is meant to be a VERY scalable
 *   Number container.
**/

#include <math.h>
#include <iostream>
#include <sstream>

#include "LargeNumber.hpp"

using namespace std;


LargeNumber::LargeNumber(int given_k)
    : k(given_k),
    max_value(pow(10, given_k) - 1)
{
    #ifdef DEBUG
    cout << "LargeNumber::LargeNumber(" << given_k << ")" << endl;
    #endif

    // Make sure k is legal
    if (k < 1) {
        cerr << "WARNING: LargeNumber::LargeNumber(" << given_k << "): k clipped to 1." << endl;
        this->k = 1;
        this->max_value = 9;
    } else if (k > 4) {
        cerr << "WARNING: LargeNumber::LargeNumber(" << given_k << "): k clipped to 4." << endl;
        this->k = 4;
        this->max_value = 9999;
    }
}

LargeNumber::LargeNumber(string s, int given_k)
    : k(given_k),
    max_value(pow(10, given_k) - 1)
{
    #ifdef DEBUG
    cout << "LargeNumber::LargeNumber(\"" << s << "\", " << given_k << ")" << endl;
    #endif

    // Make sure k is legal
    if (k < 1) {
        cerr << "WARNING: LargeNumber::LargeNumber(" << given_k << "): k clipped to 1." << endl;
        this->k = 1;
        this->max_value = 9;
    } else if (k > 4) {
        cerr << "WARNING: LargeNumber::LargeNumber(" << given_k << "): k clipped to 4." << endl;
        this->k = 4;
        this->max_value = 9999;
    }
    
    // The number is always at least 0
    this->data.add(0);

    // Try to parse the string by reading each four of the digits
    // Because size_t is unsigned, we check it doesn't overflow
    int node_offset = 1;
    for (size_t i = s.size() - 1; i <= s.size() - 1; i--) {
        char c = s[i];

        #ifdef DEBUG
        // Throw an exception if not a digit
        if (c < '0' || c > '9') {
            cerr << "ERROR: LargeNumber::LargeNumber(\"" << s << "\", " << given_k << "): Encountered illegal character '" << c << "'." << endl;
            throw invalid_argument("An exception has occured.");
        }
        #endif
        
        // Add it to the internal list, either as new node or appending to it
        if (node_offset >= 10000) {
            this->data.add_head(0);
            // Reset the node_offset again
            node_offset = 1;
        }

        // Compute the value in this node
        int value = ((int) (c - '0')) * node_offset;
        node_offset *= 10;
        
        // Add the data
        this->data.get_head()->value += value;
    }

    #ifdef TEST
    // Print the result of the internal list to the stdout so that the test_largenumber file can check it
    cout << this->data;
    #endif
}

LargeNumber::~LargeNumber() {
    #ifdef DEBUG
    cout << "LargeNumber::~LargeNumber()" << endl;
    #endif
}

Number* LargeNumber::factoryMethod(string s) const {
    #ifdef DEBUG
    cout << "LargeNumber::factoryMethod(\"" << s << "\")" << endl;
    #endif

    // Return a pointer to a new LargeNumber object, casted to a Number pointer
    return (Number*) new LargeNumber(s);
}



void LargeNumber::print(std::ostream &os) const {
    // Print all digits successively
    for (LinkedListNode* n = this->data.get_head(); n != nullptr; n = n->next) {
        // Make sure to put some 0's in first if this isn't the first of 'em
        if (n != this->data.get_head()) {
            if (n->value == 0) {
                // Make 0 a special case as log10(0) is a tricky one
                os << "0000";
                continue;
            } else {
                // For all other numbers, compute the missing digits to get to k and print that many zeroes
                int missing = this->k - (int) (log10(n->value) + 1);
                for (int i = 0; i < missing; i++) {
                    os << '0';
                }
            }
        }
        
        os << n->value;
    }
}



bool LargeNumber::operator==(const Number& n) const {
    #ifdef DEBUG
    cout << "LargeNumber:: " << (*this) << " == " << n << endl;
    #endif

    // We assume the other is a LargeNumber as well
    LargeNumber& other = (LargeNumber&) n;

    // First, make sure the sizes are OK
    if (this->data.size() != other.data.size()) {
        return false;
    }

    // Compare each node
    LinkedListNode* n1 = this->data.get_head();
    LinkedListNode* n2 = other.data.get_head();
    while (n1 != nullptr && n2 != nullptr) {
        if (n1->value != n2->value) {
            return false;
        }

        n1 = n1->next;
        n2 = n2->next;
    }

    // Passed all checks, they are the same!
    return true;
}



Number& LargeNumber::operator++() {
    #ifdef DEBUG
    cout << "LargeNumber:: ++" << (*this) << endl;
    #endif

    // Go from back to front, adding 1 and carrying carry if needed
    int carry = 1;
    for (LinkedListNode* n = this->data.get_tail(); n != nullptr; n = n->prev) {
        n->value += carry;
        
        // Reset carry, then compute the next one
        carry = 0;
        if (n->value > this->max_value) {
            // Carry to the previous node
            carry++;
            n->value -= this->max_value + 1;
        }
    }

    // If there is still carry left, insert a new node and give it the carry value
    if (carry > 0) {
        this->data.add_head(carry);
    }

    return (*this);
}

Number& LargeNumber::operator+=(const int s) {
    #ifdef DEBUG
    cout << "LargeNumber:: " << (*this) << " += " << s << endl;
    #endif

    // Go from back to front, adding 1 and carrying carry if needed
    int carry = s;
    for (LinkedListNode* n = this->data.get_tail(); n != nullptr; n = n->prev) {
        // Note while this can theoretically overflow, we will only use this function internally, so it shouldn't overflow for this purpose
        n->value += carry;
        
        // Reset carry, then compute the next one
        carry = 0;
        if (n->value > this->max_value) {
            // Carry to the previous node
            carry++;
            n->value -= this->max_value + 1;
        }
    }

    // If there is still carry left, insert a new node and give it the carry value
    if (carry > 0) {
        this->data.add_head(carry);
    }

    return (*this);
}

Number& LargeNumber::operator+=(const Number& n) {
    #ifdef DEBUG
    cout << "LargeNumber:: " << (*this) << " += " << n << endl;
    #endif
    
    // Cast Number to LargeNumber
    const LargeNumber& other = (LargeNumber&) n;

    // Now add all nodes of the given number to this one, preserving carries is it grows too large
    LinkedListNode* n1 = this->data.get_tail();
    LinkedListNode* n2 = other.data.get_tail();
    int carry = 0;
    int ceil_value = this->max_value + 1;
    while (n1 != nullptr && n2 != nullptr) {
        // Add these together, plus any carry
        int new_value = n1->value + n2->value + carry;

        // Reset the carry and get any new ones
        carry = new_value / ceil_value;
        new_value = new_value % ceil_value;

        // Add it to the list 
        n1->value = new_value;
        
        n1 = n1->prev;
        n2 = n2->prev;
    }

    // Add any remaining n1 nodes, adding a carry if needed
    for (; n2 != nullptr; n2 = n2->prev) {
        // Add these together, plus any carry
        int new_value = n2->value + carry;

        // Reset the carry and get any new ones
        carry = new_value / ceil_value;
        new_value = new_value % ceil_value;

        // Add it to the list 
        this->data.add_head(new_value);
    }

    // If there is a carry left, make sure to add it
    while (carry > 0) {
        if (n1 == nullptr) {
            this->data.add_head(carry);
            carry = 0;
        } else {
            int new_value = n1->value + carry;

            // Reset the carry and get any new ones
            carry = new_value / ceil_value;
            new_value = new_value % ceil_value;

            n1->value = new_value;
        }
    }

    // Done
    return (*this);
}

Number* LargeNumber::operator+(const Number& n) const {
    #ifdef DEBUG
    cout << "LargeNumber:: " << (*this) << " + " << n << endl;
    #endif
    
    // Cast Number to LargeNumber
    const LargeNumber& other = (LargeNumber&) n;

    // Create the new data
    LargeNumber* result = new LargeNumber(this->k);

    // Make sure the list of n1 has the largest size
    LinkedListNode* n1 = this->data.get_tail();
    LinkedListNode* n2 = other.data.get_tail();
    if (this->data.size() < other.data.size()) {
        n1 = other.data.get_tail();
        n2 = this->data.get_tail();
    }

    // Now add all nodes of the smaller list to the larger one, preserving carries is it grows too large
    int carry = 0;
    int ceil_value = this->max_value + 1;
    while (n2 != nullptr) {
        // Add these together, plus any carry
        int new_value = n1->value + n2->value + carry;

        // Reset the carry and get any new ones
        carry = new_value / ceil_value;
        new_value = new_value % ceil_value;

        // Add it to the list 
        result->data.add_head(new_value);
        
        n1 = n1->prev;
        n2 = n2->prev;
    }

    // Add any remaining n1 nodes, adding a carry if needed
    for (; n1 != nullptr; n1 = n1->prev) {
        // Add these together, plus any carry
        int new_value = n1->value + carry;

        // Reset the carry and get any new ones
        carry = new_value / ceil_value;
        new_value = new_value % ceil_value;

        // Add it to the list 
        result->data.add_head(new_value);
    }

    // If there is a carry left, make sure to add it
    if (carry > 0) {
        result->data.add_head(carry);
    }

    // Done
    return result;
}

Number* LargeNumber::operator*(const Number& n) const {
    #ifdef DEBUG
    cout << "LargeNumber:: " << (*this) << " + " << n << endl;
    #endif

    // Cast Number to LargeNumber
    const LargeNumber& other = (LargeNumber&) n;

    // Create the new data
    LargeNumber* result = new LargeNumber(this->k);

    // Loop through other to add those one-by-one
    size_t offset = 0;
    int ceil_value = this->max_value + 1;
    for (LinkedListNode* n2 = other.data.get_tail(); n2 != nullptr; n2 = n2->prev) {
        LargeNumber temp_result(this->k);

        // We first loop over all nodes in this to add each of them to the current node in other
        int carry = 0;
        for (LinkedListNode* n1 = this->data.get_tail(); n1 != nullptr; n1 = n1->prev) {
            // Compute the new value
            int new_value = n1->value * n2->value + carry;

            // Compute the carry
            carry = new_value / ceil_value;
            new_value = new_value % ceil_value;

            // Set the the result
            temp_result.data.add_head(new_value);
        }

        // Add the leftover carry to r
        if (carry > 0) {
            temp_result.data.add_head(carry);
        }

        // Shift the LargeNumber by offset (simply add empty nodes at the right)
        for (size_t i = 0; i < offset; i++) {
            temp_result.data.add(0);
        }

        // Add the tempresult
        (*result) += temp_result;

        // Don't forget to increment
        offset++;
    }

    return result;
}



string LargeNumber::to_string() const {
    stringstream sstr;
    this->print(sstr);
    return sstr.str();
}
