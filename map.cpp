#pragma once
#include <vector>
#include "location.cpp"
using namespace std;

class map{
public:
    map(const vector<location> &mapping) : mapping(mapping) {}

    const vector<location> &getMapping() const {
        return mapping;
    }

    void setMapping(const vector<location> &mapping) {
        map::mapping = mapping;
    }

private:
    vector<location> mapping;

};

