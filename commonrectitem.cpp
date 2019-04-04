#include "commonrectitem.h"

#include <QPainter>
#include <QDebug>
class CommonRectItem::DataPrivate
{
public:
    DataPrivate(const QString &text)
        :labelText(text)
        ,color(QColor(Qt::gray))
        ,isBold(false)
    {

    }
public:
    QString labelText;
    QColor color;
    bool isBold;
};

CommonRectItem::CommonRectItem(const QString &text,QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
    ,_p(new DataPrivate(text))
{
}

CommonRectItem::~CommonRectItem()
{
    delete _p;
}

void CommonRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font = painter->font();
    font.setFamily("\"微软雅黑\"");
    font.setPixelSize(14);
    painter->setPen(_p->color);
    font.setBold(_p->isBold);
    painter->setFont(font);

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    painter->drawText(QRectF(this->rect().center().x(),this->rect().center().y()-20,this->rect().height()/2,40),Qt::AlignRight|Qt::AlignVCenter,_p->labelText);
}

void CommonRectItem::setColor(const QColor &color)
{
    _p->color = color;
}

void CommonRectItem::setBold(bool bold)
{
    _p->isBold = bold;
}
