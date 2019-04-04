#include "commonitemlist.h"

#include <vector>
#include <QTimeLine>
#include <QDebug>
#include "commonrectitem.h"

class CommonItemList::DataPrivate
{
public:
    DataPrivate()
        :timeLine(new QTimeLine(1000,nullptr))
        ,currentNumber(0)
        ,singleAngle(0)
        ,currentAngle(0)
    {

    }
    ~DataPrivate(){
        delete timeLine;
        timeLine = nullptr;
    }
public:
    std::vector<CommonRectItem*> childs;
    QTimeLine *timeLine;
    double singleAngle;
    int currentNumber;
    double currentAngle;
};

CommonItemList::CommonItemList(const QStringList &data,const QRectF &rect,QGraphicsItem *parent,QObject *obj)
    : QObject(obj),QGraphicsRectItem(parent)
    ,_p(new DataPrivate())
{
    initTimeLine();
    setList(data,rect,1);
}

CommonItemList::~CommonItemList()
{
    delete _p;
}

void CommonItemList::UpdateNumber(int number)
{
    if(number != _p->currentNumber)
    {
        setNumber(number);
        startTime();
    }
}

void CommonItemList::initNumber(int number)
{
    setNumber(number);
    this->setRotation(_p->currentAngle);
//    startTime();
}

void CommonItemList::setList(const QStringList &data,const QRectF &rect,int defaultNumber)
{
    this->setRect(rect);
    _p->singleAngle = 360.0/std::max<double>(0,data.count());
    this->setTransformOriginPoint(this->rect().center());

    for(int i=0;i<data.count();++i)
    {
        CommonRectItem* item = new CommonRectItem(data.at(i),this);
        item->setRect(this->rect());
        item->setTransformOriginPoint(item->rect().center());
        item->setRotation(_p->singleAngle*i);
        _p->childs.push_back(item);
    }
    setNumber(defaultNumber);
}

void CommonItemList::setNumber(int initNumber)
{
    _p->currentNumber = initNumber;
    _p->currentAngle = -_p->singleAngle*std::max<size_t>(0,std::min<size_t>(initNumber-1,_p->childs.size()-1));
    emphasizeNumber(initNumber);
}

void CommonItemList::startTime()
{
    _p->timeLine->stop();
    _p->timeLine->start();
}

void CommonItemList::frameUpdated(int frame)
{
    static int n=0;
    if(frame<150)
    {
        this->setRotation(_p->currentAngle+_p->singleAngle*(1-frame/150.0));
    }
    else if(frame < 1000)
    {
        this->setRotation(_p->currentAngle+(n%2?-1:1)*(1000-frame)/3000.);
        ++n;
    }
    else
    {
        n=0;
        this->setRotation(_p->currentAngle);
    }
}

void CommonItemList::emphasizeNumber(int number)
{
    for(size_t i=0;i<_p->childs.size();++i)
    {
        if(static_cast<size_t>(number-1) != i)
        {
            _p->childs[i]->setColor(Qt::gray);
            _p->childs[i]->setBold(false);
        }
        else
        {
            _p->childs[i]->setColor(Qt::white);
            _p->childs[i]->setBold(true);
        }
    }
}

void CommonItemList::initTimeLine()
{
    _p->timeLine->setFrameRange(0,1000);
    _p->timeLine->setUpdateInterval(10);
    connect(_p->timeLine,&QTimeLine::frameChanged,this,&CommonItemList::frameUpdated);
}
