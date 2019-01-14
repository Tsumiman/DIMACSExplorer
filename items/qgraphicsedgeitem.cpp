#include "qgraphicsedgeitem.h"
#include "qgraphicsvertexitem.h"
#include <QDebug>
#include <QPen>
#include "graph/edge.h"
#include "graph/vertex.h"
#include "items/qgraphicsalignedtextitem.h"

const QPen QGraphicsEdgeItem::DefaultPen = QPen(QBrush(Qt::blue), 2);

bool QGraphicsEdgeItem::hasText() const
{
    return textblob->isVisible();
}

void QGraphicsEdgeItem::setText(const QString &text)
{
    this->textblob->setVisible(true);
    this->text->setText(text);
    this->update();
}

void QGraphicsEdgeItem::prepareTextBlob()
{
    textblob = new QGraphicsItemGroup(this);
    textblob->setVisible(false);
    QGraphicsEllipseItem* eli = new QGraphicsEllipseItem(textblob);
    text = new QGraphicsAlignedTextItem("", Qt::AlignHCenter | Qt::AlignVCenter, textblob);
    textblob->addToGroup(eli);
    textblob->addToGroup(text);

    eli->setRect(-10, -10, 20, 20);
    eli->setBrush(QBrush(Qt::white));
    eli->setPen(QPen(QBrush(Qt::blue), 2));
}

QGraphicsEdgeItem::QGraphicsEdgeItem(Edge *model): QGraphicsLineItem(), model(model)
{
    this->setZValue(DefaultZValue);
    this->setPen(DefaultPen);
    this->prepareTextBlob();
    this->updatePosition();
}

void QGraphicsEdgeItem::updatePosition()
{
    auto* V = model->vertices().first->repr();
    auto* U = model->vertices().second->repr();
    this->setLine(QLineF(V->getCenter(), U->getCenter()));
    this->textblob->setPos((V->getCenter() + U->getCenter())/2);
}
