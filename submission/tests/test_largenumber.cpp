/* TEST LARGENUMBER.cpp
 *   by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/16/2020, 3:20:28 PM
 * Last edited:
 *   5/18/2020, 9:23:16 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This file contains some tests for smaller parts of the LinkedList.
**/

#include <iostream>
#include <sstream>

#include "LargeNumber.hpp"

using namespace std;


#define ADD_ASSERT(N1, N2, RES) \
    LargeNumber* result_ ## N1 ## N2 ## RES = (LargeNumber*) (LargeNumber(#N1) + LargeNumber(#N2)); \
    if ((result_ ## N1 ## N2 ## RES)->to_string() != #RES) { \
        cout << " [FAIL]" << endl << endl; \
        cerr << "ERROR: Unexpected output value for " << #N1 << " + " << #N2 << ": got \"" << (*(result_ ## N1 ## N2 ## RES)) << "\", expected \"" << #RES << "\"" << endl << endl; \
        delete result_ ## N1 ## N2 ## RES; \
        return false; \
    } \
    delete result_ ## N1 ## N2 ## RES;

#define ADD_INPLACE_ASSERT(N1, N2, RES) \
    LargeNumber result_ ## N1 ## N2 ## RES(#N1); \
    result_ ## N1 ## N2 ## RES += LargeNumber(#N2); \
    if ((result_ ## N1 ## N2 ## RES).to_string() != #RES) { \
        cout << " [FAIL]" << endl << endl; \
        cerr << "ERROR: Unexpected output value for " << #N1 << " + " << #N2 << ": got \"" << (result_ ## N1 ## N2 ## RES) << "\", expected \"" << #RES << "\"" << endl << endl; \
        return false; \
    }

#define MUL_ASSERT(N1, N2, RES) \
    LargeNumber* result_ ## N1 ## N2 ## RES = (LargeNumber*) (LargeNumber(#N1) * LargeNumber(#N2)); \
    if ((result_ ## N1 ## N2 ## RES)->to_string() != #RES) { \
        cout << " [FAIL]" << endl << endl; \
        cerr << "ERROR: Unexpected output value for " << #N1 << " * " << #N2 << ": got \"" << (*(result_ ## N1 ## N2 ## RES)) << "\", expected \"" << #RES << "\"" << endl << endl; \
        delete result_ ## N1 ## N2 ## RES; \
        return false; \
    } \
    delete result_ ## N1 ## N2 ## RES;


bool test_parsing() {
    // First, let's create the expected string
    stringstream exp_stream;
    exp_stream << LinkedList({123, 4567, 8910, 1112, 1314, 1516, 1718, 1920});
    string expected = exp_stream.str();

    // Create the obect to parse shit
    LargeNumber test("1234567891011121314151617181920");
    
    string result = test.to_string();

    // Analyse the cout to see if it indeed ends with the array we expect
    if (result != "1234567891011121314151617181920") {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: Unexpected output value: got \"" << result << "\", expected 1234567891011121314151617181920" << endl << endl;
        return false;
    }

    // Otherwise, return success
    cout << " [ OK ]" << endl;
    return true;
}

bool test_equal() {
    // Create a base LargeNumber
    LargeNumber base("91638716243748921643786874619234");

    // Create two references: one is equal, one is not (based on size) and one is not based on values
    LargeNumber eq("91638716243748921643786874619234");
    LargeNumber neq_1("42");
    LargeNumber neq_2("91638716243747652873786874619234");

    // Check 'em
    if (base != eq) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: LargeNumbers are not equal while they should be: " << base << " and " << eq << "." << endl << endl;
        return false;
    } else if (base == neq_1) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: LargeNumbers are equal while they shouldn't be (case 1): " << base << " and " << neq_1 << "." << endl << endl;
        return false;
    } else if (base == neq_2) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: LargeNumbers are equal while they shouldn't be (case 2): " << base << " and " << neq_2 << "." << endl << endl;
        return false;
    }

    // Passed the tests, return success
    cout << " [ OK ]" << endl;
    return true;
}

