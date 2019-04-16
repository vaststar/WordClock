#include "clockview.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QtDebug>
#include <QDateTime>

#include "commonitemlist.h"

class clockView::DataPrivate{
public:
    DataPrivate()
        :scene(new QGraphicsScene(nullptr))
        ,second(nullptr),minitue(nullptr),hour(nullptr),lightornight(nullptr),dayofweek(nullptr),day(nullptr),month(nullptr)
        ,timer(new QTimer(nullptr))
    {
        months<<QStringLiteral("一月")<<QStringLiteral("二月")<<QStringLiteral("三月")<<QStringLiteral("四月")<<QStringLiteral("五月")<<QStringLiteral("六月")<<QStringLiteral("七月")<<QStringLiteral("八月")<<QStringLiteral("九月")<<QStringLiteral("十月")
              <<QStringLiteral("十一月")<<QStringLiteral("十二月");
        days<<QStringLiteral("一日")<<QStringLiteral("二日")<<QStringLiteral("三日")<<QStringLiteral("四日")<<QStringLiteral("五日")<<QStringLiteral("六日")<<QStringLiteral("七日")<<QStringLiteral("八日")<<QStringLiteral("九日")<<QStringLiteral("十日")
            <<QStringLiteral("十一日")<<QStringLiteral("十二日")<<QStringLiteral("十三日")<<QStringLiteral("十四日")<<QStringLiteral("十五日")<<QStringLiteral("十六日")<<QStringLiteral("十七日")<<QStringLiteral("十八日")<<QStringLiteral("十九日")<<QStringLiteral("二十日")
            <<QStringLiteral("二十一日")<<QStringLiteral("二十二日")<<QStringLiteral("二十三日")<<QStringLiteral("二十四日")<<QStringLiteral("二十五日")<<QStringLiteral("二十六日")<<QStringLiteral("二十七日")<<QStringLiteral("二十八日")<<QStringLiteral("二十九日")<<QStringLiteral("三十日")
            <<QStringLiteral("三十一日");
        dayOfWeek<<QStringLiteral("星期一")<<QStringLiteral("星期二")<<QStringLiteral("星期三")<<QStringLiteral("星期四")<<QStringLiteral("星期五")<<QStringLiteral("星期六")<<QStringLiteral("星期日");
        lightOrNight<<QStringLiteral("上午")<<QStringLiteral("下午");
        hours<<QStringLiteral("一点")<<QStringLiteral("二点")<<QStringLiteral("三点")<<QStringLiteral("四点")<<QStringLiteral("五点")<<QStringLiteral("六点")<<QStringLiteral("七点")<<QStringLiteral("八点")<<QStringLiteral("九点")<<QStringLiteral("十点")
             <<QStringLiteral("十一点")<<QStringLiteral("十二点");
        minitues<<QStringLiteral("一分")<<QStringLiteral("二分")<<QStringLiteral("三分")<<QStringLiteral("四分")<<QStringLiteral("五分")<<QStringLiteral("六分")<<QStringLiteral("七分")<<QStringLiteral("八分")<<QStringLiteral("九分")<<QStringLiteral("十分")
               <<QStringLiteral("十一分")<<QStringLiteral("十二分")<<QStringLiteral("十三分")<<QStringLiteral("十四分")<<QStringLiteral("十五分")<<QStringLiteral("十六分")<<QStringLiteral("十七分")<<QStringLiteral("十八分")<<QStringLiteral("十九分")<<QStringLiteral("二十分")
               <<QStringLiteral("二十一分")<<QStringLiteral("二十二分")<<QStringLiteral("二十三分")<<QStringLiteral("二十四分")<<QStringLiteral("二十五分")<<QStringLiteral("二十六分")<<QStringLiteral("二十七分")<<QStringLiteral("二十八分")<<QStringLiteral("二十九分")<<QStringLiteral("三十分")
               <<QStringLiteral("三十一分")<<QStringLiteral("三十二分")<<QStringLiteral("三十三分")<<QStringLiteral("三十四分")<<QStringLiteral("三十五分")<<QStringLiteral("三十六分")<<QStringLiteral("三十七分")<<QStringLiteral("三十八分")<<QStringLiteral("三十九分")<<QStringLiteral("四十分")
               <<QStringLiteral("四十一分")<<QStringLiteral("四十二分")<<QStringLiteral("四十三分")<<QStringLiteral("四十四分")<<QStringLiteral("四十五分")<<QStringLiteral("四十六分")<<QStringLiteral("四十七分")<<QStringLiteral("四十八分")<<QStringLiteral("四十九分")<<QStringLiteral("五十分")
               <<QStringLiteral("五十一分")<<QStringLiteral("五十二分")<<QStringLiteral("五十三分")<<QStringLiteral("五十四分")<<QStringLiteral("五十五分")<<QStringLiteral("五十六分")<<QStringLiteral("五十七分")<<QStringLiteral("五十八分")<<QStringLiteral("五十九分")<<QStringLiteral("零分");

        seconds<<QStringLiteral("一秒")<<QStringLiteral("二秒")<<QStringLiteral("三秒")<<QStringLiteral("四秒")<<QStringLiteral("五秒")<<QStringLiteral("六秒")<<QStringLiteral("七秒")<<QStringLiteral("八秒")<<QStringLiteral("九秒")<<QStringLiteral("十秒")
              <<QStringLiteral("十一秒")<<QStringLiteral("十二秒")<<QStringLiteral("十三秒")<<QStringLiteral("十四秒")<<QStringLiteral("十五秒")<<QStringLiteral("十六秒")<<QStringLiteral("十七秒")<<QStringLiteral("十八秒")<<QStringLiteral("十九秒")<<QStringLiteral("二十秒")
              <<QStringLiteral("二十一秒")<<QStringLiteral("二十二秒")<<QStringLiteral("二十三秒")<<QStringLiteral("二十四秒")<<QStringLiteral("二十五秒")<<QStringLiteral("二十六秒")<<QStringLiteral("二十七秒")<<QStringLiteral("二十八秒")<<QStringLiteral("二十九秒")<<QStringLiteral("三十秒")
              <<QStringLiteral("三十一秒")<<QStringLiteral("三十二秒")<<QStringLiteral("三十三秒")<<QStringLiteral("三十四秒")<<QStringLiteral("三十五秒")<<QStringLiteral("三十六秒")<<QStringLiteral("三十七秒")<<QStringLiteral("三十八秒")<<QStringLiteral("三十九秒")<<QStringLiteral("四十秒")
              <<QStringLiteral("四十一秒")<<QStringLiteral("四十二秒")<<QStringLiteral("四十三秒")<<QStringLiteral("四十四秒")<<QStringLiteral("四十五秒")<<QStringLiteral("四十六秒")<<QStringLiteral("四十七秒")<<QStringLiteral("四十八秒")<<QStringLiteral("四十九秒")<<QStringLiteral("五十秒")
              <<QStringLiteral("五十一秒")<<QStringLiteral("五十二秒")<<QStringLiteral("五十三秒")<<QStringLiteral("五十四秒")<<QStringLiteral("五十五秒")<<QStringLiteral("五十六秒")<<QStringLiteral("五十七秒")<<QStringLiteral("五十八秒")<<QStringLiteral("五十九秒")<<QStringLiteral("零秒");
    }
public:
    QGraphicsScene *scene;
    QStringList seconds;
    QStringList minitues;
    QStringList hours;
    QStringList lightOrNight;
    QStringList dayOfWeek;
    QStringList days;
    QStringList months;
    CommonItemList *second;
    CommonItemList *minitue;
    CommonItemList *hour;
    CommonItemList *lightornight;
    CommonItemList *dayofweek;
    CommonItemList *day;
    CommonItemList *month;
    QTimer *timer;
};

