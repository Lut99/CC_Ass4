/* LARGE NUMBER.hpp
 *   by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 7:30:20 PM
 * Last edited:
 *   5/18/2020, 9:23:39 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   File for the LargeNumber class, which is meant to be a VERY scalable
 *   Number container.
**/

#ifndef LARGENUMBER_HPP
#define LARGENUMBER_HPP

#include <string>
#include <ostream>

#include "LinkedList.hpp"
#include "Number.hpp"

class LargeNumber: public Number {
    private:
        /* Stores the parts of the number. */
        LinkedList data;

        /* The maximum number of digits per node in the LinkedList. */
        int k;
        /* The maximum value nodes can have without going beyong k digits. */
        int max_value;

    protected:
        /* Write the internal number to a stream. */
        virtual void print(std::ostream &os) const;
        
    public:
        /* Default constructor for the Number class. */
        LargeNumber(int k = 4);
        /* Constructor for the LargeNumber class that parses it from string. If DEBUG is given and the string contains illegal characters, throws an invalid_argument exception. */
        LargeNumber(std::string s, int k = 4);
        /* Deconstructor for the LargeNumber class. */
        virtual ~LargeNumber();
        /* Creates a new LargeNumber object from given string, as Number. */
        virtual Number* factoryMethod(std::string s) const;

        /* Compares this LargeNumber to another Number, and returns if they are equal. */
        virtual bool operator==(const Number& n) const;

        /* Increments the Number by one, inplace. */
        virtual Number& operator++();
        /* Adds a scalar to this LargeNumber object. */
        virtual Number& operator+=(const int s);
        /* Adds another LargeNumber to this LargeNumber object, inplace */
        virtual Number& operator+=(const Number& n);
        /* Adds another LargeNumber to this LargeNumber and returns the result as a new, allocated object. */
        virtual Number* operator+(const Number& n) const;
        /* Multiplies this LargeNumber with another LargeNumber and returns the result in a new, allocated object. */
        virtual Number* operator*(const Number& n) const;

        /* Prints the LargeNumber to a string. */
        std::string to_string() const;
};

#endif
