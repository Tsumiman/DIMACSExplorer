#ifndef COMMONNEIGHBORHOODSTATISTIC_H
#define COMMONNEIGHBORHOODSTATISTIC_H
#include "edgestatistic.h"

class CommonNeighborhoodStatistic: public EdgeStatistic
{
public:
    CommonNeighborhoodStatistic();

    int calculate(const Edge* E) const override;
};

#endif // COMMONNEIGHBORHOODSTATISTIC_H
