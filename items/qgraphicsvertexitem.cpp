#include "qgraphicsvertexitem.h"
#include "qgraphicsedgeitem.h"
#include "graph/vertex.h"
#include "graph/edge.h"
#include <QDebug>

const QBrush QGraphicsVertexItem::DefaultBrush = QBrush(Qt::red);
const QBrush QGraphicsVertexItem::SelectedBrush = QBrush(Qt::yellow);
const QBrush QGraphicsVertexItem::HoverBrush = QBrush(QColor(255, 100, 100));

Vertex *QGraphicsVertexItem::getModel() const
{
    return m_model;
}

void QGraphicsVertexItem::setText(const QString& text)
{
    this->textblob->setVisible(true);
    this->text->setText(text);
    this->update();
}

void QGraphicsVertexItem::prepareTextBlob()
{
    textblob = new QGraphicsItemGroup(this);
    textblob->setVisible(false);
    QGraphicsEllipseItem* eli = new QGraphicsEllipseItem(textblob);
    text = new QGraphicsAlignedTextItem("", Qt::AlignHCenter | Qt::AlignVCenter, textblob);
    textblob->addToGroup(eli);
    textblob->addToGroup(text);
    eli->setRect(-7, -7, 14, 14);
    eli->setBrush(QBrush(Qt::white));
    eli->setPen(QPen(QBrush(Qt::blue), 2));
}

QGraphicsVertexItem::QGraphicsVertexItem(Vertex* model): QGraphicsVertexItem(model, QPointF(0, 0))
{
}

QGraphicsVertexItem::QGraphicsVertexItem(Vertex* model, const QPointF& position): m_model(model)
{
    this->prepareTextBlob();
    this->setZValue(DefaultZValue);
    this->setRect(-DefaultRadius, -DefaultRadius, 2*DefaultRadius, 2*DefaultRadius);
    this->setPos(position);
    this->centerPos = position;
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setBrush(DefaultBrush);
    this->setPen(QPen(QBrush(Qt::blue), 2));
}

const QPointF &QGraphicsVertexItem::getCenter() const
{
    return centerPos;
}

QVariant QGraphicsVertexItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange) {
        this->centerPos = value.toPointF();
        for (auto& edge: m_model->edges()) {
            edge->repr()->updatePosition();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void QGraphicsVertexItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<"WHOOP";
    this->setBrush(HoverBrush);
    return QGraphicsItem::hoverEnterEvent(event);
}
