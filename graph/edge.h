#ifndef EDGE_H
#define EDGE_H
#include <algorithm>

class QGraphicsEdgeItem;
class Vertex;
class Graph;

class Edge
{
    QGraphicsEdgeItem* item;
    Graph* parent;
    std::pair<Vertex*, Vertex*> m_vertices;

public:
    Edge(Graph* parent, Vertex* U, Vertex* V);
    ~Edge();

    Graph* graph();
    std::pair<Vertex *, Vertex *> vertices() const;
    QGraphicsEdgeItem* repr();

    bool isEndpoint(const Vertex *V) const;
    Vertex* secondEndpoint(const Vertex *V) const;
};

#endif // EDGE_H
