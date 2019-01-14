#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <QGraphicsScene>
#include <QFile>
#include "statistics/edgestatistic.h"

class Vertex;
class Edge;

class Graph
{
    std::vector<Vertex*> m_vertices;
    bool m_loaded;
    QGraphicsScene* m_scene;

    EdgeStatistic* m_currentEdgeStat;

    void parseLine(QString& line);

    void updateEdgeStatistic();

public:
    Graph(QGraphicsScene* scene);
    ~Graph();

    Vertex* addVertex();
    Edge* addEdge(Vertex* V, Vertex* U);
    Edge* addEdge(int V, int U);
    void deleteEdge(Edge* E);
    void deleteEdge(Vertex* V, Vertex* U);
    void deleteEdge(int V, int U);

    void clearGraph();

    void contractVertices(int V, int U);
    void contractVertices(Vertex* V, Vertex* U);
    void contractVertices(Edge* e);

    bool readFromDIMACS(QFile& source);
    void setEdgeStatistic(EdgeStatistic *statistic);
};

#endif // GRAPH_H
