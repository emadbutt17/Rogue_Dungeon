#include "TwoTuple.h"

TwoTuple::TwoTuple(int rp, int tp) {
    first = rp;
    second = tp;
}

// usually a room
int TwoTuple::getFirst() {
    return this->first;
}

void TwoTuple::setFirst(int f) {
    this->first = f;
}

// usually a thing serial number
int TwoTuple::getSecond() {
    return second;
}

void TwoTuple::setSecond(int s) {
    second = s;
}


//int TwoTuple::hashCode( ) { //TODO Is this needed?
//    return Integer.valueOf(first+second).hashCode( );
//}

bool TwoTuple::equals(TwoTuple* other) {
    if (this == other) return true;
    if (other == NULL) return false;
    return (first == other->getFirst() && second == other->getSecond());
}


/*bool TwoTuple::equals(Object* other) { //TODO: Not sure how this would be implemented in C++
    if (other == null) return false;
    if (this == other) return true;
    if (other instanceof TwoTuple) {
        return equals((TwoTuple) other);
    } else {
        return false;
    }
}*/

std::string TwoTuple::toString() {
            std::string str = CLASSID + "\n";
    str += "   first: " + std::to_string(first) + "\n";
    str += "   second: " + std::to_string(second) + "\n";
    return str;
}

