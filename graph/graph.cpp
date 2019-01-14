#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include "items/qgraphicsvertexitem.h"
#include "items/qgraphicsedgeitem.h"
#include <stdexcept>
#include <QDebug>

void Graph::setEdgeStatistic(EdgeStatistic *statisitc)
{
    m_currentEdgeStat = statisitc;
    updateEdgeStatistic();
}

void Graph::parseLine(QString &line)
{
    if (!line.length()) {
        return;
    }

    if (line[0] == 'c') {
        return;
    }

    if (line[0] == 'p') {
        QStringList list = line.split(" ");
        auto V = list[2].toInt();
        for (int i = 0; i < V; ++i) addVertex();
        return;
    }

    if (line[0] == 'e') {
        QStringList list = line.split(" ");
        auto V = list[1].toInt();
        auto U = list[2].toInt();
        addEdge(V-1, U-1);
        return;
    }

    else throw std::runtime_error("Wrong file format");
}

void Graph::updateEdgeStatistic()
{
    if (!m_currentEdgeStat) return;
    for (Vertex* v: m_vertices) {
        for (Edge* e: v->edges()) {
            int value = m_currentEdgeStat->calculate(e);
            e->repr()->setText(QString::number(value));
        }
    }
}

Graph::Graph(QGraphicsScene *scene): m_scene(scene)
{
    m_currentEdgeStat = nullptr;
}

Graph::~Graph()
{
    for (auto& vertex: m_vertices) {
        delete vertex;
    }
    delete m_currentEdgeStat;
}

Vertex *Graph::addVertex()
{
    m_vertices.push_back(new Vertex(this));
    m_vertices.back()->repr()->setText(QString::number(m_vertices.size()));
    this->m_scene->addItem(m_vertices.back()->repr());
    return m_vertices.back();
}

Edge *Graph::addEdge(Vertex *V, Vertex *U)
{
    Edge* edge = new Edge(this, V, U);
    this->m_scene->addItem(edge->repr());
    updateEdgeStatistic();
    return edge;
}

Edge *Graph::addEdge(int V, int U)
{
    if (std::max(V, U) >= static_cast<int>(m_vertices.size()) || std::min(V, U) < 0) {
        throw std::out_of_range("At least one of the vertices is not present in graph.");
    }
    return addEdge(m_vertices[V], m_vertices[U]);
}

void Graph::deleteEdge(Edge *E)
{
    if (!E) {
        qDebug()<<"Log: Nullptr passed to deleteEdge as edge";
        return;
    }
    updateEdgeStatistic();
    delete E;
}

void Graph::deleteEdge(Vertex *V, Vertex *U)
{
    if (!V || !U) {
        qDebug()<<"Log: Nullptr passed to deleteEdge as vertex";
        return;
    }
    for (Edge* edge: V->edges()) {
        if (edge->isEndpoint(U)) {
            deleteEdge(edge);
            return;
        }
    }
}

void Graph::deleteEdge(int V, int U)
{
    if (std::max(V, U) >= static_cast<int>(m_vertices.size()) || std::min(V, U) < 0) {
        throw std::out_of_range("At least one of the vertices is not present in graph.");
    }
    deleteEdge(m_vertices[V], m_vertices[U]);
}

void Graph::clearGraph()
{
    for (auto& V: m_vertices) {
        delete V;
    }
    m_vertices.clear();
}

void Graph::contractVertices(int V, int U)
{
    if (std::max(V, U) >= static_cast<int>(m_vertices.size()) || std::min(V, U) < 0) {
        throw std::out_of_range("At least one of the vertices is not present in graph.");
    }
    contractVertices(m_vertices[V], m_vertices[U]);
}

void Graph::contractVertices(Vertex *V, Vertex *U)
{
    for (Edge* e: U->edges()) {
        Vertex* Z = e->secondEndpoint(U);
        if (Z != V && !V->hasEdge(Z)) {
            addEdge(V, Z);
        }
    }
    m_vertices.erase(std::find(m_vertices.begin(), m_vertices.end(), U));
    delete U;
    updateEdgeStatistic();
}

void Graph::contractVertices(Edge *e)
{
    contractVertices(e->vertices().first, e->vertices().second);
}

bool Graph::readFromDIMACS(QFile &source)
{
    clearGraph();
    QTextStream in(&source);
    while (!in.atEnd()) {
        QString line = in.readLine();
        try {
            parseLine(line);
        }
        catch (std::runtime_error& error) {
            clearGraph();
            return false;
        }
    }
    return true;
}
