/* MATH.hpp
 *   by Anonymous
 *
 * Created:
 *   5/15/2020, 6:31:01 PM
 * Last edited:
 *   5/15/2020, 6:45:58 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Header file for the math library
**/

#ifndef MATH_HPP
#define MATH_HPP

#include "Number.hpp"

namespace Numbers {
    // Math library that computes fibonacci and factorial numbers, uses the Number interface
    class Math
    {
        public:
            /* Computes the n'th fibonacci number. */
            static Number* fibonacci(const Number& n);

            /* Computes the n'th factorial number. */ 
            static Number* factorial(const Number& n);

    };
}

#endif
