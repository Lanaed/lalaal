#ifndef MARKERARRAY_H
#define MARKERARRAY_H

#include "marker.h"
#include <string>

class MarkerArray
{
public:
    MarkerArray();
    MarkerArray(unsigned int elementsCount);
    Marker at(unsigned int position);

    void setValue(unsigned int position, Marker value);
    void remove(unsigned int position);
    void resize(unsigned int size);
    void append(Marker value);

    unsigned int size();
    bool isEmpty();

    void getArray(std::string filepath);
    void toFile(std::string filepath);
    int contains(unsigned int value);
private:
    Marker* _base;
    unsigned int _elementsCount;
};

#endif // MARKERARRAY_H
