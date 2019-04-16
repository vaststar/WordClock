#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QSystemTrayIcon>
#include <QGuiApplication>
#include <QScreen>
#include <QMenu>
#include <QSettings>
#include <QDir>
#include <QDebug>

#include "clockview.h"
#include "makedesktop.h"
#include "globaleventfilter.h"

class mainwidget::DataPrivate
{
public:
    DataPrivate()
        :wallpaper(nullptr)
        ,screen(nullptr)
        ,filter(new GlobalEventFilter())
        ,configFile(new QSettings( QCoreApplication::applicationDirPath() + QDir::separator() + "config.ini", QSettings::IniFormat))
    {
        qApp->installNativeEventFilter(filter);
    }
public:
    clockView *wallpaper;
    clockView *screen;
    GlobalEventFilter *filter;
    QSettings *configFile;//配置文件
};

mainwidget::mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwidget),
    _p(new DataPrivate())
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow );
    startApp();
}

mainwidget::~mainwidget()
{
    delete ui;
}

void mainwidget::startApp()
{
    InitTray();
    StartClock(_p->configFile->value("/settings/wallpaper",false).toBool());
}

void mainwidget::InitTray()
{
    QSystemTrayIcon *tray = new QSystemTrayIcon(this);
    tray ->setIcon(QIcon(":/logo.png"));
    tray->setToolTip(QStringLiteral("Word Clock"));
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet("QMenu{background:white;}QMenu:selected {background:rgb(222,222,222);}QMenu::item {background:white;color:black;}QMenu::item:selected {background:rgb(222,222,222);}");

    QAction *actionSet = menu->addAction(_p->configFile->value("/settings/wallpaper",false).toBool()?QStringLiteral("切换为屏保"):QStringLiteral("切换为壁纸"));
    connect(actionSet,&QAction::triggered,this,&mainwidget::ChangeType);

    QAction *action = menu->addAction(QStringLiteral("退出"));
    connect(action,&QAction::triggered,this,&mainwidget::close);
    connect(action,&QAction::triggered,qApp,&QApplication::quit);
    tray->setContextMenu(menu);
    tray->show();
}

void mainwidget::StartWallPaper()
{
    if(!_p->wallpaper)
    {
        _p->wallpaper = new clockView(nullptr);
        makeDesktop::MakeHandleDesktop(_p->wallpaper);//替换桌面背景
        connect(this,&mainwidget::StopWallPaper,_p->wallpaper,&clockView::stopClock);
        connect(this,&mainwidget::StopWallPaper,_p->wallpaper,&clockView::hide);
    }
    _p->wallpaper->showMaximized();
    _p->wallpaper->startClock();
}

void mainwidget::StartScreenSaver()
{
    if(!_p->screen)
    {
        _p->screen = new clockView(nullptr);
        _p->screen->setGeometry(QGuiApplication::primaryScreen()->geometry());
        connect(_p->filter,&GlobalEventFilter::LesuireTime,[this](int time){
            if(time>60){
                _p->screen->startClock();
                _p->screen->showFullScreen();
            }
            else{
                _p->screen->stopClock();
                _p->screen->hide();
            }
        });
        connect(this,&mainwidget::StopScreenSaver,[this](){
            _p->filter->stopFilter();
            _p->screen->stopClock();
            _p->screen->hide();
        });
    }
    _p->filter->startFilter();
}

void mainwidget::StartClock(bool wallpaper)
{
    if(wallpaper)
    {
        StartWallPaper();
        emit StopScreenSaver();
    }else{
        StartScreenSaver();
        emit StopWallPaper();
    }
}

void mainwidget::ChangeType()
{
    bool IsNowWallPaper = !_p->configFile->value("/settings/wallpaper",false).toBool();
    _p->configFile->setValue("/settings/wallpaper",IsNowWallPaper);
    dynamic_cast<QAction*>(sender())->setText(IsNowWallPaper?QStringLiteral("切换为屏保"):QStringLiteral("切换为壁纸"));
    StartClock(IsNowWallPaper);
}

