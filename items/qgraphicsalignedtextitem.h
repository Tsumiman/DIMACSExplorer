#ifndef QGRAPHICSALIGNEDTEXTITEM_H
#define QGRAPHICSALIGNEDTEXTITEM_H

#include <QGraphicsSimpleTextItem>

class QGraphicsAlignedTextItem
    : public QGraphicsSimpleTextItem
{
public:
    QGraphicsAlignedTextItem( const QString & text, Qt::Alignment flags, QGraphicsItem * pParent = 0 );
    QGraphicsAlignedTextItem( const QString & text, QGraphicsItem * pParent = 0 );
    QGraphicsAlignedTextItem( QGraphicsItem * pParent = 0 );

    ~QGraphicsAlignedTextItem();

    QRectF boundingRect() const;
    void paint( QPainter * pPainter, const QStyleOptionGraphicsItem * pOption, QWidget * pWidget = 0 );

    Qt::Alignment alignment() const;
    void setAlignment( Qt::Alignment flags );

private:
    Qt::Alignment	mFlags;
    mutable QRectF	mBounds;
};

#endif // QGRAPHICSALIGNEDTEXTITEM_H
