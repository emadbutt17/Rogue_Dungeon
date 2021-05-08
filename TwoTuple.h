#ifndef TWOTUPLE_H_
#define TWOTUPLE_H_

#include <string>

class TwoTuple{

private:
    const int DEBUG = 0;
    const std::string CLASSID = "TwoTuple";
    int first;
    int second;

public:
    TwoTuple(int rp, int tp);
    std::string toString();
    bool equals(TwoTuple* other);
    int hashCode( );
    void setSecond(int s);
    int getSecond();
    void setFirst(int f);
    int getFirst();
};

#endif

