#ifndef COMMONRECTITEM_H
#define COMMONRECTITEM_H

#include <QGraphicsRectItem>
#include <QColor>

class CommonRectItem : public QGraphicsRectItem
{
public:
    explicit CommonRectItem(const QString &text,QGraphicsItem *parent = nullptr);
    ~CommonRectItem()override;
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setColor(const QColor &color);
    void setBold(bool bold = false);
private:
    class DataPrivate;
    DataPrivate *_p;
};

#endif // COMMONRECTITEM_H
