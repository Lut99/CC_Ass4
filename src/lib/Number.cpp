/* NUMBER.cpp
 *   by Anonymous
 *
 * Created:
 *   5/15/2020, 6:35:01 PM
 * Last edited:
 *   5/15/2020, 6:40:26 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The number class forms the abstract basis for both the SmallNumber and
 *   the BigNumber classes.
**/

#include "Number.hpp"

using namespace std;
using namespace Numbers;


bool Number::operator!=(const Number& n) const {
    return !((*this) == n);
}



ostream& Numbers::operator<<(ostream& os, const Number& n) {
    n.print(os);
    return os;
}

