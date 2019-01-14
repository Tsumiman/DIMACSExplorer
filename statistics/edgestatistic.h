#ifndef EDGESTATISTIC_H
#define EDGESTATISTIC_H
#include "graph/edge.h"

class EdgeStatistic
{
public:
    EdgeStatistic();
    virtual ~EdgeStatistic();
    virtual int calculate(const Edge* e) const = 0;

};

#endif // EDGESTATISTIC_H
