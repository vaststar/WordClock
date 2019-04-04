#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "clockview.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDebug>

mainwidget::mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwidget)
{
    ui->setupUi(this);
    this->showMaximized();
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow );
    InitTray();
}

mainwidget::~mainwidget()
{
    delete ui;
}

void mainwidget::InitTray()
{
    QSystemTrayIcon *tray = new QSystemTrayIcon(this);
    tray ->setIcon(QIcon(":/logo.png"));
    tray->setToolTip(QStringLiteral("Word Clock"));
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet("QMenu{background:white;}QMenu:selected {background:rgb(222,222,222);}QMenu::item {background:white;color:black;}QMenu::item:selected {background:rgb(222,222,222);}");
    QAction *action = menu->addAction(QStringLiteral("退出"));
    connect(action,&QAction::triggered,this,&mainwidget::close);
    connect(action,&QAction::triggered,qApp,&QApplication::quit);
    tray->setContextMenu(menu);
    tray->show();
}
