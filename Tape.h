#pragma once

#include <fstream>
#include <list>

class Tape
{
    std::list<char> data;

private:
    Tape();
    Tape(const Tape&);
    Tape& operator =(const Tape&);

public:
    Tape(char* filename);

    char first() const   { return data.front(); }
    bool empty() const   { return data.empty(); }
    char next()          { return *(++data.begin()); }
    void pop()           { data.pop_front(); }
};
