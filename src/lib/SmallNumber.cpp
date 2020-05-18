/* SMALL NUMBER.cpp
 *   by Bas Terwijn, re-organised by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 6:50:54 PM
 * Last edited:
 *   5/18/2020, 9:24:30 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Implements a Small Number container, which extends from the abstract
 *   Number class.
**/

#include <iostream>
#include <sstream>

#include "SmallNumber.hpp"

using namespace std;


SmallNumber::SmallNumber() {
    #ifdef DEBUG
    cout << "SmallNumber::SmallNumber()" << endl;
    #endif

    this->number = 0;
}

SmallNumber::SmallNumber(string s) {
    #ifdef DEBUG
    cout << "SmallNumber::SmallNumber(" << s << ")" << endl;
    #endif

    // Fetch the string from the stream
    stringstream ss(s);
    ss >> number;

    // Make sure it is always positive
    if (number<0) {
        number = -number;
    }
}

SmallNumber::~SmallNumber() {
    #ifdef DEBUG
    cout << "SmallNumber::~SmallNumber()" << endl;
    #endif
}

Number* SmallNumber::factoryMethod(string s) const {
    #ifdef DEBUG
    cout << "SmallNumber::factoryMethod(" << s << ")" << endl;
    #endif

    // Use the normal constructor for this job
    return (Number*) new SmallNumber(s);
}



void SmallNumber::print(std::ostream &os) const {
    os << this->number;
}



bool SmallNumber::operator==(const Number& n) const {
    #ifdef DEBUG
    cout << "SmallNumber:: " << (*this) << " == " << n << endl;
    #endif

    // Get the Number as SmallNumber. Upon failure, just let the exception handling do the rest
    const SmallNumber& sn = static_cast<const SmallNumber&>(n);

    // Return the result of the inner number
    return this->number == sn.number;
}



Number& SmallNumber::operator++() {
    #ifdef DEBUG
    cout << "SmallNumber:: ++" << (*this) << endl;
    #endif

    // Increment and return
    ++this->number;
    return *this;
}

Number* SmallNumber::operator+(const Number& n) const {
    #ifdef DEBUG
    cout << "SmallNumber:: " << (*this) << " + " << n << endl;
    #endif
    
    // Create the new object
    SmallNumber* result = new SmallNumber();

    // Cast the number to SmallNumber
    const SmallNumber& sn=static_cast<const SmallNumber&>(n);
    
    // Add 'em and done
    result->number = this->number + sn.number;
    return result;
}

Number* SmallNumber::operator*(const Number& n) const {
    #ifdef DEBUG
    cout << "SmallNumber:: " << (*this) << " * " << n << endl;
    #endif

    // Create the new object
    SmallNumber* result=new SmallNumber();

    // Cast the input to a SmallNumber
    const SmallNumber& sn=static_cast<const SmallNumber&>(n);

    // Multiply and return
    result->number = this->number * sn.number;
    return result;
}
