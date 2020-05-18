/* SMALL NUMBER.hpp
 *   by Bas Terwijn, re-organised by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 6:30:08 PM
 * Last edited:
 *   5/18/2020, 9:24:28 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Header file for SmallNumber class.
**/

#ifndef SMALLNUMBER_HPP
#define SMALLNUMBER_HPP

#include <string>

#include "Number.hpp"

// Simple implementation of Number interface
class SmallNumber : public Number
{
    private:
        /* The internal value of the Number. */
        int number;

    protected:
        /* Write the internal number to a stream. */
        virtual void print(std::ostream &os) const;
        
    public:
        /* Default constructor for the Number class. */
        SmallNumber();
        /* Constructor for the SmallNumber class that parses it from string. */
        SmallNumber(std::string s);
        /* Deconstructor for the SmallNumber class. */
        virtual ~SmallNumber();
        /* Creates a new SmallNumber object from given string, as Number. */
        virtual Number* factoryMethod(std::string s) const;

        /* Compares this SmallNumber to another Number, and returns if they are equal. */
        virtual bool operator==(const Number& n) const;

        /* Increments the Number by one, inplace. */
        virtual Number& operator++();
        /* Adds another SmallNumber to this SmallNumber and returns the result as a new, allocated object. */
        virtual Number* operator+(const Number& n) const;
        /* Multiplies this SmallNumber with another SmallNumber and returns the result in a new, allocated object. */
        virtual Number* operator*(const Number& n) const;
};

#endif
