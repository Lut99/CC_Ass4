/* MAIN.cpp
 *   by Tim Müller (11774606)
 *
 * Created:
 *   5/15/2020, 6:28:51 PM
 * Last edited:
 *   5/15/2020, 7:31:13 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file is the entry point for either SmallNumber or LargeNumber.
**/

#include <iostream>

// Choose which number library to use. */
#ifdef SMALLNUMBER
#include "SmallNumber.hpp"
#else
#include "LargeNumber.hpp"
#endif
#include "Math.hpp"

using namespace std;
using namespace Numbers;


int main(int argc,char** argv)
{
    if (argc<2) 
    {
        cout<<"Computes the n-th fibonacci and factorial."<<endl;
        cout<<"usage: "<<argv[0]<<" <n>"<<endl;
        exit(0);
    }

    // Initialize the correct number library
    #ifdef SMALLNUMBER
    SmallNumber n(argv[1]);
    #else
    LargeNumber n(argv[1]);
    #endif

    // Do a run of the Fibonacci
    Number *fib = Math::fibonacci(n);
    cout << "fibonacci(" << n << ") = " << (*fib) << endl;
    delete fib;

    // Do a run of the Factorial
    Number *fac = Math::factorial(n);
    cout << "factorial(" << n << ") = " << (*fac) << endl;
    delete fac;
    
    // Done
    return EXIT_SUCCESS;
}