/* MATH.cpp
 *   by Bas Terwijn, re-organised by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 6:42:18 PM
 * Last edited:
 *   5/18/2020, 9:24:34 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Math class allows us to do some math operations on the Numbers
 *   class.
**/

#include <iostream>

#include "Math.hpp"

using namespace std;


Number* Math::fibonacci(const Number& n) {
    // It's a open-and-close case for 0 and 1
    Number* fib0=n.factoryMethod("0");
    if (n==*fib0) 
        return fib0;
    Number* fib1=n.factoryMethod("1");
    if (n==*fib1)
    {
        delete fib0;
        return fib1;
    }

    // Otherwise, do the rest of the computation
    Number* result=NULL;
    Number* i=n.factoryMethod("1");
    for (;(*i)!=n;++(*i)) {
        // Add the previous two numbers
        result=(*fib0)+(*fib1);

        // Show us which if told to do so
        #ifdef DEBUG
        cout << "fib("<< (*i) << "):" << (*result) << endl;
        #endif

        // Move the numbers one in their order
        delete fib0;
        fib0=fib1;
        fib1=result;
    }

    // Cleanup and return
    delete i;
    delete fib0;
    return result;
}

Number* Math::factorial(const Number& n) {
    // Create a placeholder for the result
    Number* result = n.factoryMethod("1");

    // If it's the first number, we know already
    Number* i = n.factoryMethod("0");
    if ((*i) == n)
    {
        // Cleanup and return
        delete i;
        return result;
    }

    // Increment so that i is now 1, which is the above starting case
    ++(*i);

    // The rest of the numbers are done by multiplying all other numbers with one another
    while ((*i)!=n) {
        // Move to the next number
        ++(*i);

        // Do the multiplication with the new number
        Number* temp = result;
        result = (*result) * (*i);

        // Print the intermediate result if compiled to do so
        #ifdef DEBUG
        cout << "fac(" << (*i) << "):" << (*result) << endl;
        #endif

        // Clean the old value
        delete temp;
    }

    // Cleanup and return
    delete i;
    return result;
}
