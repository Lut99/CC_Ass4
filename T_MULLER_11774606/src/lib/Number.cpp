/* NUMBER.cpp
 *   by Tim Müller (11774606)
 * 
 * ASSIGNMENT 4
 * 
 * Compiled on KDE Neon (Ubuntu 18.04.2) with GCC 7.5.0
 *
 * Created:
 *   5/15/2020, 6:35:01 PM
 * Last edited:
 *   5/18/2020, 9:25:35 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The number class forms the abstract basis for both the SmallNumber and
 *   the BigNumber classes.
**/

#include <sstream>

#include "Number.hpp"

using namespace std;


bool Number::operator!=(const Number& n) const {
    return !((*this) == n);
}



ostream& operator<<(ostream& os, const Number& n) {
    n.print(os);
    return os;
}
