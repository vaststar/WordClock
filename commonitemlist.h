#ifndef COMMONITEMLIST_H
#define COMMONITEMLIST_H

#include <QGraphicsRectItem>
#include <QStringList>
#include <QObject>

class CommonItemList : public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit CommonItemList(const QStringList &data,const QRectF &rect,QGraphicsItem *parent = nullptr,QObject *obj = nullptr);
    ~CommonItemList();
public:
    void UpdateNumber(int number);
    void initNumber(int number);
private:
    void setNumber(int initNumber);
    void startTime();
private slots:
    void frameUpdated(int frame);
private:
    void setList(const QStringList &data,const QRectF &rect,int defaultNumber=11);
    void emphasizeNumber(int number);
    void initTimeLine();
private:
    class DataPrivate;
    DataPrivate *_p;
};

#endif // COMMONITEMLIST_H
