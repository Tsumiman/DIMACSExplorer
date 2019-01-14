#include "vertex.h"
#include "edge.h"
#include "items/qgraphicsvertexitem.h"

std::set<Edge *> Vertex::edges() const
{
    return m_edges;
}

std::set<Vertex *> Vertex::neighborhood() const
{
    std::set<Vertex*> result;
    for (Edge* e: m_edges) {
        result.insert(e->secondEndpoint(this));
    }
    return result;
}

Vertex::Vertex(Graph* parent): parent(parent)
{
    item = new QGraphicsVertexItem(this, QPointF(-500+rand()%1000, -500+rand()%1000));
}

Vertex::~Vertex()
{
    while (!m_edges.empty()) {
        delete *m_edges.begin();
    }
    delete item;
}

void Vertex::addEdge(Edge *edge)
{
    m_edges.insert(edge);
}

QGraphicsVertexItem *Vertex::repr()
{
    return item;
}

bool Vertex::hasEdge(Vertex *U)
{
    for (Edge* edge: m_edges) {
        if (edge->isEndpoint(U)) {
            return true;
        }
    }
    return false;
}

void Vertex::forgetEdge(Edge *edge)
{
    m_edges.erase(edge);
}
