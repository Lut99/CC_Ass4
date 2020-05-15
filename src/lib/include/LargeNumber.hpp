/* LARGE NUMBER.hpp
 *   by Anonymous
 *
 * Created:
 *   5/15/2020, 7:30:20 PM
 * Last edited:
 *   5/15/2020, 7:35:28 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   File for the LargeNumber class, which is meant to be a VERY scalable
 *   Number container.
**/

#ifndef LARGENUMBER_HPP
#define LARGENUMBER_HPP

#include "Number.hpp"

namespace Numbers {
    class LargeNumber: public Number {
        private:
            

        protected:
            /* Write the internal number to a stream. */
            virtual void print(std::ostream &os) const;
            
        public:
            /* Default constructor for the Number class. */
            LargeNumber();
            /* Constructor for the LargeNumber class that parses it from string. */
            LargeNumber(std::string s);
            /* Deconstructor for the LargeNumber class. */
            virtual ~LargeNumber();
            /* Creates a new LargeNumber object from given string, as Number. */
            virtual Number* factoryMethod(std::string s) const;

            /* Compares this LargeNumber to another Number, and returns if they are equal. */
            virtual bool operator==(const Number& n) const;

            /* Increments the Number by one, inplace. */
            virtual Number& operator++();
            /* Adds another LargeNumber to this LargeNumber and returns the result as a new, allocated object. */
            virtual Number* operator+(const Number& n) const;
            /* Multiplies this LargeNumber with another LargeNumber and returns the result in a new, allocated object. */
            virtual Number* operator*(const Number& n) const;
    };
}

#endif