clockView::clockView(QWidget *parent) :
    QGraphicsView(parent),
    _p(new DataPrivate())
{
    this->setCursor(QCursor(Qt::BlankCursor));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow );
    setStyleSheet("QWidget{background:back;}");
    QTimer::singleShot(1000,this,&clockView::initScene);
}

clockView::~clockView()
{
    delete _p;
}

void clockView::startClock()
{
    if(!_p->timer->isActive())
    {
        _p->timer->start(1000);
    }

}

void clockView::stopClock()
{
    if(_p->timer->isActive())
    {
        _p->timer->stop();
    }
}

void clockView::updateTime()
{
    QDateTime time(QDateTime::currentDateTime().addMSecs(400));
    _p->second->UpdateNumber(time.time().second()==0?60:time.time().second());
    _p->minitue->UpdateNumber(time.time().minute()==0?60:time.time().minute());
    _p->hour->UpdateNumber(time.time().hour()%12);
    _p->lightornight->UpdateNumber(time.time().hour()<=12?1:2);
    _p->dayofweek->UpdateNumber(time.date().dayOfWeek());
    _p->day->UpdateNumber(time.date().day());
    _p->month->UpdateNumber(time.date().month());
}

void clockView::initScene()
{
    setScene(_p->scene);
    _p->scene->setSceneRect(this->rect());

    _p->second = new CommonItemList(_p->seconds,QRect(QPoint(0,5),QSize(this->rect().width(),this->rect().height()-10)));
    _p->scene->addItem(_p->second);

    _p->minitue = new CommonItemList(_p->minitues,QRect(this->rect().x(),this->rect().y()+70,this->rect().width(),this->rect().height()-140));
    _p->scene->addItem(_p->minitue);

    _p->hour = new CommonItemList(_p->hours,QRect(this->rect().x(),this->rect().y()+135,this->rect().width(),this->rect().height()-270));
    _p->scene->addItem(_p->hour);

    _p->lightornight = new CommonItemList(_p->lightOrNight,QRect(this->rect().x(),this->rect().y()+185,this->rect().width(),this->rect().height()-370));
    _p->scene->addItem(_p->lightornight);

    _p->dayofweek = new CommonItemList(_p->dayOfWeek,QRect(this->rect().x(),this->rect().y()+225,this->rect().width(),this->rect().height()-450));
    _p->scene->addItem(_p->dayofweek);

    _p->day = new CommonItemList(_p->days,QRect(this->rect().x(),this->rect().y()+280,this->rect().width(),this->rect().height()-560));
    _p->scene->addItem(_p->day);

    _p->month = new CommonItemList(_p->months,QRect(this->rect().x(),this->rect().y()+350,this->rect().width(),this->rect().height()-700));
    _p->scene->addItem(_p->month);

    initClock();
}

void clockView::initClock()
{
    QDateTime time(QDateTime::currentDateTime().addMSecs(400));
    _p->second->initNumber(time.time().second());
    _p->minitue->initNumber(time.time().minute());
    _p->hour->initNumber(time.time().hour()%12);
    _p->lightornight->initNumber(time.time().hour()<=12?1:2);
    _p->dayofweek->initNumber(time.date().dayOfWeek());
    _p->day->initNumber(time.date().day());
    _p->month->initNumber(time.date().month());

    connect(_p->timer,&QTimer::timeout,this,&clockView::updateTime);
//    startClock();
}

