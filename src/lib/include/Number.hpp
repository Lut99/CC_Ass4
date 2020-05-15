/* NUMBER.hpp
 *   by Anonymous
 *
 * Created:
 *   5/15/2020, 6:32:16 PM
 * Last edited:
 *   5/15/2020, 7:27:21 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Header for the abstract Number class.
**/

#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <string>
#include <ostream>

namespace Numbers {
    // Interface of Number type (abstract class)
    // its methods are virtual so they can be overridden in derived classes
    class Number
    {
        protected:
            /* Prints the number to given stream. */
            virtual void print(std::ostream &os) const=0;

        public:
            /* Default constructor for the Number class. */
            Number() {}
            /* Parses the number from a string. */
            Number(std::string) {}
            /* Deconstructor for the Number class. */
            virtual ~Number() {}
            /* Creates a new Number object from given string. */
            virtual Number* factoryMethod(std::string s) const=0;

            /* Check if this number is the same as the other number. */
            virtual bool operator==(const Number& n) const=0;
            /* Check if this number is NOT the same as the other number. */
            virtual bool operator!=(const Number& n) const;

            /* Increments the number. */
            virtual Number& operator++()=0;
            /* Adds another number to this number and returns a new Number object (allocated). */
            virtual Number* operator+(const Number& n) const=0;
            /* Multiplies this number with another number and returns the result in a new Number object (allocated). */
            virtual Number* operator*(const Number& n) const=0;

            /* Friends the stream operator to convert to string. */
            friend std::ostream& operator<<(std::ostream &os, const Number& n);
    };

    /* Allows the Number to be printed to given stream. */
    std::ostream& operator<<(std::ostream& os, const Number& n);
}

#endif