bool test_increment_simple() {
    // First, simple case: carry of one, no adding new nodes
    LargeNumber n("19999");

    // Add it
    ++n;

    // Check if it is now 20000.
    if (n != LargeNumber("20000")) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: Number should be 20000 after incrementing, but is " << n << "." << endl << endl;
        return false;
    }

    // Otherwise, success
    cout << " [ OK ]" << endl;
    return true;
}

bool test_increment_hard() {
    // Hard case: carry over multiple nodes, create a new one
    LargeNumber n("999999999999");

    // Add it
    ++n;

    // Check if it is now 20000.
    if (n != LargeNumber("1000000000000")) {
        cout << " [FAIL]" << endl << endl;
        cerr << "ERROR: Number should be 1000000000000 after incrementing, but is " << n << "." << endl << endl;
        return false;
    }

    // Otherwise, success
    cout << " [ OK ]" << endl;
    return true;
}

bool test_add() {
    // Do a series of computations, checking them each time
    ADD_ASSERT(50, 50, 100)
    ADD_ASSERT(12412, 1234234, 1246646)
    ADD_ASSERT(0, 72349871902374902873409182734098, 72349871902374902873409182734098)
    ADD_ASSERT(100000000000000000000000000000000000, 100000000000000000000000000000000000, 200000000000000000000000000000000000)
    ADD_ASSERT(100000000000000000000000000000000000, 823894628763487264982763489263498273649, 823994628763487264982763489263498273649)
    ADD_ASSERT(999899990001, 9998999900010000, 9999999800000001)
    ADD_ASSERT(9998999900010000, 999899990001, 9999999800000001)

    // Succes!
    cout << " [ OK ]" << endl;
    return true;
}

bool test_add_inplace() {
    // Do some more computations, this time using the +=
    ADD_INPLACE_ASSERT(50, 50, 100)
    ADD_INPLACE_ASSERT(12412, 1234234, 1246646)
    ADD_INPLACE_ASSERT(0, 72349871902374902873409182734098, 72349871902374902873409182734098)
    ADD_INPLACE_ASSERT(100000000000000000000000000000000000, 100000000000000000000000000000000000, 200000000000000000000000000000000000)
    ADD_INPLACE_ASSERT(100000000000000000000000000000000000, 823894628763487264982763489263498273649, 823994628763487264982763489263498273649)
    ADD_INPLACE_ASSERT(999899990001, 9998999900010000, 9999999800000001)
    ADD_INPLACE_ASSERT(9998999900010000, 999899990001, 9999999800000001)
    
    // Succes!
    cout << " [ OK ]" << endl;
    return true;
}

bool test_multiply() {
    // Do a series of computations, checking them each time
    MUL_ASSERT(50, 50, 2500)
    MUL_ASSERT(2345, 6456465, 15140410425)
    MUL_ASSERT(1000000000, 1000000000000, 1000000000000000000000)
    MUL_ASSERT(1000000000000, 37546287634582763952468726348723648726348732, 37546287634582763952468726348723648726348732000000000000)
    MUL_ASSERT(99999999, 99999999, 9999999800000001)
    MUL_ASSERT(99999999999999999999, 99999999999999999999, 9999999999999999999800000000000000000001)

    // Succes!
    cout << " [ OK ]" << endl;
    return true;
}


int main() {
    cout << "  Testing string parsing...    ";
    if (!test_parsing()) {
        cout << "LargeNumber tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing equality function... ";
    if (!test_equal()) {
        cout << "LargeNumber tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing increment (simple)...";
    if (!test_increment_simple()) {
        cout << "LargeNumber tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing increment (hard)...  ";
    if (!test_increment_hard()) {
        cout << "LargeNumber tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing addition...          ";
    if (!test_add()) {
        cout << "LargeNumber tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing addition (inplace)...";
    if (!test_add_inplace()) {
        cout << "LargeNumber tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "  Testing multiplication...    ";
    if (!test_multiply()) {
        cout << "LargeNumber tests failed." << endl << endl;
        return EXIT_FAILURE;
    }

    cout << "LargeNumber tests success!" << endl << endl;
    return EXIT_SUCCESS;
}
