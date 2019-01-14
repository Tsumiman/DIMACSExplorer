#include "qgraphview.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>

QGraphView::QGraphView(QWidget *parent): QGraphicsView(parent)
{

}

void QGraphView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}

