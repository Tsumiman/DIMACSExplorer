#ifndef QGRAPHICSVERTEXITEM_H
#define QGRAPHICSVERTEXITEM_H
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <set>
#include "qgraphicsalignedtextitem.h"

class QGraphicsEdgeItem;
class Vertex;

class QGraphicsVertexItem : public QGraphicsEllipseItem
{
    Vertex* m_model;
    static const int DefaultRadius = 15;
    static const int DefaultZValue = 1;
    static const int DefaultBlobZValue = 5;
    static const int DefaultTextZValue = 6;
    static const QBrush DefaultBrush;
    static const QBrush SelectedBrush;
    static const QBrush HoverBrush;

    QGraphicsItemGroup* textblob;
    QGraphicsAlignedTextItem *text;
    void prepareTextBlob();

    QPointF centerPos;

public:
    QGraphicsVertexItem(Vertex* m_model);
    QGraphicsVertexItem(Vertex* m_model, const QPointF& position);

    const QPointF& getCenter() const;
    void setText(const QString& text);

    // QGraphicsItem interface
    Vertex *getModel() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
};

#endif // QGRAPHICSVERTEXITEM_H
