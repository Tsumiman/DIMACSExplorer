#ifndef VERTEX_H
#define VERTEX_H
#include <set>

class QGraphicsVertexItem;
class Edge;
class Graph;

class Vertex
{
    QGraphicsVertexItem *item;
    std::set<Edge*> m_edges;
    Graph* parent;

public:
    Vertex(Graph* parent);
    ~Vertex();
    void addEdge(Edge* edge);
    QGraphicsVertexItem* repr();

    bool hasEdge(Vertex* U);

    void forgetEdge(Edge* edge);
    std::set<Edge*> edges() const;
    std::set<Vertex*> neighborhood() const;
};

#endif // VERTEX_H
