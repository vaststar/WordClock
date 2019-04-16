#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMenu>

namespace Ui {
class mainwidget;
}

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainwidget(QWidget *parent = nullptr);
    ~mainwidget();
public:
    void startApp();
private:
    void InitTray();
    void StartWallPaper();
    void StartScreenSaver();
    void StartClock(bool wallpaper);
signals:
    void StopWallPaper();
    void StopScreenSaver();
private slots:
    void ChangeType();
    void ChangeScreenTime(QMenu*menu,int index,bool checked);
private:
    Ui::mainwidget *ui;
    class DataPrivate;
    DataPrivate *_p;
};

#endif // MAINWIDGET_H
