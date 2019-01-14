#include "commonneighborhoodstatistic.h"
#include "graph/edge.h"
#include "graph/vertex.h"
#include <algorithm>

struct Counter
{
  struct value_type { template<typename T> value_type(const T&) { } };
  void push_back(const value_type&) { ++count; }
  size_t count = 0;
};

CommonNeighborhoodStatistic::CommonNeighborhoodStatistic()
{

}

int CommonNeighborhoodStatistic::calculate(const Edge *E) const
{
    Vertex *V = E->vertices().first;
    Vertex *U = E->vertices().second;
    auto vNBH = V->neighborhood();
    auto uNBH = U->neighborhood();
    Counter c;
    std::set_intersection(vNBH.begin(), vNBH.end(), uNBH.begin(), uNBH.end(), std::back_inserter(c));
    return c.count;
}
