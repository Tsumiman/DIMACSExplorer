#ifndef QGRAPHVIEW_H
#define QGRAPHVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

class QGraphView : public QGraphicsView
{
public:
    QGraphView(QWidget* parent = nullptr);

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void newVertexRequested(const QPointF position);
};

#endif // QGRAPHVIEW_H
