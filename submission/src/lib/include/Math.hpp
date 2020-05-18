/* MATH.hpp
 *   by Bas Terwijn, re-organised by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 6:31:01 PM
 * Last edited:
 *   5/18/2020, 9:24:36 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Header file for the math library
**/

#ifndef MATH_HPP
#define MATH_HPP

#include "Number.hpp"

// Math library that computes fibonacci and factorial numbers, uses the Number interface
class Math
{
    public:
        /* Computes the n'th fibonacci number. */
        static Number* fibonacci(const Number& n);

        /* Computes the n'th factorial number. */ 
        static Number* factorial(const Number& n);

};

#endif
