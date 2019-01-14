#include "edge.h"
#include "vertex.h"
#include "items/qgraphicsedgeitem.h"
#include <stdexcept>

std::pair<Vertex *, Vertex *> Edge::vertices() const
{
    return m_vertices;
}

QGraphicsEdgeItem *Edge::repr()
{
    return item;
}

bool Edge::isEndpoint(const Vertex *V) const
{
    return (m_vertices.first == V || m_vertices.second == V);
}

Vertex *Edge::secondEndpoint(const Vertex *V) const
{
    if (!isEndpoint(V)) {
        throw std::runtime_error("Asked for a second endpoint of an edge for which the first vertex is not an endpoint.");
    }
    if (m_vertices.first == V) {
        return m_vertices.second;
    }
    else {
        return m_vertices.first;
    }
}

Edge::Edge(Graph* parent, Vertex *U, Vertex *V): parent(parent), m_vertices(V, U)
{
    item = new QGraphicsEdgeItem(this);
    U->addEdge(this);
    V->addEdge(this);
}

Edge::~Edge()
{
    m_vertices.first->forgetEdge(this);
    m_vertices.second->forgetEdge(this);
    delete item;
}

Graph *Edge::graph()
{
    return parent;
}
