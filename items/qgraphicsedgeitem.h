#ifndef QGRAPHICSEDGEITEM_H
#define QGRAPHICSEDGEITEM_H
#include <QGraphicsLineItem>
#include <QPen>
#include <QGraphicsItemGroup>
#include "items/qgraphicsalignedtextitem.h"

class Edge;

class QGraphicsVertexItem;

class QGraphicsEdgeItem : public QGraphicsLineItem
{
private:
    Edge* model;
    static const int DefaultZValue = -1;
    static const QPen DefaultPen;
    QGraphicsItemGroup* textblob;
    QGraphicsAlignedTextItem *text;

    void prepareTextBlob();

public:
    QGraphicsEdgeItem(Edge* model);
    void updatePosition();
    bool hasText() const;
    void setText(const QString& text);
};

#endif // QGRAPHICSEDGEITEM_H
